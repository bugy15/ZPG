#pragma once

#include<string.h>
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<glm/gtc/type_ptr.hpp> 
#include<glm/gtc/matrix_transform.hpp>

#include "ShaderLoader.h"
#include "AbstractObserver.h"

using namespace glm;


class Shader : public ShaderLoader, public AbstractObserver
{
private:
	Camera * camera;
	Light  * light;

	struct lightSource{
		vec4  position;
		vec4  direction;
		vec4  color;
		float angle;
		float intensity;
	};

	lightSource Lights[3];

	GLuint programID;
	mat4   ModelMatrix, ViewMatrix, ProjectionMatrix;
	mat3   NormalMatrix;
	vec4   color;
	vec3   cameraPosition, center;
	 
public:
		   Shader(Camera * camera, const char * vertexFile, const char * fragmentFile);
	       ~Shader();
	GLint  getUniformID(const GLchar * name);
	void   loadShader(const char * vertexFile, const char * fragmentFile);
	void   setShader();
	void   setCamera(Camera *camera);
	void   updateCamera(Camera * camera);
	void   setLight(Light * light);
	void   updateLight(Light * light);
	void   setModelData(mat4 &ModelMatrix, vec4 color);

	void  setData();
};

