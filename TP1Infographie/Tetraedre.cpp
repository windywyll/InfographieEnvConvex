#include "Tetraedre.h"
#include "Triangle.h"

void Tetraedre::computeSphereCenter()
{
	//||MO||² + 2y(MO.N) + y² = ||AO||² + 2y(AO.N) + y² <=> 2y(MO.N - AO.N) = ||AO||² - ||MO||² <=> y = (||AO||² - ||MO||²)/2(MO - AO).N
	//avec O centre du cercle circnscrit de ABC, M quatrième point ud tétraèdre et, y (lambda) distance entre
	Triangle triangle(std::vector<GLuint>(m_pointID.begin(), m_pointID.begin()+3),glm::mat3(m_vertices[1],m_vertices[2],m_vertices[3]));
	glm::vec3 vecAO = triangle.getCircleCenter() - m_vertices[0];
	glm::vec3 vecMO = triangle.getCircleCenter() - m_vertices[3];
	m_lambda = (1/2) * ((vecAO.x * vecAO.x + vecAO.y * vecAO.y + vecAO.z * vecAO.z) - (vecMO.x * vecMO.x + vecMO.y * vecMO.y + vecMO.z * vecMO.z))/glm::dot((vecMO - vecAO),triangle.getNormal());
}

void Tetraedre::setVertices(std::vector<GLuint> pointID, GLfloat *vertices)
{
	if(pointID.size() == 4)
	{
		m_pointID = pointID;
		if(vertices != nullptr)
		{
			m_vertices = glm::mat4x3(vertices[0],vertices[1],vertices[2],vertices[3],vertices[4],vertices[5],vertices[6],vertices[7],vertices[8],vertices[9],vertices[10],vertices[11]);
			computeSphereCenter();//quand les points changent, on recalcule le centre de la sphère circonscrite
		}
	}
}

void Tetraedre::setVertices(std::vector<GLuint> pointID, glm::mat4x3 vertices)
{
	if(pointID.size() == 4)
	{
		m_vertices = vertices; 
		computeSphereCenter();//quand les points changent, on recalcule le centre de la sphère circonscrite
	}
}