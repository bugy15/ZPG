#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <glfw3.h>  
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/glm.hpp>
#include <map>

#include "Shader.h"
#include "Object.h"
#include "Light.h"
#include "Window.h"
#include "Model.h"
#include "Camera.h"
#include "Direction.h"


class Scene 
{

private:
	Window * window;
	Camera * camera;

	Shader * phong;
	Shader * lambert;

	Light  * light;
	Light  * light1;
	Light  * light2;
	Light  * light3;

	Object * object1;
	Object * object2;
	Object * object3;
	Object * object4;

	Model * sphere;
	Model * plane;

	vector<Shader*> listOfShaders;
	vector<Light *> listOfLights;
	vector<Object*> listOfObjects;

	map<string, Shader*> mapOfShaders;

public:
	Scene();
	~Scene();
	void loadModels();
	void createShaders();
	void createObjects();
	void drawObject();
	void createLights();
	void drawLights();
	void draw();
	void moveObject(int id, direction dir);
};

