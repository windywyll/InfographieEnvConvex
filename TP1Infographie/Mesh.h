#ifndef MESH
#define MESH

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL.h>
#include <string>
#include <sstream>
#include <queue>

#include "Tetraedre.h"

class Mesh{
private:
	GLuint m_ID;
	unsigned int m_numFaces;
	unsigned int m_numVertices;
	GLfloat *m_vertices;
	GLuint *m_faces;

public:
	Mesh();
	~Mesh();

	void init(GLuint numVerts, GLfloat* vertices, GLfloat* colours, GLfloat* normals, GLfloat* texcoords, GLuint indexCount, GLuint* indices);
	void init(GLuint numVerts, GLfloat* vertices, GLfloat* colours, GLfloat* normals,GLfloat* texcoords);
	void init(GLuint numVerts, GLfloat* vertices);
	void loadFromObjFile(const char* filename);
	void draw();

	unsigned int getNumFaces();
	unsigned int getNumVertices();
	float *getVertices();
	unsigned int *getFaces();
	GLuint getID();

	Mesh getAlphaShape();

	//private function for alpha shape
private:
	void Mesh::generateAllTetraedreForAlphaShape(std::priority_queue<Tetraedre> * tetraedreList);
	Tetraedre getHigherLambdaOfTriangle(GLuint p1, GLuint p2, GLuint p3);
};
#endif