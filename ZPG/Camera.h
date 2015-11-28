#pragma once

#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "AbstractSubject.h"

using namespace std;
using namespace glm;

class Camera : public AbstractSubject
{
private:
	static Camera * camera;
	list<AbstractObserver* > abstractObservers;

	mat4  ProjectionMatrix;
	vec3  eye, center, up, multipler;
	float alpha_x, alpha_y, sensitivity;
	
public:
	static Camera * Camera::getInstance();

	void setCamera();
	void setProjectionMatrix(mat4 ProjectionMatrix);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void moveFront();
	void moveBack();
	void rotateLeft();
	void rotateRight();
	void rotateUp();
	void rotateDown();
	void registerObserver(AbstractObserver* observer);
	void removeObserver(AbstractObserver* observer);
	void notifyObserver();
	mat4 getProjectionMatrix();
	mat4 getViewMatrix();
	vec3 getCameraPosition();
	vec3 getCenter();
	vec3 getUp();
};

