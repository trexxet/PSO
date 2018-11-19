#include "Function.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>


std::vector<Function::Description> Function::List = {
		{6.0f, 6.0f, "Waves", "-cos(x^2+y^2) / exp((x^2+y^2)/8)", "../cl/waves.cl"},
		{6.0f, 6.0f, "Hills", "-cos(x)cos(y) / exp((x^2+y^2)/32)", "../cl/hills.cl"}
};


Function::Function (float half_w, float half_h,
                    std::string string_representation, const CLEnviroment& cl_env, const std::string& cl_file)
	: str_repr (std::move (string_representation)), prog (cl_env, cl_file),
	  domain_w (2.0f * half_w), domain_h (2.0f * half_h)
{}


Function Function::get (const std::string& name, const CLEnviroment& cl_env) {
	for (auto& func : List)
		if (std::get<2>(func) == name)
			return Function (std::get<0>(func), std::get<1>(func), std::get<3>(func), cl_env, std::get<4>(func));
	throw std::invalid_argument ("No such function: " + name);
}


void Function::calculate_coordinates (int pix_w, int pix_h, float *coord_x, float *coord_y) {

}


void Function::calculate_values (float *val_x, float *val_y) {

}


void Function::getList (NameList* buffer) {
	size_t list_size = List.size ();
	*buffer = (char**) calloc (list_size + 1, sizeof(char*));
	for (size_t i = 0; i < list_size; i++) {
		(*buffer)[i] = (char*) calloc (std::get<2>(List[i]).length () + 1, sizeof(char));
		memcpy ((*buffer)[i], std::get<2>(List[i]).c_str (), std::get<2>(List[i]).length ());
	}
}


void Function::freeList (NameList* buffer) {
	size_t i = 0;
	char *str = nullptr;
	while ((str = (*buffer)[i++])) free (str);
	free (*buffer);
	*buffer = nullptr;
}
