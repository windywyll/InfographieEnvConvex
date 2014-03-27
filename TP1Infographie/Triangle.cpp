#include "Triangle.h"


void Triangle::computeCircleCenter()
{
	//OA = IcA - yVc
	//OC = IcC - yVc
	//y = 1/2 * (||IcC||² - ||IcA||²)/((IcA - IcC).Vc)
	//avec O centre du cercle circonsrit, |y| (lambda) le rayon du cercle le centre , Ic centre de de la face AB et Vc vecteur de la médiatrice
	computeNormal();
	glm::mat2x3 PerpendicularBisector = computePerpendicularBisector(0, 1);
	glm::vec3 vecIcC = m_vertices[2] - PerpendicularBisector[0];
	glm::vec3 vecIcA = m_vertices[0] - PerpendicularBisector[0];
	GLfloat lambda = (1/2) * (vecIcC.length() * vecIcC.length() - vecIcA.length() * vecIcA.length())/glm::dot((vecIcA - vecIcC),PerpendicularBisector[1]);
	m_circleCenter = m_vertices[0] + vecIcA - PerpendicularBisector[0] + PerpendicularBisector[1] * lambda;//not sure
}

void Triangle::computeNormal()
{
	glm::vec3 v1,v2;
	v1 = m_vertices[1] - m_vertices[0];
	v2 = m_vertices[2] - m_vertices[1];
	m_normal = 
		glm::normalize(
			glm::cross(v1,v2));
}

glm::mat2x3 Triangle::computePerpendicularBisector(GLuint p1, GLuint p2)
{
	glm::vec3 point = glm::vec3((m_vertices[p1] + m_vertices[p2])/2.0f);
	glm::vec3 direction = 
		glm::normalize(
			glm::cross(m_normal,
				glm::vec3(m_vertices[p2] - m_vertices[p1])));
	return glm::mat2x3(point,direction);
}

