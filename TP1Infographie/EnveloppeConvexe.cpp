#include "EnveloppeConvexe.h"
#include <iostream>
#include <fstream>

using namespace std;

EnveloppeConvexe::EnveloppeConvexe()
{
	m_vertices = NULL;
	num_vertices = 0;
}

EnveloppeConvexe::~EnveloppeConvexe()
{

}

void EnveloppeConvexe::loadFile(string filename)
{
	ifstream myFile;
	myFile.open(filename);
	if(myFile.is_open()){
		while(!myFile.eof()){
			myFile >> m_vertices[num_vertices*3];
			myFile >> m_vertices[num_vertices*3 + 1];
			myFile >> m_vertices[num_vertices*3 + 2];

			num_vertices ++;
		}
	}

	myFile.close();
}

void EnveloppeConvexe::add_edges(glm::vec3 p1, glm::vec3 p2)
{
	vector<GLfloat>::iterator itx1 = m_edges.begin(), itE = m_edges.end(), ity1, itz1, itx2, ity2, itz2;

	while (itx1 != itE)
	{
		ity1 = itx1+1;
		itz1 = itx1+2;
		itx2 = itx1+3;
		ity2 = itx1+4;
		itz2 = itx1+5;

		if((*itx1==p2.x && *ity1==p2.y && *itz1==p2.z) && (*itx2==p1.x && *ity2==p1.y && *itz2==p1.z))
		{
			m_edges.erase(itx1,itx1+5);
		}
		else
		{
			m_edges.push_back(p1.x);
			m_edges.push_back(p1.y);
			m_edges.push_back(p1.z);
			m_edges.push_back(p2.x);
			m_edges.push_back(p2.y);
			m_edges.push_back(p2.z);
		}
		
		itx1 = itx1+6;

	}

	if(itx1 != itE){
		m_edges.push_back(p1.x);
		m_edges.push_back(p1.y);
		m_edges.push_back(p1.z);
		m_edges.push_back(p2.x);
		m_edges.push_back(p2.y);
		m_edges.push_back(p2.z);
	}
}

void EnveloppeConvexe::filter(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 pTest)
{
	glm::vec3 v1 = p1 - pTest;
	glm::vec3 v2 = p2 - pTest;
	glm::vec3 v3 = p3 - pTest;
	int deltpos = glm::determinant(glm::mat3(v1, v2, v3));
	if(deltpos < 0){
		add_edges(p1, p2);
		add_edges(p2, p3);
		add_edges(p3, p1);
	}
}

void EnveloppeConvexe::calculateVolume()
{
	if(num_vertices >= 4)
	{
		glm::vec3 a (m_vertices[0], m_vertices[1], m_vertices[2]);
		glm::vec3 b (m_vertices[3], m_vertices[4], m_vertices[5]);
		glm::vec3 c (m_vertices[6], m_vertices[7], m_vertices[8]);
		glm::vec3 d (m_vertices[9], m_vertices[10], m_vertices[11]);

		GLuint ai = 0, bi, ci, di = 3;

		if(glm::determinant(glm::mat3(d-a, d-b, d-c)) > 0.0)
		{
			bi = 1;
			ci = 2;
		}
		else
		{
			bi = 2;
			ci = 1;
		}

		m_faces.push_back(ai);
		m_faces.push_back(bi);
		m_faces.push_back(ci);

		m_faces.push_back(ci);
		m_faces.push_back(bi);
		m_faces.push_back(di);

		m_faces.push_back(ai);
		m_faces.push_back(ci);
		m_faces.push_back(di);

		for(int i = 12; i<(num_vertices-1)*3; i = i+3)
		{
			glm::vec3 test (m_vertices[i], m_vertices[i+1], m_vertices[i+2]);

			vector<GLuint>::iterator it = m_faces.begin(), itE = m_faces.end(), it2, it3;

			while (it != itE)
			{
				it2 = it+1;
				it3 = it+2;

				glm::vec3 j(m_vertices[*it], m_vertices[*it+1], m_vertices[*it+2]);
				glm::vec3 k(m_vertices[*it2], m_vertices[*it2+1], m_vertices[*it2+2]);
				glm::vec3 l(m_vertices[*it3], m_vertices[*it3+1], m_vertices[*it3+2]);

				filter(j,k,l,test);

				m_faces.push_back(i/3);
				m_faces.push_back(*it);
				m_faces.push_back(*it2);

				it = it+3;
			}
		}
	}
}

void EnveloppeConvexe::displayTriangles()
{
	vector<GLuint>::iterator it = m_faces.begin(), itE = m_faces.end(), it2, it3;

	while (it != itE)
	{
		it2 = it+1;
		it3 = it+2;
		cout << *it << ", " << *it2 << ", " << *it3 << endl;
		it = it+3;
	}
}

void EnveloppeConvexe::printObj(string filename)
{
	ofstream myFile;
	myFile.open(filename);

	for(int i = 0; i < (num_vertices-1)*3; i = i+3)
	{
		myFile << "v " << m_vertices[i] << " " << m_vertices[i +1] << " " << m_vertices[i + 2] << endl;
	}

	myFile << endl;

	vector<GLuint>::iterator it = m_faces.begin(), itE = m_faces.end(), it2, it3;
	while (it != itE)
	{
		it2 = it+1;
		it3 = it+2;
		myFile << "f " << *it << " " << *it2 << " " << *it3 << endl;
		it = it+3;
	}
}