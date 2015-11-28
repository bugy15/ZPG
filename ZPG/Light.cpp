#include "Light.h"
#include "AbstractObserver.h"


Light::Light(Object * object, glm::vec4 position, glm::vec4 direction, glm::vec4 color, float angle, float intensity)
{
	this->object	= object;
	this->position  = position;
	this->direction = direction;
	this->color		= color;
	this->angle		= angle;
	this->intensity = intensity;

	this->updateObjectPosition();
}

glm::vec4 Light::getPosition()
{
	return this->position;
}

glm::vec4 Light::getDirection()
{
	return this->direction;
}

glm::vec4 Light::getColor()
{
	return this->color;
}

float Light::getAngle()
{
	return this->angle;
}

float Light::getIntensity()
{
	return this->intensity;
}

Object * Light::getObject()
{
	return this->object;
}

void Light::setPosition(glm::vec3 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;

	this->notifyObserver();
	this->updateObjectPosition();
}

void Light::setDirection(glm::vec4 direction)
{
	this->direction = direction;
	this->notifyObserver();
}

void Light::setColor(glm::vec4 color)
{
	this->color = color;
	this->notifyObserver();
}

void Light::setAngle(float angle)
{
	this->angle = angle;
	this->notifyObserver();
}

void Light::setIntensity(float intensity)
{
	this->intensity = intensity;
	this->notifyObserver();
}

void Light::updateObjectPosition()
{
	if (this->object != NULL)
		this->object->setPosition(vec3(this->position.x, this->position.y, this->position.z));
}

void Light::registerObserver(AbstractObserver * observer)
{
	this->abstractObservers.push_back(observer);
}

void Light::removeObserver(AbstractObserver * observer)
{
	this->abstractObservers.remove(observer);
}

void Light::notifyObserver()
{
	list<AbstractObserver*>::iterator pos = this->abstractObservers.begin();
	while (pos != this->abstractObservers.end())
	{
		((AbstractObserver*)(*pos))->updateLight(this);
		++pos;
	}
}

void Light::draw()
{
	notifyObserver();
}