#include "TPMain.h"

#define PI 3.141592f

using namespace std;

////////////////
//STATIC MEMBERS
////////////////

// Something went wrong - print error message and quit
void TPMain::exitFatalError(char *message)
{
    cout << message << " " << endl;
    cout << SDL_GetError();
    SDL_Quit();
	cin.get();
    exit(1);
}

TPMain &TPMain::getInstance()
{
	static TPMain s_instance;
	if(!s_instance.m_isSetupDone)
		s_instance.setupRC();
	return s_instance;
}

void TPMain::deleteContext()
{
	if(m_isSetupDone)
	{
		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_window);
		m_isSetupDone = false;
	}
	SDL_Quit();
	m_isSetupDone = false;
}

/////////////////
//INSTANCE MEMBER
/////////////////

void TPMain::setupRC()
{
	/* Initialize default output device */
	//if (!BASS_Init(-1,44100,0,0,NULL))
	//	cout << "Can't initialize device";

    if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize video
        exitFatalError("Unable to initialize SDL"); 
	  
    // Request an OpenGL 3.0 context.
    // If you request a context not supported by your drivers,
    // no OpenGL context will be created
	
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
 
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on

    // Turn on x4 multisampling anti-aliasing (MSAA)
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering

	m_windowWidth = 800;
	m_windowHeight = 600;

    // Create 800x600 window
    m_window = SDL_CreateWindow("SDL/GLM/OpenGL Real Time 3D Demo",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if (!m_window) // Check window was created OK
        exitFatalError("Unable to create window");

    // Create opengl context and attach to window
    m_glContext = SDL_GL_CreateContext(m_window);
    // set swap buffers to sync with monitor's vertical refresh rate
    SDL_GL_SetSwapInterval(1);

	GLenum err = glewInit();
	// Required on Windows... init GLEW to access OpenGL beyond 1.1
	// remove on other platforms
	if (GLEW_OK != err)
	{	// glewInit failed, something is seriously wrong.
		cout << "glewInit failed, aborting." << endl;
		exit (1);
	}
	m_isSetupDone = true;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

TPMain::TPMain()
{m_isSetupDone = false;}


TPMain::~TPMain()
{
	if(m_isSetupDone)
	{
		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_window);
		m_isSetupDone = false;
		SDL_Quit();
	}
	
}

void TPMain::init()
{
	///////
	//MESH
	///////

	/////////////
	//REAL OBJECT
	/////////////

	/////////
	//PLAYER
	/////////


	/////////
	//SKY BOX
	/////////

	///////
	//LIGHT
	///////

	//SDL_ShowCursor(SDL_DISABLE);
}

void TPMain::draw()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.5, 0.5, 0.5, 1.0); // set background colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	////////////////
	//DRAWING OJECTS
	////////////////

	SDL_GL_SwapWindow(m_window); // swap buffers
}

void TPMain::update()
{

}

void TPMain::handleEvents()
{
	SDL_Event sdlEvent;	// variable to detect SDL events

	while(SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.type == SDL_QUIT)
			m_running = false;
	}
}

void TPMain::run()
{
	clock_t currentTime, LastTime;
	currentTime = LastTime = clock();
	m_running = true;
	while (m_running)
	{
		currentTime = clock();
		m_timeElapsed = ((float)(currentTime - LastTime)/CLOCKS_PER_SEC);
		LastTime = currentTime;
		handleEvents();
		update();
		draw();
	}
}

float TPMain::getElapsedTime()
{
	return m_timeElapsed;
}
