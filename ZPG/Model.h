#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>

#include "ObjectLoader.h"


class Model : public ObjectLoader
{
private:
	GLuint  vao;
	GLsizei pocetPrvku;

public:
			Model(char * filename);
	GLsizei getVao();
	GLsizei getCount();
};

