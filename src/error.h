#ifndef ERROR_H
#define ERROR_H

typedef enum {
    ERROR_SUCCESS = 0,
    ERROR_UNKNOWN,
    ERROR_NO_ARGUMENT,
    ERROR_INVALID_ARGUMENT,
    ERROR_MISSING_ARGUMENT,
    ERROR_OUT_OF_MEMORY,
    ERROR_FILE_NOT_FOUND,
    ERROR_PERMISSION_DENIED,
    ERROR_FAILED_MKDIR
} ErrorCode;

char *error_message(ErrorCode CODE);
void warn_print(const char *message);
void error_print(ErrorCode CODE, const char *message);
void nerror_print(ErrorCode CODE);
_Noreturn void fatal_error(ErrorCode CODE, const char *message);
_Noreturn void nfatal_error(ErrorCode CODE);
void print(const char *message);

#endif // ERROR_H
