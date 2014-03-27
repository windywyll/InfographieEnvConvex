#ifndef TETRAEDRE_H
#define TETRAEDRE_H

#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Tetraedre
{
public:
	Tetraedre(){m_vertices = glm::mat4x3(0.0);}
	Tetraedre(GLfloat *vertices){setVertices(vertices);}
	Tetraedre(glm::mat4x3 vertices){setVertices(vertices);}
	~Tetraedre(){}

	void setVertices(GLfloat *vertices){if(vertices != NULL) {m_vertices = glm::mat4x3(vertices); computeSphereCenter();}}
	void setVertices(glm::mat4x3 vertices){m_vertices = vertices; computeSphereCenter();}
	GLfloat *getVertices(){return glm::value_ptr(m_vertices);}
	glm::mat4x3 getVerticesMatrix(){return m_vertices;}
	GLfloat getlambda(){return m_lambda;}

	void computeSphereCenter();

	bool operator<(Tetraedre & other){return m_lambda < other.m_lambda;}
	bool operator>(Tetraedre & other){return m_lambda > other.m_lambda;}

private :
	glm::mat4x3 m_vertices;
	GLfloat m_lambda;
};

#endif