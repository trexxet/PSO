#pragma once

#include <string>
#include <vector>




class Function {
	using Description = std::vector<std::string>;
	static std::vector<Description> List;
	Function (const std::string &string_representation, const std::string &cl_file);

	std::string cl_file;

public:
	std::string str_repr;

	using NameList = char**;
	static Function get (const std::string &name);
	static void getList (NameList* buffer);
	static size_t getListSize () { return List.size ();}
	static void freeList (NameList* buffer);
};
