#include "help.h"

#include <stdio.h>
#include <stdlib.h>

#include "version.h"

_Noreturn void print_help() {
    print_version_nexit();
    printf("%s", "\nUsage: lumi [OPTIONS] [COMMAND]\n"
                 "\n"
                 "Options:\n"
                 "  -h, --help                Show this help message and exit\n"
                 "  -v, --version             Show version information and exit\n"
                 "  -n, --new <path>          Create a new project at the specified path\n"
                 "  -g, --generate <name>     Generate a new scene\n"
                 "\n"
                 "Project Commands:\n"
                 "  -V, --verify [dir]        Validate the project configuration\n"
                 "  -B, --build  [dir]        Compile the project assets and code\n"
                 "  -R, --run    [dir]        Execute the project\n"
                 "  -C, --clean  [dir]        Remove build artifacts\n");
    exit(0);
}
