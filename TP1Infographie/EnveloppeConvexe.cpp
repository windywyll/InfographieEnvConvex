#include "EnveloppeConvexe.h"

using namespace std;

EnveloppeConvexe::EnveloppeConvexe()
{
	m_vertices = NULL;
}

void EnveloppeConvexe::add_edges(glm::vec3 p1, glm::vec3 p2)
{
	for ( vector<GLfloat*>::iterator it = m_edges.begin(), itE = m_edges.end(); it != itE; it ++ )
	{
		if()
			//si p2 = les cases i, i+1, i+2 et p1 = les trois suivantes
				//alors un truc
			//sinon
				//ajouter bords
	}
}

void EnveloppeConvexe::filter(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 pTest)
{
	glm::vec3 v1 = p1 - pTest;
	glm::vec3 v2 = p2 - pTest;
	glm::vec3 v3 = p3 - pTest;
	int deltpos = glm::determinant(glm::mat3(v1, v2, v3));
	if(deltpos < 0){
		add_edges(p1, p2);
		add_edges(p2, p3);
		add_edges(p3, p1);
	}
}

void EnveloppeConvexe::calculateVolume(GLfloat *points)
{

}