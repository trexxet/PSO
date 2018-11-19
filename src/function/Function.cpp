#include "Function.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>


std::vector<Function::Description> Function::List = {
		// name      domain_x/2  domain_y/2  string_representation                 cl_file_path
		{  "Waves",  6.0f,       6.0f,       "-cos(x^2+y^2) / exp((x^2+y^2)/8)",   "../cl/waves.cl" },
		{  "Hills",  6.0f,       6.0f,       "-cos(x)cos(y) / exp((x^2+y^2)/32)",  "../cl/hills.cl" }
};


cl::Kernel* Function::coord_kernel = nullptr;


Function::Function (float half_w, float half_h,
                    std::string string_representation, const CLEnviroment& cl_env, const std::string& cl_file)
	: str_repr (std::move (string_representation)), program (cl_env, cl_file),
	  domain_w (2.f * half_w), domain_h (2.f * half_h)
{}


Function Function::get (const std::string& name, const CLEnviroment& cl_env) {
	for (auto& func : List)
		if (std::get<0>(func) == name)
			return Function (std::get<1>(func), std::get<2>(func), std::get<3>(func), cl_env, std::get<4>(func));
	throw std::invalid_argument ("No such function: " + name);
}


void Function::calculate_coordinates (const CLEnviroment& cl_env, size_t pix_w, size_t pix_h) {
	coord_x = (float*) calloc (pix_w, sizeof(float));
	coord_y = (float*) calloc (pix_h, sizeof(float));
	float step_x = domain_w / (float) pix_w;
	float step_y = domain_h / (float) pix_h;
	size_t x_buf_size = sizeof(float) * pix_w;
	size_t y_buf_size = sizeof(float) * pix_h;

	cl::Buffer coord_x_buf (cl_env.ctx (), CL_MEM_WRITE_ONLY, x_buf_size);
	cl::Buffer coord_y_buf (cl_env.ctx (), CL_MEM_WRITE_ONLY, y_buf_size);

	coord_kernel->setArg (0, step_x);
	coord_kernel->setArg (1, step_y);
	coord_kernel->setArg (2, coord_x_buf);
	coord_kernel->setArg (3, coord_y_buf);

	cl_env.queue ().enqueueNDRangeKernel (*coord_kernel, cl::NullRange, cl::NDRange (pix_w, pix_h));
	cl_env.queue ().enqueueReadBuffer (coord_x_buf, CL_TRUE, 0, x_buf_size, (void*) coord_x);
	cl_env.queue ().enqueueReadBuffer (coord_y_buf, CL_TRUE, 0, y_buf_size, (void*) coord_y);
}


void Function::calculate_values (float *val_x, float *val_y) {

}


void Function::getList (NameList* buffer) {
	size_t list_size = List.size ();
	*buffer = (char**) calloc (list_size + 1, sizeof(char*));
	for (size_t i = 0; i < list_size; i++) {
		(*buffer)[i] = (char*) calloc (std::get<0>(List[i]).length () + 1, sizeof(char));
		memcpy ((*buffer)[i], std::get<0>(List[i]).c_str (), std::get<0>(List[i]).length ());
	}
}


void Function::freeList (NameList* buffer) {
	size_t i = 0;
	char *str = nullptr;
	while ((str = (*buffer)[i++])) free (str);
	free (*buffer);
	*buffer = nullptr;
}


Function::~Function () {
	free (coord_x);
	free (coord_y);
}
