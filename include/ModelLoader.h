#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <SFML/OpenGL.hpp>


std::vector<std::string> split(char[], char);

bool LoadModel(std::string, GLfloat*, bool=true);