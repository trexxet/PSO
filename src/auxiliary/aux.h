#pragma once

#include <string>
#include <utility>

namespace aux {
	std::pair<std::string, bool> loadFileToString (const std::string& filename);
}
