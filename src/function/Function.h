#pragma once

#include <string>
#include <vector>

#include "../opencl/CLEnviroment.h"


class Function {
	using Description = std::vector<std::string>;
	static std::vector<Description> List;
	Function (std::string string_representation, const CLEnviroment& cl_env, const std::string &cl_file);

	CLProgram prog;

public:
	std::string str_repr;

	using NameList = char**;
	static Function get (const std::string &name, const CLEnviroment& cl_env);
	static void getList (NameList* buffer);
	static size_t getListSize () { return List.size ();}
	static void freeList (NameList* buffer);
};
