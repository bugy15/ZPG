#include "Subject.h"
#include <algorithm>

using namespace std;

void Subject::attach(Shader * shader)
{
	list.push_back(shader);
}
void Subject::detach(Shader * shader)
{
	list.erase(std::remove(list.begin(), list.end(), shader), list.end());
}

void Subject::notify()
{

}
