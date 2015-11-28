#include "Controls.h"


Controls * Controls::controls = NULL;

Controls * Controls::getInstance()
{
	if (controls == NULL)
	{
		controls = new Controls();
		return controls;
	}
	return controls;
}

void Controls::keyboardFunction(int Key, int X, int Y)
{
	switch (Key)
	{
	case 87:
		camera->moveFront();
		break;
	case 83:
		camera->moveBack();
		break;
	case 65:
		camera->moveRight();
		break;
	case 68:
		camera->moveLeft();
		break;
	case 341:
		camera->moveDown();
		break;
	case 32:
		camera->moveUp();
		break;

	default:
		break;
	}
}

void Controls::callBackFunctions(GLFWwindow * window)
{
	glfwSetErrorCallback([](int error, const char* description) -> void {Controls::getInstance()->error_callback(error, description); });
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {Controls::getInstance()->key_callback(window, key, scancode, action, mods); });
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {Controls::getInstance()->window_size_callback(window, width, height); });
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos) -> void {Controls::getInstance()->cursor_pos_callback(window, mouseXPos, mouseYPos); });
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) -> void {Controls::getInstance()->mouse_button_callback(window, button, action, mods); });
	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) -> void {Controls::getInstance()->window_focus_callback(window, focused); });
	glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified) -> void {Controls::getInstance()->window_iconify_callback(window, iconified); });
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) -> void{Controls::getInstance()->scroll_callback(window, xoffset, yoffset); });
}

void Controls::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Controls::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	keyboardFunction(key, action, 0);

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controls::window_size_callback(GLFWwindow* window, int width, int height)
{
	window_height = height;
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
	camera->setProjectionMatrix(glm::perspective(45.0f, (float)(width / height), 0.1f, 100.0f));
}

void Controls::cursor_pos_callback(GLFWwindow* window, double x, double y)
{
	if (state)
	{
		if (mouseMoveX < x)
			camera->rotateLeft();
		if (mouseMoveX > x)
			camera->rotateRight();
		if (mouseMoveY < y)
			camera->rotateDown();
		if (mouseMoveY > y)
			camera->rotateUp();
	}

	if (move)
	{
		if (mouseMoveX < x)
			scene->moveObject(idOfObject, LEFT);
		if (mouseMoveX > x)
			scene->moveObject(idOfObject, RIGHT);
		if (mouseMoveY < y)
			scene->moveObject(idOfObject, DOWN);
		if (mouseMoveY > y)
			scene->moveObject(idOfObject, UP);
	}

	mouseMoveY = y;
	mouseMoveX = x;
}

void Controls::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		state = true;
	else
		state = false;

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		idOfObject = this->stencilBuffer();
		move = true;
	}
	else
		move = false;
}

void Controls::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (move)
	{
		if (yoffset == 1)
			scene->moveObject(idOfObject, FORWARD);
		else
			scene->moveObject(idOfObject, BACKWARD);
	}
	else
	{
		if (yoffset == 1)
			camera->moveFront();
		else
			camera->moveBack();
	}
}

void Controls::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback %d \n", focused);
}

void Controls::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback %d \n", iconified);
}

GLuint Controls::stencilBuffer()
{
	GLbyte color[4]; GLfloat depth; GLuint index;
	int newy = window_height - (int)mouseMoveY - 10;
	glReadPixels((GLint)mouseMoveX, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels((GLint)mouseMoveX, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels((GLint)mouseMoveX, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
	printf("Clicked on pixel %i, %i, color %02hhx%02hhx%02hhx%02hhx, depth%f, stencil index %u \n", (int)mouseMoveX, (int)mouseMoveY, color[0], color[1], color[2], color[3], depth, index);

	return index;
}

void Controls::createScene()
{
	scene = new Scene();
	scene->draw();
}

void Controls::createCamera()
{
	camera = camera->getInstance();
}
