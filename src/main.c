#include <stdio.h>

#include "commands/help.h"
#include "commands/new.h"
#include "commands/version.h"
#include "error.h"
#include "getopt/getopt.h"

static struct option g_long_options[] = {{"help", no_argument, 0, 'h'},
                                         {"version", no_argument, 0, 'v'},
                                         {"new", required_argument, 0, 'n'},
                                         {"generate", required_argument, 0, 'g'},
                                         {"verify", optional_argument, 0, 'V'},
                                         {"build", optional_argument, 0, 'B'},
                                         {"run", optional_argument, 0, 'R'},
                                         {"clean", optional_argument, 0, 'C'},
                                         {0, 0, 0, 0}};

int main(const int argc, char *argv[]) {

    if (argc <= 1) {
        nfatal_error(ERROR_NO_ARGUMENT);
    }

    int opt;
    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "hvn:g:V::B::R::C::", g_long_options, &option_index)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
            case 'v':
                print_version();
            case 'n': {
                const ErrorCode STATUS = new_project(optarg);
                if (STATUS != ERROR_SUCCESS) {
                    fatal_error(STATUS, "Failed to create project");
                }
                return ERROR_SUCCESS;
            }
            case ':':
                fatal_error(ERROR_MISSING_ARGUMENT, argv[optind - 2]);
            default:
                fatal_error(ERROR_INVALID_ARGUMENT, argv[optind - 1]);
                ;
        }
    }
    if (optind < argc) {
        while (optind < argc) {
            error_print(ERROR_INVALID_ARGUMENT, argv[optind++]);
        }
        return ERROR_INVALID_ARGUMENT;
    }

    return 0;
}
