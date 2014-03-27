#include "Tetraedre.h"
#include "Triangle.h"

void Tetraedre::computeSphereCenter()
{
	//||MO||² + 2y(MO.N) + y² = ||AO||² + 2y(AO.N) + y² <=> 2y(MO.N - AO.N) = ||AO||² - ||MO||² <=> y = (||AO||² - ||MO||²)/2(MO - AO).N
	//avec O centre du cercle circnscrit de ABC, M quatrième point ud tétraèdre et, y (lambda) distance entre
	Triangle triangle(glm::mat3(m_vertices[1],m_vertices[2],m_vertices[3]));
	glm::vec3 vecAO = triangle.getCircleCenter() - m_vertices[0];
	glm::vec3 vecMO = triangle.getCircleCenter() - m_vertices[3];
	m_lambda = (1/2) * (vecAO.length() * vecAO.length() - vecMO.length() * vecMO.length())/glm::dot((vecMO- vecAO),triangle.getNormal());
}