#ifndef ENVCONVEX
#define ENVCONVEX

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL.h>
#include <string>
#include <sstream>
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

class EnveloppeConvexe{
	private:
		GLfloat *m_vertices;
		std::vector<GLfloat*> m_faces;
		std::vector<GLfloat*> m_edges;

	public:
		EnveloppeConvexe();
		~EnveloppeConvexe();

		void calculateVolume(GLfloat *points);
		void add_edges(glm::vec3 p1,glm::vec3 p2);
		void filter(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 pTest);

}

#endif