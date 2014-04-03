#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Triangle
{
public:
	Triangle(){m_vertices = glm::mat3(0.0);}
	Triangle(std::vector<GLuint> pointID, GLfloat *vertices){setVertices(pointID, vertices);}
	Triangle(std::vector<GLuint> pointID, glm::mat3 vertices){setVertices(pointID, vertices);}
	~Triangle(){}

	
	void setVertices(std::vector<GLuint> pointID, GLfloat *vertices = nullptr);
	void setVertices(std::vector<GLuint> pointID, glm::mat3 vertices);
	GLfloat *getVertices(){return glm::value_ptr(m_vertices);}
	glm::mat3 getVerticesMatrix(){return m_vertices;}
	glm::vec3 getCircleCenter(){return m_circleCenter;}
	glm::vec3 getNormal(){return m_normal;}
	std::vector<GLuint> getPointsRef(){return m_pointID;}

private:
	std::vector<GLuint> m_pointID;
	glm::mat3 m_vertices;
	glm::vec3 m_circleCenter;
	glm::vec3 m_normal;

	//fonctions pour calculer le centre du cercle circonscrit au triangle
	void computeCircleCenter();
	void computeNormal();
	glm::mat2x3 computePerpendicularBisector(GLuint p1, GLuint p2);
};

#endif
