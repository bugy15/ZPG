#include "Object.h"


Object::Object(GLuint ID, string nameOfShader, Model * model, vec4 color, vec3 position, vec3 scale, vec3 rotate, float angle)
{

	this->model = model;

	this->ID           = ID;
	this->nameOfShader = nameOfShader;
	this->color        = color;
	this->ModelMatrix  = glm::scale(glm::mat4(1.0f), scale);
	this->ModelMatrix  = glm::rotate(this->ModelMatrix, angle, rotate);
	this->ModelMatrix  = glm::translate(this->ModelMatrix, position);
	this->multipler    = vec3(0.2, 0.2, 0.2);
}

GLsizei Object::getVao()
{
	return this->model->getVao();
}

GLsizei Object::getCount()
{
	return this->model->getCount();
}

string Object::getNameOfShader()
{
	return this->nameOfShader;
}

mat4 Object::getModelMatrix()
{
	return this->ModelMatrix;
}

vec4 Object::getColor()
{
	return this->color;
}

vec3 Object::getPosition()
{
	return vec3(this->ModelMatrix[3]);
}

GLuint Object::getId()
{
	return this->ID;
}

void Object::setColor(vec4 color)
{
	this->color = color;
}

void Object::setNameOfShader(string nameOfShader)
{
	this->nameOfShader = nameOfShader;
}

void Object::setPosition(vec3 position)
{
	this->ModelMatrix = translate(mat4(1.0f), position);
}

void Object::move(direction dir, vec3 center, vec3 up)
{

	vec3 moveHorizontal = multipler * normalize(cross(center, up));
	vec3 moveVertical   = multipler * normalize(up);
	vec3 moveDepthical  = normalize(center);

	switch (dir)
	{
		case LEFT:
			this->ModelMatrix = translate(this->ModelMatrix, moveHorizontal);
			break;
		case RIGHT:
			this->ModelMatrix = translate(this->ModelMatrix, -moveHorizontal);
			break;
		case UP:
			this->ModelMatrix = translate(this->ModelMatrix, moveVertical);
			break;
		case DOWN:
			this->ModelMatrix = translate(this->ModelMatrix, -moveVertical);
			break;
		case FORWARD:
			this->ModelMatrix = translate(this->ModelMatrix, moveDepthical);
			break;
		case BACKWARD:
			this->ModelMatrix = translate(this->ModelMatrix, -moveDepthical);
			break;
	}
}

Object::~Object()
{
	delete model;
}