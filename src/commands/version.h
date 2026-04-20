#ifndef VERSION_H
#define VERSION_H
#include <stdio.h>

_Noreturn void print_version();
static void print_version_nexit() {
    printf("LUMI version %s\n", PROJECT_VERSION "\nCopyright (c) 2026 TheMonHub and contributors\n"
                                            "Licensed under the Apache 2.0 License\n"
                                            "Source code: https://github.com/TheMonHub/LUMI\n\n"
                                            "Third-party components:\n"
                                            "- LuaJIT: Copyright (C) 2005-2026 Mike Pall\n"
                                            "- getopt_port: Copyright (c) 2012-2023 Kim Grasman");
}

#endif // VERSION_H
