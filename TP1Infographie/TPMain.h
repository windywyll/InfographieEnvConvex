#ifndef TP_MAIN
#define TP_MAIN

#include <ctime>
#include <vector>
#include <iostream>

#include <SDL.h>

#include <GL/glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class TPMain
{
public :
	static TPMain &getInstance();
	void deleteContext();

	void init();
	void draw();
	void update();
	void run();
	void handleEvents();
	glm::mat4 getViewMatrix(){return m_view;}
	glm::mat4 getProjectionMatrix(){return m_projection;}

	float getElapsedTime();

	static void exitFatalError(char *message);
	
private :
	static TPMain s_instance; //the instance of the singleton class
	SDL_GLContext m_glContext; // OpenGL context handle
    SDL_Window *m_window; // window handle
	bool m_isSetupDone;

	glm::vec3 m_playerLastPosition;

	void setupRC();
	
	TPMain();
	~TPMain();

	float m_timeElapsed;

	bool m_running;

	//size of the window
	int m_windowWidth, m_windowHeight;

	glm::mat4 m_view;
	glm::mat4 m_projection;
};

#endif
