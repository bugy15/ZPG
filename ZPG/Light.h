#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <list>
#include <iostream>

#include "AbstractSubject.h"
#include "Object.h"

using namespace std;


class Light : public AbstractSubject
{
private:

	list<AbstractObserver* > abstractObservers;

	Object * object;

	glm::vec4 position;
	glm::vec4 direction;
	glm::vec4 color;
	float angle;
	float intensity;


public:
	Light(Object * object, glm::vec4 position, glm::vec4 direction, glm::vec4 color, float angle, float intensity);
	glm::vec4 getPosition();
	glm::vec4 getDirection();
	glm::vec4 getColor();
	float     getAngle();
	float	  getIntensity();
	Object *  getObject();
	void	  setPosition(glm::vec3 position);
	void	  setDirection(glm::vec4 direction);
	void	  setColor(glm::vec4 color);
	void      setAngle(float angle);
	void      setIntensity(float intensity);
	void      updateObjectPosition();
	void      registerObserver(AbstractObserver * observer);
	void      removeObserver(AbstractObserver * observer);
	void      notifyObserver();
	void      draw();
};

