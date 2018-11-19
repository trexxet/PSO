#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "../opencl/CLEnviroment.h"


class Function {
	using Description = std::tuple<float, float, std::string, std::string, std::string>;
	static std::vector<Description> List;
	Function (float half_w, float half_h,
	          std::string string_representation, const CLEnviroment& cl_env, const std::string &cl_file);

	CLProgram prog;

	float domain_w = 0, domain_h = 0;

public:
	std::string str_repr;

	void calculate_coordinates (int pix_w, int pix_h, float* coord_x, float* coord_y);
	void calculate_values (float* val_x, float* val_y);

	using NameList = char**;
	static Function get (const std::string &name, const CLEnviroment& cl_env);
	static void getList (NameList* buffer);
	static size_t getListSize () { return List.size ();}
	static void freeList (NameList* buffer);
};
