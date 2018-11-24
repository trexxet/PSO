#pragma once

#include "glad.h"

#include <string>
#include <tuple>
#include <vector>

#include "../opencl/CLEnviroment.h"


#define COORD_PROGRAM_PATH "../cl/calc_coords.cl"

class Function {
	using Description = std::tuple<std::string, float, float, std::string, std::string>;
	static std::vector<Description> List;
	Function (float half_w, float half_h,
	          std::string string_representation, const CLEnviroment& cl_env, const std::string& cl_file);


	CLProgram program;
	static cl::Kernel *coord_kernel;

	float *coord_x = nullptr, *coord_y = nullptr;
	size_t size_x = 0, size_y = 0, x_buf_size = 0, y_buf_size = 0;
	float *values = nullptr;

	GLuint texID = 0;
	void generateTexture ();

public:
	std::string str_repr;
	float domain_w = 0, domain_h = 0;

	void calculate_coordinates (const CLEnviroment& cl_env, size_t pix_w, size_t pix_h);
	void calculate_values (const CLEnviroment& cl_env);
	GLuint texture () { return texID; }

	using NameList = char**;
	static Function get (const std::string &name, const CLEnviroment& cl_env);
	static void getList (NameList* buffer);
	static size_t getListSize () { return List.size ();}
	static void freeList (NameList* buffer);

	static void setCoordinatesKernel (const CLEnviroment& cl_env, const std::string& cl_file) {
		coord_kernel = new cl::Kernel (CLProgram(cl_env, cl_file).program (), "calc_coordinates");
	}
	static void deleteCoordinatesKernel () {
		delete coord_kernel;
	}

	~Function ();
};
