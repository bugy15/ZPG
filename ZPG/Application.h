#pragma once

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <glfw3.h>  

#include "Controls.h"
#include "Window.h"


class Application
{
private:
	static Application * single;
	Window   * window;
	Controls * controls;

public:
	static Application * getInstance();
	bool init(int argc, char* argv[]);
	void start_program();
	~Application();
};

