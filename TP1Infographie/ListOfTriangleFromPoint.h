#ifndef LIST_OF_TRIANGLE_FROM_POINT_H
#define LIST_OF_TRIANGLE_FROM_POINT_H

#include <GL/glew.h>
#include <iostream>
#include <queue>

#include "Tetraedre.h"

class ListOfTriangleFromPoint
{
public:
	ListOfTriangleFromPoint(){}
	~ListOfTriangleFromPoint(){}

	//pour rajouter un thétraedre, on vérifie bien qu'on utilise le même point M
	void addTetraedre(Tetraedre tetraedre){if(&tetraedre.getVertices()[3*3] == m_Point){m_tetraedreList.push(tetraedre); m_higherLambda = m_tetraedreList.top().getLambda();}}

	GLfloat getHigherLambda() {return m_higherLambda;}
	GLfloat *getM(){return m_Point;}
	std::priority_queue<Tetraedre,std::vector<Tetraedre>, std::greater<Tetraedre>> &getTetraedreList(){return m_tetraedreList;}

	bool operator>(const ListOfTriangleFromPoint &other) const{return m_higherLambda > other.m_higherLambda;}
	bool operator<(const ListOfTriangleFromPoint &other) const{return m_higherLambda < other.m_higherLambda;}
private:
	GLfloat m_higherLambda;
	GLfloat *m_Point;//le point M de l'algorithme
	//liste ordonnée de tétraèdre (qui conserve le lamnda entre le triangle et M)
	std::priority_queue<Tetraedre,std::vector<Tetraedre>, std::greater<Tetraedre>> m_tetraedreList;
};

#endif