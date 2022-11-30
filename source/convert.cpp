#include <retronym/convert.h>

char* retrograde(std::string s) {
    char* result = new char[s.size()];
    return strcpy(result, s.c_str());
}

char** retrograde_params(std::vector<std::string> args) {
    size_t nparams = args.size();
    size_t nbytes = nparams * sizeof(char*);
    char** params = (char**)malloc(nbytes);

    for (size_t i = 0; i < nparams; i++) {
        params[i] = retrograde(args[i]);
    }

    // This array needs to be null-terminated.
    params[nparams] = 0;
    char** pparams = (char**)malloc(nbytes);
    memmove(pparams, params, nbytes);

    return pparams;
}