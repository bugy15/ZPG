#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <glfw3.h>  
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Camera.h"
#include "Scene.h"
#include "Direction.h"


class Controls 
{
private:
	static Controls * controls;
	Camera * camera;
	Scene  * scene;

	int    window_height = 480;
	bool   a = true;
	bool   state  = false, move = false;
	double mouseMoveX, mouseMoveY;
	GLuint idOfObject;

	void   key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void   error_callback(int error, const char * description);
	void   window_size_callback(GLFWwindow * window, int width, int height);
	void   cursor_pos_callback(GLFWwindow * window, double mouseX, double mouseY);
	void   mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
	void   window_focus_callback(GLFWwindow * window, int focused);
	void   window_iconify_callback(GLFWwindow * window, int iconified);
	void   scroll_callback(GLFWwindow * window, double xoffset, double yoffset);
	void   keyboardFunction(int Key, int X, int Y);
	GLuint stencilBuffer();

public:
	static Controls * Controls::getInstance();
	void callBackFunctions(GLFWwindow * window);
	void createCamera();
	void createScene();

};
