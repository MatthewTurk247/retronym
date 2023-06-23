#include <retronym/convert.h>

char* retrograde(std::string s) {
    char* result = new char[s.size()];
    return strcpy(result, s.c_str());
}

char** palloc(std::vector<std::string> args) {
    size_t nparams = args.size();
    size_t nbytes = (nparams + 1) * sizeof(char*);  // +1 for null terminator.
    char** params = (char**)malloc(nbytes);

    for (size_t i = 0; i < nparams; i++) {
        params[i] = retrograde(args[i]);
    }

    // This array needs to be null-terminated.
    params[nparams] = NULL;  // Use NULL here.

    char** pparams = (char**)malloc(nbytes);
    memmove(pparams, params, nbytes);
    // Don't forget to free the original array.
    free(params);

    return pparams;
}
