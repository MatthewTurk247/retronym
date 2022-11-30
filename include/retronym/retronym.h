#pragma once

#include <string>

namespace retro {
	int execvp(std::string file, std::vector<std::string> argv);
	
	int execv(std::string path, std::vector<std::string> argv);
}  // namespace retro
