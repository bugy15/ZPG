#include "Window.h"


GLFWwindow * Window::window = NULL;

GLFWwindow * Window::getInstance()
{
	if (window == NULL)
	{
		window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
		return window;
	}
	return window;
}

Window::~Window()
{
	glfwDestroyWindow(window);
}