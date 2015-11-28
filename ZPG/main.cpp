#include "Application.h"

int main(int argc, char* argv[])
{
	Application * aplikace;
	aplikace = aplikace->getInstance();

	if (!aplikace->init(argc, argv)){
		exit(EXIT_FAILURE);
	}

	aplikace->start_program();
	aplikace->~Application();
	return 0;
}