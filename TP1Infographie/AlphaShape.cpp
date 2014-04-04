#include "AlphaShape.h"

#include "Triangle.h"
#include <set>

void AlphaShape::getAlphaShape(Mesh &source, Mesh &alphaShape)
{
	std::vector<GLfloat> vertices;
	//Création de la liste des points en dupliquant celle du mesh source
	vertices.assign(source.getVertices(), source.getVertices() + source.getNumVertices());
	std::vector<GLuint> faces;
	m_tempMesh = &source;

	//On génère les liste de triangles ordonnés pas plus grand Lambda (une liste ordonnée de composé d'élément avec un point et sa liste ordonnée de point associé)
	generateAllTetraedreForAlphaShape();

	if(m_tetraedreList.size() > 0)//Si on a bien des objets
	{
		std::set<Triangle> listeTriangles;
		while(m_tetraedreList.size() > 0)
		{
			//1. On choisis le M avec le plus grand lamba ABC ce point est retiré de la liste des points restant à traiter
			ListOfTriangleFromPoint listeCourante = m_tetraedreList.top();
			m_tetraedreList.pop();//on retire le point de la liste
			//2. On supprime tous les triangles associés à ce point. cela crée un trou comme pour l'enveloppe convexe
				//je pas de triangles de base que supprimme t'on ?
			//3. On bouche le trou avec M comme dans le cas de l'enveloppe convexe, le choix de M consiste à creuser l'objet le moins possible.
				//le même M qu'au dessus ? celà parait avoir peu de sens, dans ce cas comment choisir le M ? ce n'est pas clair
			//4. on associe alors des points aux nouveau triangles comme ci dessus (?)
				//Quel ci dessus ?
			//5. retour à 1 sauf si n'y a plus de point associé à un triangle (boucle while)
		}
	}
	else
	{
		std::cout << "no points for alphashape" << std::endl;
	}
	alphaShape.init(vertices.size()/3, vertices.data(), nullptr, nullptr, nullptr, faces.size(), faces.data());//Création du mesh pour OpenGL (interface graphique non utilisée pour le moment)
}

void AlphaShape::generateAllTetraedreForAlphaShape()
{
	GLuint numVertices = m_tempMesh->getNumVertices();
	for(GLuint i = 0; i < numVertices-2; i++)//3 boucle pour avoir chaque triangle de la forme
		for(GLuint j = i+1; j < numVertices-1; j++)
			for(GLuint k = j+1; k < numVertices; k++)
				addTetraedreWithHigherLambdaOfTriangle(i, j, k);//on cherche le plus grand lambda du triangle actuel
	//On transforme la map en priority queue
	for(std::map<GLfloat*,ListOfTriangleFromPoint>::iterator it = m_tempConstructorMap.begin(); it != m_tempConstructorMap.end(); ++it)
		m_tetraedreList.push(it->second);
}

void AlphaShape::addTetraedreWithHigherLambdaOfTriangle(GLuint p1, GLuint p2, GLuint p3)
{
	GLfloat *vertices = m_tempMesh->getVertices();
	GLuint numVertices = m_tempMesh->getNumVertices();

	GLint firstM;//détermination de premier point pour faire un tétraèdre
	if(p1 != 0)
		firstM = 0;
	else if(p2 != 1)
		firstM = 1;
	else if (p3 != 2)
		firstM = 2;
	else
		firstM = 3;

	std::vector<GLuint> indexes(4);
	indexes[0] = p1;
	indexes[1] = p2;
	indexes[2] = p3;
	indexes[3] = firstM;
	//création de premier tétraèdre
	Tetraedre maxTetraedre = Tetraedre(indexes,glm::mat4x3(vertices[p1*3],vertices[p1*3+1],vertices[p1*3+2],vertices[p2*3],vertices[p2*3+1],vertices[p2*3+2],vertices[p3*3],vertices[p3*3+1],vertices[p3*3+2],vertices[firstM*3],vertices[firstM*3+1],vertices[firstM*3+2]));
	for(GLuint i = firstM + 1; i < numVertices ; i ++)// on crée tout les tétraèdres possible
	{
		if(i != p1 && i != p2 && i != p3)//vérification que M n'est pas un poitn déjà utilisé
		{
			indexes = std::vector<GLuint>(4);
			indexes[0] = p1;
			indexes[1] = p2;
			indexes[2] = p3;
			indexes[3] = i;
			//création du tétraedre avec le point actuel
			glm::mat4x3 values(vertices[p1*3],vertices[p1*3+1],vertices[p1*3+2],vertices[p2*3],vertices[p2*3+1],vertices[p2*3+2],vertices[p3*3],vertices[p3*3+1],vertices[p3*3+2],vertices[i*3],vertices[i*3+1],vertices[i*3+2]);
			Tetraedre current = Tetraedre(indexes, values);
			if(current > maxTetraedre)//on regarde qui a le plus grand rayon de cercle circonscrit
				maxTetraedre = current;
		}
	}
	if(maxTetraedre.getLambda() >= 0)//si le plus grand lambda est positif, on le rajoute à la map des tétraèdres avec pour clé le point M
	{
		if(m_tempConstructorMap.find(&maxTetraedre.getVertices()[3*3]) != m_tempConstructorMap.end())
			m_tempConstructorMap[&maxTetraedre.getVertices()[3*3]] = ListOfTriangleFromPoint();
		m_tempConstructorMap[&maxTetraedre.getVertices()[3*3]].addTetraedre(maxTetraedre);
	}
	else//ou sinon on rajoute un triangle dans les triangles inutilisés
	{
		indexes = std::vector<GLuint>(3);
		indexes[0] = p1;
		indexes[1] = p2;
		indexes[2] = p3;
		glm::mat3 values(vertices[p1*3],vertices[p1*3+1],vertices[p1*3+2],vertices[p2*3],vertices[p2*3+1],vertices[p2*3+2],vertices[p3*3],vertices[p3*3+1],vertices[p3*3+2]);
		m_unusedTriangles.push_back(Triangle(indexes,values));
	}
}
