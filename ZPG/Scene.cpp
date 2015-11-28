#include "Scene.h"


Scene::Scene()
{
	camera = camera->getInstance();

	this->loadModels();
	this->createObjects();
	this->createLights();
	this->createShaders();

	camera->setCamera();
}

void Scene::loadModels()
{
	sphere = new Model("Models/sphere.obj");
	plane  = new Model("Models/plane.obj");
}

void Scene::createShaders()
{
	listOfShaders.push_back(phong   = new Shader(camera, "Shaders/Phong-VS.glsl", "Shaders/Phong-FS.glsl"));
	listOfShaders.push_back(lambert = new Shader(camera, "Shaders/Lambert-VS.glsl", "Shaders/Lambert-FS.glsl"));

	mapOfShaders["phong"]   = phong;
	mapOfShaders["lambert"] = lambert;

	for (vector<Shader*>::const_iterator it = listOfShaders.begin(); it != listOfShaders.end(); ++it)
	{
		for (vector<Light*>::const_iterator itt = listOfLights.begin(); itt != listOfLights.end(); ++itt)
		{
			(*it)->setLight((*itt));
		}
	}
}

void Scene::createObjects()
{
	GLuint i = 0;
	listOfObjects.push_back(object3 = new Object(i++, "phong", plane,   vec4(0, 0, 1, 1), vec3(0, 0, 20), vec3(2, 1, 2), vec3(1, 1, 1), 0));
	listOfObjects.push_back(object1 = new Object(i++, "phong", sphere , vec4(1, 0, 1, 1), vec3(0, 0, 0), vec3(1, 1, 1), vec3(1, 1, 1), 0));
	listOfObjects.push_back(object2 = new Object(i++, "phong", sphere,  vec4(1, 0, 0, 1), vec3(0, 0, 0), vec3(1, 1, 1), vec3(1, 1, 1), 0));
}

void Scene::drawObject()
{
	GLuint i = 0;

	glClear(GL_STENCIL_BUFFER_BIT);
	for (vector<Object*>::const_iterator it = listOfObjects.begin(); it != listOfObjects.end(); ++it)
	{
		mapOfShaders[(*it)->getNameOfShader()]->setShader();
		glBindVertexArray((*it)->getVao());
		mapOfShaders[(*it)->getNameOfShader()]->setModelData((*it)->getModelMatrix(), (*it)->getColor());
		glStencilFunc(GL_ALWAYS, i++, 0xFF);
		glDrawArrays(GL_TRIANGLES, 0, (*it)->getCount());
	}
}

void Scene::createLights()
{
	listOfLights.push_back(light  = new Light(NULL,    vec4(5, 5, 5, 0),    vec4(0, 0, -1, 1), vec4(1, 1, 1, 1), 10, 60));
	//listOfLights.push_back(light3 = new Light(NULL,    vec4(5, 5, 5, 2),    vec4(0, -1, 0, 0), vec4(1, 0, 1, 1), 50, 100));
	listOfLights.push_back(light1 = new Light(object1, vec4(15, 5, -15, 1), vec4(0, -1, 0, 1), vec4(1, 1, 1, 1), 30, 50));
	listOfLights.push_back(light2 = new Light(object2, vec4(0, 5, 0, 2),    vec4(0, 0, -1, 1), vec4(1, 1, 1, 1), 99, 100));
	
}

void Scene::drawLights()
{
	for (vector<Light*>::const_iterator it = listOfLights.begin(); it != listOfLights.end(); ++it)
	{
		(*it)->draw();
	}
}

void Scene::draw()
{
	while (!glfwWindowShouldClose(window->getInstance()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		this->drawObject();
		this->drawLights();

		glfwPollEvents();
		glfwSwapBuffers(window->getInstance());
	}
}

void Scene::moveObject(int id, direction dir)
{
	for (vector<Object*>::const_iterator it = listOfObjects.begin(); it != listOfObjects.end(); ++it)
	{
		if ((*it)->getId() == id && id != 0)
			(*it)->move(dir, camera->getCenter(), camera->getUp());

		for (vector<Light*>::const_iterator it = listOfLights.begin(); it != listOfLights.end(); ++it)
		{
			if ((*it)->getObject() != NULL && (*it)->getObject()->getId() == id)
				(*it)->setPosition((*it)->getObject()->getPosition());
		}
	}
}
Scene::~Scene()
{
	phong->deleteShader();
	lambert->deleteShader();
	delete light;
	delete light1;
	delete light2;
	delete object1;
	delete object2;
	delete object3;
	delete camera;
	delete window;
	delete sphere;
	delete plane;
	delete phong;
	delete lambert;
}