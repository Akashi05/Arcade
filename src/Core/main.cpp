/*
** Core.cpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/src
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:37:11 PM 2025 ramziathzakari@epitech.eu
** Last update Sat Apr 11 9:08:17 AM 2025 ramziathzakari@epitech.eu
*/

#include <cstring>
#include <stdio.h>
#include <dlfcn.h>
#include <ostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "../../include/Error.hpp"
#include "../../include/Core.hpp"
#include "../../include/Ncurses.hpp"
#include "../../include/SFML.hpp"

void error_libaries(char *av)
{
    std::string arg = av;
    std::string lib = arg.substr((arg.length()-3), arg.length());
    try {
        if (lib != ".so")
            throw Error(" ./arcade ./lib/arcade_***.so");
    } catch (const Error &e) {
        std::cerr << "Usage:" << e.what() << std::endl;
        exit(84);
    }
}

int verify_the_lib(char *av)
{
    if (strstr(av, "arcade_ncurses") != NULL)
        return 1;
    if (strstr(av, "arcade_sdl2") != NULL)
        return 2;
    if (strstr(av, "arcade_sfml") != NULL)
        return 3;
    return 0;
}

int main(int argc, char **argv) 
{
    try {
        if (argc != 2) throw Error("Usage: ./arcade ./lib/arcade_***.so");
        if (access(argv[1], X_OK) != 0) throw Error("Library not found or inaccessible");

    } catch (const Error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    int i = verify_the_lib(argv[1]);
    try {
        if (i != 3 && i!= 2 && i != 1)
            throw Error(" is not a librairie!!");
    } catch (const Error &e) {
        std::cerr << argv[1] << e.what() << std::endl;
        return 84;
    }
    try {
        Core core(argv[1]);
        core.run();
    } catch (const std::exception &e) {
        std::cerr << "error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
