#pragma once
//GLEW - The OpenGL Extension Wrangler Library
#include <GL/glew.h>
//FreeGLUT Free OpenGL Utility Toolkit 
#include <GL/freeglut.h>
//GLM - OpenGL Mathematics
#include <glm/glm.hpp>
#include <fstream>      // std::ifstream
#include <string>
#include <vector>
#include <istream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace glm;

typedef struct
{
	float Position[3];
	float Normal[3];
	float uv[2];
	float Tangent[4];
} Vertex;

class ObjectLoader
{
	vector <Vertex> data;
	vector <vec4> vertices;
	vector <vec3> normals;
	vector <vec2> uv;
public:
	GLsizei loadObject(char * filename, GLuint &VAO);
};

