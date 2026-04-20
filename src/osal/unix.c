#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>

#include "osal.h"

#include <sys/stat.h>

#include "error.h"

int osal_mkdir(const char *path) {
    if (mkdir(path, 0755) != 0) {
        if (errno == EEXIST) {
            return 0;
        }
        error_print(ERROR_FAILED_MKDIR, path);
        perror("LUMI: [ERROR] Reason");
        return -1;
    }
    return 0;
}
