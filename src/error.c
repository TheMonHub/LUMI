#include "error.h"

#include <stdio.h>
#include <stdlib.h>

char *error_message(const ErrorCode CODE) {
    switch (CODE) {
        case ERROR_NO_ARGUMENT:
            return "No argument provided";
        case ERROR_INVALID_ARGUMENT:
            return "Invalid argument";
        case ERROR_MISSING_ARGUMENT:
            return "Missing argument";
        case ERROR_OUT_OF_MEMORY:
            return "Out of memory";
        case ERROR_FILE_NOT_FOUND:
            return "File not found";
        case ERROR_PERMISSION_DENIED:
            return "Permission denied";
        case ERROR_FAILED_MKDIR:
            return "Failed to create directory";
        default:
            return "Unknown error";
    }
}

void warn_print(const char *message) {
    fprintf(stderr, "LUMI: [WARN]  %s\n", message);
}

void error_print(const ErrorCode CODE, const char *message) {
    if (CODE == ERROR_INVALID_ARGUMENT || CODE == ERROR_MISSING_ARGUMENT) {
        fprintf(stderr, "LUMI: [ERROR] %s: '%s'\nUse -h or --help for usage information\n", error_message(CODE),
                message);
        return;
    }

    fprintf(stderr, "LUMI: [ERROR] %s: %s\n", error_message(CODE), message);
}

void nerror_print(const ErrorCode CODE) {
    if (CODE == ERROR_NO_ARGUMENT) {
        fprintf(stderr, "LUMI: [ERROR] %s\nUse -h or --help for usage information\n", error_message(CODE));
        return;
    }
    fprintf(stderr, "LUMI: [ERROR] %s\n", error_message(CODE));
}

_Noreturn void fatal_error(const ErrorCode CODE, const char *message) {
    if (CODE == ERROR_INVALID_ARGUMENT || CODE == ERROR_MISSING_ARGUMENT) {
        fprintf(stderr, "LUMI: [FATAL] %s: '%s'\nUse -h or --help for usage information\n", error_message(CODE),
                message);
        exit(CODE);
    }

    fprintf(stderr, "LUMI: [FATAL] %s: %s\n", error_message(CODE), message);
    exit(CODE);
}

_Noreturn void nfatal_error(const ErrorCode CODE) {
    if (CODE == ERROR_NO_ARGUMENT) {
        fprintf(stderr, "LUMI: [FATAL] %s\nUse -h or --help for usage information\n", error_message(CODE));
        exit(CODE);
    }
    fprintf(stderr, "LUMI: [FATAL] %s\n", error_message(CODE));
    exit(CODE);
}

void print(const char *message) {
    printf("LUMI: [INFO]  %s\n", message);
    fflush(stdout);
}
