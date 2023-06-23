//
//  retronym.hpp
//  retronym
//
//  Created by Matthew Turk on 6/21/23.
//

#include <iostream>
#include <string>
#include <unistd.h>
#include <map>
#include <string>

#ifndef retronym_
#define retronym_

/* The classes below are exported */
#pragma GCC visibility push(default)

class retro {
public:
    FILE* fopen(const std::string& filePath, const std::string& mode);
    std::string joinPath(const std::string& part);
    template<typename... Args>
    std::string joinPath(const std::string& part, Args... args);
    std::string getenv(const std::string& name);
    int exec(const std::string& path, const std::vector<std::string>& args, const std::map<std::string, std::string>& env);
private:
    char** allocateArgs(const std::vector<std::string>& args);
    char** allocateEnv(const std::map<std::string, std::string>& env);
    void freevp(char** argv, size_t size);
};

#pragma GCC visibility pop
#endif
