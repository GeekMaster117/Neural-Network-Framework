#include <iostream>
#include <execinfo.h>

#include "utils.h"
#include "config.h"

void printStackTrace() 
{
    void* callstack[128];
    int frames = backtrace(callstack, 128);
    char** symbols = backtrace_symbols(callstack, frames);

    std::cout << "Stack trace (max depth " << stackTraceDepth << "):" << std::endl;
    for (int i = 0; i < stackTraceDepth && i < frames; i++) {
        std::cout << symbols[i] << std::endl;
    }
    free(symbols);
}