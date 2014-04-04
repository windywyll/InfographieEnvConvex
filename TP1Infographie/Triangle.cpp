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
	GLfloat lambda = (1/2) * ((vecIcC.x * vecIcC.x + vecIcC.y * vecIcC.y + vecIcC.z * vecIcC.z) - (vecIcA.x * vecIcA.x + vecIcA.y * vecIcA.y + vecIcA.z * vecIcA.z))/glm::dot((vecIcA - vecIcC),PerpendicularBisector[1]);
	m_circleCenter = m_vertices[0] + vecIcA - PerpendicularBisector[0] + PerpendicularBisector[1] * lambda;//not sure
}

void Triangle::computeNormal()//calcule la normale du triangle
{
	glm::vec3 v1,v2;
	v1 = m_vertices[1] - m_vertices[0];
	v2 = m_vertices[2] - m_vertices[1];
	m_normal = 
		glm::normalize(
			glm::cross(v1,v2));//normalisation du produit vectoriel de deux des vecteurs du triangle
}

glm::mat2x3 Triangle::computePerpendicularBisector(GLuint p1, GLuint p2)//clacul d'un médiatrice du triangle
{
	glm::vec3 point = glm::vec3((m_vertices[p1] + m_vertices[p2])/2.0f);
	glm::vec3 direction = 
		glm::normalize(
			glm::cross(m_normal,
				glm::vec3(m_vertices[p2] - m_vertices[p1])));
	return glm::mat2x3(point,direction);
}

void Triangle::setVertices(std::vector<GLuint> pointID, GLfloat *vertices)
{
	if(pointID.size() == 3)
	{
		m_pointID = pointID;
		if(vertices != nullptr)
		{
			m_vertices = glm::mat3(vertices[0],vertices[1],vertices[2],vertices[3],vertices[4],vertices[5],vertices[6],vertices[7],vertices[8]);
			computeCircleCenter();//quand les points changent, on recalcule le centre de la sphère circonscrite
		}
	}
}

void Triangle::setVertices(std::vector<GLuint> pointID, glm::mat3 vertices)
{
	if(pointID.size() == 3)
	{
		m_vertices = vertices; 
		computeCircleCenter();//quand les points changent, on recalcule le centre de la sphère circonscrite
	}
}