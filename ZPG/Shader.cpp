#include "Shader.h"
#include "Camera.h"
#include "Light.h"


Shader::Shader(Camera * camera, const char * vertexFile, const char * fragmentFile)
{
	this->camera = camera;
	camera->registerObserver(this);
	this->programID = this->ShaderLoader::loadShader(vertexFile, fragmentFile);
}

Shader::~Shader()
{
	this->deleteShader();
}

GLint Shader::getUniformID(const GLchar * name)
{
	return glGetUniformLocation(programID, name);
}

void Shader::setShader()
{
	glUseProgram(this->programID);
}

void Shader::setCamera(Camera * camera)
{
	this->camera = camera;
	camera->registerObserver(this);
}

void Shader::updateCamera(Camera * camera)
{
	this->ViewMatrix       = camera->getViewMatrix();
	this->ProjectionMatrix = camera->getProjectionMatrix();
	this->cameraPosition   = camera->getCameraPosition();
	this->center           = camera->getCenter();
}

void Shader::setLight(Light * light)
{
	this->light = light;
	light->registerObserver(this);
}

void Shader::updateLight(Light * light)
{
	glm::vec4 pos = light->getPosition();
	int id        = (int) pos.w;

	this->Lights[id].position  = light->getPosition();
	this->Lights[id].direction = light->getDirection();
	this->Lights[id].color     = light->getColor();
	this->Lights[id].angle     = light->getAngle();
	this->Lights[id].intensity = light->getIntensity();
}

void Shader::setModelData(mat4 &ModelMatrix, vec4 color)
{
	this->ModelMatrix  = ModelMatrix;
	this->NormalMatrix = transpose(inverse(glm::mat3(ModelMatrix)));
	this->color = color;
	this->setData();
}

void Shader::setData()
{
	glUniformMatrix4fv(getUniformID("ModelMatrix"),      1, GL_FALSE, value_ptr(this->ModelMatrix));
	glUniformMatrix4fv(getUniformID("ViewMatrix"),       1, GL_FALSE, value_ptr(this->ViewMatrix));
	glUniformMatrix4fv(getUniformID("ProjectionMatrix"), 1, GL_FALSE, value_ptr(this->ProjectionMatrix));
	glUniformMatrix3fv(getUniformID("NormalMatrix"),     1, GL_FALSE, value_ptr(this->NormalMatrix));

	glUniform3f(getUniformID("cameraPosition"), this->cameraPosition.x, this->cameraPosition.y, this->cameraPosition.z);
	glUniform4f(getUniformID("model_ambient"), (GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.1, (GLfloat) 1.0);
	glUniform4f(getUniformID("model_color"), this->color.x, this->color.y, this->color.z, this->color.w);

	glUniform4f(getUniformID("light[0].position"),  this->cameraPosition.x, this->cameraPosition.y, this->cameraPosition.z, Lights[0].position.w);
	glUniform4f(getUniformID("light[0].direction"), this->center.x,    this->center.y,    this->center.z,    Lights[0].direction.w);
	glUniform4f(getUniformID("light[0].color"),     Lights[0].color.x, Lights[0].color.y, Lights[0].color.z, Lights[0].color.w);
	glUniform1f(getUniformID("light[0].angle"),     Lights[0].angle);
	glUniform1f(getUniformID("light[0].intensity"), Lights[0].intensity);

	glUniform4f(getUniformID("light[1].position"),  Lights[1].position.x,  Lights[1].position.y,  Lights[1].position.z,  Lights[1].position.w);
	glUniform4f(getUniformID("light[1].direction"), Lights[1].direction.x, Lights[1].direction.y, Lights[1].direction.z, Lights[1].direction.w);
	glUniform4f(getUniformID("light[1].color"),     Lights[1].color.x,     Lights[1].color.y,     Lights[1].color.z,     Lights[1].color.w);
	glUniform1f(getUniformID("light[1].angle"),     Lights[1].angle);
	glUniform1f(getUniformID("light[1].intensity"), Lights[1].intensity);

	glUniform4f(getUniformID("light[2].position"),  Lights[2].position.x,  Lights[2].position.y,  Lights[2].position.z,  Lights[2].position.w);
	glUniform4f(getUniformID("light[2].direction"), Lights[2].direction.x, Lights[2].direction.y, Lights[2].direction.z, Lights[2].direction.w);
	glUniform4f(getUniformID("light[2].color"),     Lights[2].color.x,     Lights[2].color.y,     Lights[2].color.z,     Lights[2].color.w);
	glUniform1f(getUniformID("light[2].angle"),     Lights[2].angle);
	glUniform1f(getUniformID("light[2].intensity"), Lights[2].intensity);
}
