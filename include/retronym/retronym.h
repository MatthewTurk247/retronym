#pragma once
#include <string>
#include "unistd.h"

namespace retro {
	int execvp(std::string file, std::vector<std::string> argv);
	
	int execv(std::string path, std::vector<std::string> argv);
}  // namespace retro
