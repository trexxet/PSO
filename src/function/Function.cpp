#include "Function.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>


std::vector<Function::Description> Function::List = {
		// name      domain_x/2  domain_y/2  string_representation                 cl_file_path
		{  "Waves",  3.0f,       3.0f,       "-cos(x^2+y^2) / exp((x^2+y^2)/8)",   "../cl/waves.cl" },
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
	free (coord_x);
	free (coord_y);
	size_x = pix_w;
	size_y = pix_h;
	coord_x = (float*) calloc (pix_w, sizeof(float));
	coord_y = (float*) calloc (pix_h, sizeof(float));
	float step_x = domain_w / (float) pix_w;
	float step_y = domain_h / (float) pix_h;
	x_buf_size = sizeof(float) * pix_w;
	y_buf_size = sizeof(float) * pix_h;

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


void Function::calculate_values (const CLEnviroment& cl_env, const float max_val) {
	free (values);
	free (rgb);
	size_t val_buf_size = sizeof(float) * size_x * size_y;
	size_t rgb_buf_size = val_buf_size * 3;
	values = (float*) calloc (val_buf_size, 1);
	rgb = (float*) calloc (rgb_buf_size, 1);

	cl::Kernel kernel (program.program (), "calculate");
	cl::Buffer coord_x_buf (cl_env.ctx (), CL_MEM_READ_ONLY, x_buf_size);
	cl::Buffer coord_y_buf (cl_env.ctx (), CL_MEM_READ_ONLY, y_buf_size);
	cl::Buffer values_buf (cl_env.ctx (), CL_MEM_WRITE_ONLY, val_buf_size);
	cl::Buffer rgb_buf (cl_env.ctx (), CL_MEM_WRITE_ONLY, rgb_buf_size);

	cl_env.queue ().enqueueWriteBuffer (coord_x_buf, CL_TRUE, 0, x_buf_size, (void*) coord_x);
	cl_env.queue ().enqueueWriteBuffer (coord_y_buf, CL_TRUE, 0, y_buf_size, (void*) coord_y);

	kernel.setArg (0, coord_x_buf);
	kernel.setArg (1, coord_y_buf);
	kernel.setArg (2, values_buf);
	kernel.setArg (3, max_val);
	kernel.setArg (4, rgb_buf);

	cl_env.queue ().enqueueNDRangeKernel (kernel, cl::NullRange, cl::NDRange (size_x, size_y));
	cl_env.queue ().enqueueReadBuffer (values_buf, CL_TRUE, 0, val_buf_size, (void*) values);
	cl_env.queue ().enqueueReadBuffer (rgb_buf, CL_TRUE, 0, rgb_buf_size, (void*) rgb);

	generateTexture ();
}


void Function::generateTexture () {
	if (texID != 0)
		glDeleteTextures (1, &texID);
	glGenTextures (1, &texID);
	glBindTexture (GL_TEXTURE_2D, texID);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB32F, (GLsizei) size_x, (GLsizei) size_y, 0, GL_RGB, GL_FLOAT, rgb);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
	free (values);
	free (rgb);
	if (texID != 0)
		glDeleteTextures (1, &texID);
}
