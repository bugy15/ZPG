#pragma once

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <glfw3.h>  


class Window
{
private:
	static GLFWwindow * window;

public:
	static GLFWwindow * getInstance();
	~Window();
};

