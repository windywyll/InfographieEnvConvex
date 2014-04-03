#ifndef TETRAEDRE_H
#define TETRAEDRE_H

#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Tetraedre
{
public:
	Tetraedre(){m_vertices = glm::mat4x3(0.0);}
	Tetraedre(std::vector<GLuint> pointID, GLfloat *vertices = nullptr){setVertices(pointID, vertices);}
	Tetraedre(std::vector<GLuint> pointID, glm::mat4x3 vertices){setVertices(pointID, vertices);}
	~Tetraedre(){}

	void setVertices(std::vector<GLuint> pointID, GLfloat *vertices = nullptr);
	void setVertices(std::vector<GLuint> pointID, glm::mat4x3 vertices);
	GLfloat *getVertices(){return glm::value_ptr(m_vertices);}
	glm::mat4x3 getVerticesMatrix(){return m_vertices;}
	GLfloat getLambda(){return m_lambda;}
	std::vector<GLuint> getPointsRef(){return m_pointID;}

	//fonction utilisées pour trier les objets dans une priority_queue
	bool operator<(const Tetraedre &other) const{return m_lambda < other.m_lambda;}
	bool operator>(const Tetraedre &other) const{return m_lambda > other.m_lambda;}

private :
	//fonction pour calculer le centre de la sphère circonscite
	void computeSphereCenter();

	std::vector<GLuint> m_pointID;
	glm::mat4x3 m_vertices;
	GLfloat m_lambda;
};

#endif