#include "Mesh.h"
#include "ObjLoader.h"
#include <vector>
#include "rt3d.h"

using namespace std;

Mesh::Mesh()
{
	m_vertices = NULL;
	m_faces = NULL;
	m_numFaces = 0;
	m_numVertices = 0;
}

Mesh::~Mesh()
{}

void Mesh::init(GLuint numVerts, GLfloat* vertices, GLfloat* colours, GLfloat* normals, GLfloat* texcoords, GLuint indexCount, GLuint* indices)
{
	m_vertices = new float[numVerts*3];
	memcpy(m_vertices,vertices,numVerts*3*sizeof(float));
	m_faces = new unsigned int[indexCount];
	memcpy(m_faces,indices,indexCount*sizeof(unsigned int));
	m_numFaces = indexCount;
	m_numVertices = numVerts;
	m_ID = createMesh(numVerts, vertices, colours, normals, texcoords, indexCount, indices);
}

void Mesh::init(GLuint numVerts, GLfloat* vertices, GLfloat* colours, GLfloat* normals,GLfloat* texcoords)
{
	m_vertices = new float[numVerts*3];
	memcpy(m_vertices,vertices,numVerts*3*sizeof(float));
	m_numVertices = numVerts;
	m_ID = createMesh(numVerts, vertices, colours, normals,texcoords);
}

void Mesh::init(GLuint numVerts, GLfloat* vertices)
{
	m_vertices = new float[numVerts*3];
	memcpy(m_vertices,vertices,numVerts*3*sizeof(float));
	m_numVertices = numVerts;
	m_ID = createMesh(numVerts, vertices);
}

void Mesh::draw()
{
	if(m_faces != NULL)
		drawIndexedMesh(m_ID, m_numFaces, GL_TRIANGLES);
	else
		drawMesh(m_ID, m_numVertices, GL_TRIANGLES); 
}

void Mesh::loadFromObjFile(const char* filename)
{
	stringstream streamName;
	streamName << "Models\\" << filename;

	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> tex_coords;
	vector<GLuint> indices;
	loadObj(streamName.str().c_str(), verts, norms, tex_coords, indices);
	init(verts.size()/3, verts.data(), nullptr, norms.data(), tex_coords.data(), indices.size(), indices.data());
}

unsigned int Mesh::getNumFaces()
{
	return m_numFaces;
}
		
unsigned int Mesh::getNumVertices()
{
	return m_numVertices;
}

float *Mesh::getVertices()
{
	return m_vertices;
}

unsigned int *Mesh::getFaces()
{
	return m_faces;
}

Mesh Mesh::getAlphaShape()
{
	Mesh alphaShape = Mesh();
	alphaShape.m_vertices = m_vertices;
	alphaShape.m_numVertices = m_numVertices;


	return alphaShape;
}

void Mesh::generateAllTetraedreForAlphaShape(std::priority_queue<Tetraedre> *tetraedreList)
{
	for(GLuint i = 0; i < m_numVertices-2; i++)
		for(GLuint j = i+1; j < m_numVertices-1; j++)
			for(GLuint k = j+1; k < m_numVertices; k++)
			{
				tetraedreList.push(getHigherLambdaOfTriangle(i, j, k));
			}
}

Tetraedre getHigherLambdaOfTriangle(GLuint p1, GLuint p2, GLuint p3)
{

}