#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Triangle
{
public:
	Triangle(){m_vertices = glm::mat3(0.0);}
	Triangle(GLfloat *vertices){setVertices(vertices);}
	Triangle(glm::mat3 vertices){setVertices(vertices);}
	~Triangle(){}

	
	void setVertices(GLfloat *vertices){if(vertices != NULL) {m_vertices = glm::mat3(vertices); computeCircleCenter();}}
	void setVertices(glm::mat3 vertices){m_vertices = vertices; computeCircleCenter();}
	GLfloat *getVertices(){return glm::value_ptr(m_vertices);}
	glm::mat3 getVerticesMatrix(){return m_vertices;}
	glm::vec3 getCircleCenter(){return m_circleCenter;}
	glm::vec3 getNormal(){return m_normal;}

private:
	glm::mat3 m_vertices;
	glm::vec3 m_circleCenter;
	glm::vec3 m_normal;

	void computeCircleCenter();
	void computeNormal();
	glm::mat2x3 computePerpendicularBisector(GLuint p1, GLuint p2);
};

#endif
