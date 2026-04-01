/*
** Graphicals.hpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/include
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:48:34 PM 2025 ramziathzakari@epitech.eu
** Last update Mon Apr 13 2:20:35 AM 2025 ramziathzakari@epitech.eu
*/

#ifndef _IDISPLAY_HPP_
#define _IDISPLAY_HPP_

#include <cstring>
#include <stdio.h>
#include <dlfcn.h>
#include <ostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ncurses.h>
#include <vector>

class IDisplay {
    public:
        virtual ~IDisplay() = default;
        virtual void init() = 0;
        virtual bool isOpen() = 0;
        virtual void display_menu() = 0;
        virtual void close() = 0;
        virtual std::string getActualGame() = 0;
        virtual std::string getActualLibrary() = 0;
        virtual void setActualGame(std::string) = 0;
        virtual void setActualLibrary(std::string) = 0;
        virtual void display_game_over() = 0;
        virtual void display_score(int score) = 0;
        virtual std::string handleEvents(std::string &direction) = 0;
        virtual void display_state(const std::vector<std::vector<int>> &map) = 0;
    protected:
    private:
};

#endif