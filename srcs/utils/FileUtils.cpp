//
// Created by Marc on 11/04/2018.
//

#include <fstream>
#include <sstream>
#include "FileUtils.hpp"

std::string utils::loadFile(const std::string &file)
{
	std::string result;
	std::stringstream read;
	std::ifstream input(file);

	if (input.is_open())
	{
		read << input.rdbuf();
		result = read.str();
		input.close();
	}

	return result;
}
