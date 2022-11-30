#include <fmt/format.h>
#include <retronym/retronym.h>
#include <retronym/convert.h>

using namespace retro;

int execvp(std::string file, std::vector<std::string> argv) {
  char** params = retrograde_params(argv);
  return _execvp(params[0], params);
}

int execv(std::string path, std::vector<std::string> argv) {
  char** params = retrograde_params(argv);
  return _execv(params[0], params);
}