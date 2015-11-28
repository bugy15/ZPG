#include "Application.h"


Application* Application::single = NULL;

Application* Application::getInstance()
{
	if (single == NULL)
	{
		single = new Application();
		return single;
	}
	return single;
}

bool Application::init(int argc, char* argv[])
{
	if (!glfwInit()) 
	{
		return false;
	}

	if (!window->getInstance())
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window->getInstance());
	glfwSwapInterval(1);
	glewInit();

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Running against GLFW %i.%i.%i\n", major, minor, revision);

	// get version info
	const GLubyte * renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte * version  = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	return true;
}

void Application::start_program()
{
	controls = controls->getInstance();
	controls->callBackFunctions(window->getInstance());
	controls->createCamera();
	controls->createScene();
}
Application::~Application()
{
	printf("Destructor ~Application \n");
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
