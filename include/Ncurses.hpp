/*
** Graphicals.hpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/include
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:48:34 PM 2025 ramziathzakari@epitech.eu
** Last update Mon Apr 13 2:20:48 AM 2025 ramziathzakari@epitech.eu
*/

#ifndef _NCURSES_HPP_
#define _NCURSES_HPP_

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
#include "IDisplay.hpp"
class NCursesDisplay : public IDisplay {
    public:
        NCursesDisplay() = default;
        ~NCursesDisplay() = default;

        void init() override;
        bool isOpen() override;
        std::string handleEvents(std::string &direction) override;
        void display_menu() override;
        void display_state(const std::vector<std::vector<int>> &map) override;
        void  close();
        std::string getActualLibrary()override;
        std::string getActualGame()override;
        void setActualLibrary(std::string)override;
        void setActualGame(std::string)override;
        void display_game_over() override;
        void display_score(int score)override;
        void clear();
        void rectangle(WINDOW *win, int y1, int x1, int y2, int x2);
    protected:
    bool _isOpen = true;
    std::string actualLibrary;
    std::string actualgame;
    WINDOW *win;
    std::vector<std::string> games;
    std::vector<std::string> graphics;
    int row_high = 0;
    int col_high = 0;
};

extern "C" {
    IDisplay *create();
}

#endif