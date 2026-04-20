#include "new.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "osal/osal.h"

typedef struct {
    const char *conf;
    const char *src;
    const char *res;
    const char *start;
    const char *main_scene_dir;
    const char *main_scene;
} Paths;

ErrorCode new_project(const char *name) {
    const size_t LEN = strlen(name) + 1;
    const size_t TOTAL_PATH_SIZE = LEN + 10 // name + "/lumi.conf"
                                   + LEN + 4 // name + "/src"
                                   + LEN + 4 // name + "/res"
                                   + LEN + 14 // name + "/src/start.lua"
                                   + LEN + 9 // name + "/src/main"
                                   + LEN + 18; // name + "/src/main/main.lua"
    const char *path = malloc(TOTAL_PATH_SIZE);
    if (path == NULL) {
        return ERROR_OUT_OF_MEMORY;
    }
    const Paths PATHS = {.conf = path,
                         .src = path + LEN + 10,
                         .res = path + LEN * 2 + 10 + 4,
                         .start = path + LEN * 3 + 10 + 4 + 4,
                         .main_scene_dir = path + LEN * 4 + 10 + 4 + 14,
                         .main_scene = path + LEN * 5 + 10 + 4 + 4 + 14 + 9};

    snprintf((char *) PATHS.conf, TOTAL_PATH_SIZE, "%s/lumi.conf", name);
    snprintf((char *) PATHS.src, LEN + 4, "%s/src", name);
    snprintf((char *) PATHS.res, LEN + 4, "%s/res", name);
    snprintf((char *) PATHS.start, LEN + 14, "%s/src/start.lua", name);
    snprintf((char *) PATHS.main_scene_dir, LEN + 9, "%s/src/main", name);
    snprintf((char *) PATHS.main_scene, LEN + 18, "%s/src/main/main.lua", name);

    print("Creating project with the following files and directories:");
    print(PATHS.conf);
    print(PATHS.src);
    print(PATHS.res);
    print(PATHS.start);
    print(PATHS.main_scene_dir);
    print(PATHS.main_scene);

    if (osal_mkdir(name) != 0) {
        goto mkdir_err;
    }
    if (osal_mkdir(PATHS.src) != 0) {
        goto mkdir_err;
    }
    if (osal_mkdir(PATHS.res) != 0) {
        goto mkdir_err;
    }
    if (osal_mkdir(PATHS.main_scene_dir) != 0) {
        goto mkdir_err;
    }

    free((void *) path);
    return ERROR_SUCCESS;

mkdir_err:
    free((void *) path);
    return ERROR_FAILED_MKDIR;
}
