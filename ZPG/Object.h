#pragma once

#include <map>
#include<glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "Direction.h"


class Object
{
private:
	Model * model;

	GLsizei vao;
	GLsizei count;
	GLuint  ID;
	string  nameOfShader;
	mat4    ModelMatrix;
	vec4	color;
	vec3    multipler;
	
public:
	Object(GLuint ID, string nameOfShader, Model * model, vec4 color, vec3 position, vec3 scale, vec3 rotate, float angle);
	GLsizei getVao();
	GLsizei getCount();
	string  getNameOfShader();
	mat4    getModelMatrix();
	vec4    getColor();
	vec3    getPosition();
	GLuint  getId();
	void    setColor(vec4 color);
	void    setNameOfShader(string nameOfShader);
	void    setPosition(vec3 position);
	void    move(direction dir, vec3 center, vec3 up);
	~Object();
};

