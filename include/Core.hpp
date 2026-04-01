/*
** Core.hpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/include
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:37:27 PM 2025 ramziathzakari@epitech.eu
** Last update Mon Apr 13 5:33:20 PM 2025 ramziathzakari@epitech.eu
*/

#ifndef CORE_HPP_
# define CORE_HPP_
#include <vector>
#include <iostream>
#include "IDisplay.hpp"
#include <memory>
#include "Games.hpp"
#include <filesystem>

class Core {
    public:
        explicit Core(char *);
        void run();
        ~Core();

    protected:
    private:
    enum State {
        MENU,
        GAME,
        QUIT
    };
    State current_state = MENU;
    std::string state;
    size_t current_lib = 0;
    size_t current_game = 0;
    bool menu = true;
    void loadgraphiclibs(const std::string &path);
    void loadgamelibs(const std::string &path);
    std::vector<std::string> displayLibNames {"arcade_ncurses.so",
    "arcade_sdl.so",
    "arcade_sfml.so"};
    std::vector<std::string> gameLibNames {"arcade_snake.so", "arcade_nibbler.so"};
    void switchDisplayLibrary(const std::string& libName);
    void switchGame(const std::string &gameName);
    //std::vector<std::unique_ptr<IDisplay>> displays;
    //std::vector<std::unique_ptr<IGames>> games;
    std::unique_ptr<IDisplay> display;
    std::unique_ptr<IGames> game;
    std::vector<void*> libGamesHandles;
    std::vector<void*> libGraphicHandles; // Pour dlclose
    bool is_validate_state() const;
    void handle_game_over();
    bool is_game_lib(const std::string& filename) const;
};
#endif /* !CORE_HPP_ */
