#include "Model.h"


Model::Model(char * filename)
{
	this->pocetPrvku = loadObject(filename, this->vao);
}

GLsizei Model::getVao()
{
	return this->vao;
}

GLsizei Model::getCount()
{
	return this->pocetPrvku;
}