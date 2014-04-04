#ifndef ALPHA_SHAPE_H
#define ALPHA_SHAPE_H

#include <queue>
#include <map>
#include <vector>

#include "Mesh.h"
#include "AlphaShape.h"
#include "ListOfTriangleFromPoint.h"

class AlphaShape
{
public:
	AlphaShape(){}
	~AlphaShape(){}

	//calcule l'alpha shape du mesh source et le met dans le mesh alphaShape
	void getAlphaShape(Mesh &source, Mesh &alphaShape);

	//private function and members for alpha shape
private:
	void generateAllTetraedreForAlphaShape();
	void addTetraedreWithHigherLambdaOfTriangle(GLuint p1, GLuint p2, GLuint p3);

	//liste ordonnée selon le plus grand lambda de la liste des point associés à une liste de triangle
	std::priority_queue<ListOfTriangleFromPoint,std::vector<ListOfTriangleFromPoint>,std::greater<ListOfTriangleFromPoint>> m_tetraedreList;

	std::vector<Triangle> m_unusedTriangles;
	std::map<GLfloat*,ListOfTriangleFromPoint> m_tempConstructorMap;

	Mesh *m_tempMesh;
};

#endif