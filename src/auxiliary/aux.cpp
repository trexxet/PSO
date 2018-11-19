#include "aux.h"
#include <fstream>

std::pair<std::string, bool> aux::loadFileToString (const std::string &filename) {
	std::ifstream file (filename, std::ios::in | std::ios::binary);
	std::string string;
	bool success;
	if (file) {
		success = true;
		file.seekg (0, std::ios::end);
		string.resize ((unsigned) file.tellg ());
		file.seekg (0, std::ios::beg);
		file.read (&string[0], string.size ());
		file.close ();
	} else {
		success = false;
	}
	return std::make_pair (string, success);
}
