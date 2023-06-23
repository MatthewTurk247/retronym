#include <fmt/format.h>
#include <retronym/retronym.h>
#include <retronym/convert.h>

/*using namespace retro;

int execvp(std::string file, std::vector<std::string> argv) {
  char** params = retrograde_params(argv);
  return execvp(params[0], params);
}

int execv(std::string path, std::vector<std::string> argv) {
  char** params = retrograde_params(argv);
  return execv(params[0], params);
}*/

#ifdef _WIN32
   const char PATH_SEPARATOR = '\\';
#else
   const char PATH_SEPARATOR = '/';
#endif

FILE* retro::fopen(const std::string& filePath, const std::string& mode) {
    FILE* file = std::fopen(filePath.c_str(), mode.c_str());
    if (file == NULL) {
        // Handle error
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return nullptr;
    }
    
    return file;
}

// Base case: single argument
std::string retro::joinPath(const std::string& part) {
    return part;
}

// Recursive variadic template to handle multiple arguments
template<typename... Args>
std::string retro::joinPath(const std::string& part, Args... args) {
    return part + PATH_SEPARATOR + joinPath(args...);
}

int retro::exec(const std::string& path, const std::vector<std::string>& args, const std::map<std::string, std::string>& env) {
    char** argv = allocateArgs(args);
    char** envp = allocateEnv(env);
    
    // FIXME: Without a compatability layer, `execve` is not available to Windows.
    int result = execve(path.c_str(), argv, envp);
    freevp(argv, args.size());
    freevp(envp, env.size());
    /*std::string errorMsg = "execve failed with error: ";
    char* errorMessage = strcat(strerror(errno), errorMsg.c_str());
    
    throw std::runtime_error(strcat(errorMessage, "\n"));*/
    
    return result;
}

char** retro::allocateArgs(const std::vector<std::string>& args) {
    char** argv = new char*[args.size() + 1]; // extra room for nullptr
    
    for (size_t i = 0; i != args.size(); ++i) {
        argv[i] = new char[args[i].size() + 1]; // extra room for null terminator '\0'
        strcpy(argv[i], args[i].c_str());
    }
    argv[args.size()] = nullptr; // end array with nullptr
    
    return argv;
}

char** retro::allocateEnv(const std::map<std::string, std::string>& env) {
    char** envp = new char*[env.size() + 1]; // extra room for nullptr
    size_t i = 0;
    
    for (const auto& e : env) {
        std::string env_var = e.first + "=" + e.second;
        envp[i] = new char[env_var.size() + 1]; // extra room for '\0'
        strcpy(envp[i], env_var.c_str());
        ++i;
    }
    envp[env.size()] = nullptr; // end array with nullptr
    
    return envp;
}

void retro::freevp(char** argv, size_t size) {
    for (size_t i = 0; i != size; ++i) {
        delete [] argv[i];
    }
    delete [] argv;
}
