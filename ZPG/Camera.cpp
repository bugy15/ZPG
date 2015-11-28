#include "Camera.h"
#include "AbstractObserver.h"


Camera * Camera::camera = NULL;

Camera * Camera::getInstance()
{
	if (camera == NULL)
	{
		camera = new Camera();
		return camera;
	}
	return camera;
}

void Camera::setCamera()
{
	this->eye    = vec3(0, 5, 20);
	this->center = vec3(0, 0, -1);
	this->up     = vec3(0, 1, 0);
	this->ProjectionMatrix = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	this->multipler        = vec3(0.5f, 0.5f, 0.03f);
	this->alpha_x          = alpha_y = (float)-1.53;
	this->sensitivity      = (float)  0.02;
	notifyObserver();
}

void Camera::setProjectionMatrix(mat4 ProjectionMatrix)
{
	this->ProjectionMatrix = ProjectionMatrix;
	notifyObserver();
}

void Camera::moveLeft()
{
	eye += (normalize(cross(center, up)));
	notifyObserver();
}

void Camera::moveRight()
{
	eye -= (normalize(cross(center, up)));
	notifyObserver();
}

void Camera::moveUp()
{
	eye += multipler * (normalize(up));
	notifyObserver();
}

void Camera::moveDown()
{
	eye -= multipler * (normalize(up));
	notifyObserver();
}

void Camera::moveFront()
{
	eye += (normalize(center));
	notifyObserver();
}

void Camera::moveBack()
{
	eye -= (normalize(center));
	notifyObserver();
}
void Camera::rotateLeft()
{
	alpha_x += sensitivity;
	center = glm::vec3(cos(alpha_x), cos(alpha_y), sin(alpha_x));
	notifyObserver();
}

void Camera::rotateRight()
{
	alpha_x -= sensitivity;
	center = glm::vec3(cos(alpha_x), cos(alpha_y), sin(alpha_x));
	notifyObserver();
}

void Camera::rotateUp()
{
	if (alpha_y <= -3.14)
		alpha_y = (float)-3.13;

	if (alpha_y >= 0.00)
		alpha_y = (float)-0.01;

	alpha_y += sensitivity;
	center = glm::vec3(cos(alpha_x), cos(alpha_y), sin(alpha_x));
	notifyObserver();
}

void Camera::rotateDown()
{
	if (alpha_y <= -3.14)
		alpha_y = (float)-3.13;

	if (alpha_y >= 0.00)
		alpha_y = (float)-0.01;

	alpha_y -= sensitivity;
	center = glm::vec3(cos(alpha_x), cos(alpha_y), sin(alpha_x));
	notifyObserver();
}

void Camera::registerObserver(AbstractObserver* observer)
{
	this->abstractObservers.push_back(observer);
}

void Camera::removeObserver(AbstractObserver* observer)
{
	this->abstractObservers.remove(observer);
}

void Camera::notifyObserver()
{
	list<AbstractObserver*>::iterator pos = this->abstractObservers.begin();
	while (pos != this->abstractObservers.end())
	{
		((AbstractObserver*)(*pos))->updateCamera(this);
		++pos;
	}
}

mat4 Camera::getProjectionMatrix()
{
	return this->ProjectionMatrix;
}

mat4 Camera::getViewMatrix()
{
	return glm::lookAt(eye, center + eye, up);
}

vec3 Camera::getCameraPosition()
{
	return this->eye;
}

vec3 Camera::getCenter()
{
	return this->center;
}

vec3 Camera::getUp()
{
	return this->up;
}
