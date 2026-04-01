// /*
// ** Core.cpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/src
// **
// ** Made by ramziathzakari@epitech.eu
// ** Login   <ramziathzakari@epitech.eu>
// **
// ** Started on  Thu Mar 27 2:37:11 PM 2025 ramziathzakari@epitech.eu
// ** Last update Mon Apr 13 5:33:40 PM 2025 ramziathzakari@epitech.eu
// */

#include "../../include/Core.hpp"

#include <dlfcn.h>
#include <filesystem>
#include <iostream>
#include <algorithm>


Core::Core(char *start_lib)
{
    loadgraphiclibs(start_lib);
    if (!display)
        throw std::runtime_error("No display libraries found");
    current_game = 0;
    current_lib = 0;  
}


void Core::loadgraphiclibs(const std::string &path) 
{
        void *handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!handle) {
            const char* error = dlerror();
            std::string errorMsg = "Error loading library: ";
            errorMsg += (error != nullptr && *error != '\0') ? error : "unknown error";
            throw std::runtime_error(errorMsg);
        }
        auto createLib = (IDisplay *(*)())dlsym(handle, "create");
        if (!createLib) {
            dlclose(handle); 
            const char* error = dlerror();
            std::string errorMsg = "Error loading symbol: ";
            errorMsg += (error != nullptr && *error != '\0') ? error : "unknown error";
            throw std::runtime_error(errorMsg);
            throw std::runtime_error("Error loading symbol: " + std::string(dlerror()));
        }
        IDisplay *lib = createLib();
        display = std::unique_ptr<IDisplay>(lib);
        libGraphicHandles.push_back(handle);
}

void Core::loadgamelibs(const std::string &path)
{
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        const char* error = dlerror();
        std::string errorMsg = "Error loading library: " + std::string(error ? error : "unknown error");
        throw std::runtime_error(errorMsg);
    }
    auto creategame = (IGames *(*)())dlsym(handle, "create");
    if (!creategame) {
        dlclose(handle);
        throw std::runtime_error("Error loading symbol: " + std::string(dlerror()));
    }
    IGames *games_  = creategame();
    if (!games_) {
        dlclose(handle);
        throw std::runtime_error("Error creating game instance");
    }        
    game = std::unique_ptr<IGames>(games_);
    libGamesHandles.push_back(handle);
}

Core::~Core() {
    for (auto handle : libGamesHandles) {
        if (handle) {
            dlclose(handle);
        }
    }
    for (auto handle : libGraphicHandles) {
        if (handle) {
            dlclose(handle);
        }
    }
}


void Core::switchDisplayLibrary(const std::string& libName) {
    for (size_t i = 0; i < displayLibNames.size(); ++i) {
        if (displayLibNames[i] == libName) {
            current_lib = i;
            break;
        }
    }
}

void Core::switchGame(const std::string& gameName) {
    for (size_t i = 0; i < gameLibNames.size(); ++i) {
        if (gameLibNames[i].find(gameName) != std::string::npos) {
            current_game = i;
            return;
        }
    }
}

void Core::run() {
    std::string current_library = display->getActualLibrary();
    std::string actualGame = "";
    std::string t = "";

    if (!display) return;
    display->init();
    while (display->isOpen()) {
        if (menu == true) {
            display->display_menu();
            actualGame = display->getActualGame();
            if (!actualGame.empty()) {
                menu = false;
                loadgamelibs(actualGame);
                continue;
            }
        }

        std::string lib_charged = display->getActualLibrary();
        if (!lib_charged.empty() && lib_charged != current_library) {
            display->close();
            display = nullptr;
            current_library = lib_charged;
            loadgraphiclibs(current_library);
            display->init();
            continue;
        }
        if (actualGame == "./lib/arcade_snake.so" || actualGame == "./lib/arcade_nibbler.so") {
            loadgamelibs(actualGame);
        }
        if (game) {
            menu = false;
            game->init();
            while ((!game->is_gameEnd())) {
                display->display_state(game->getState());
                int score = game->getPlayerScore();
                display->display_score(score);
                t = display->handleEvents(state);
                if (t == "QUIT")
                    break;
                game->update(t);
                usleep(150000);
            }
            if (game->is_gameEnd()) {
                display->display_game_over();
                while (display->isOpen()) {
                    t = display->handleEvents(state);
                    if (t == "m" || t == "M" || t == "QUIT") {
                        break;
                    }
                }
            }
            display->setActualGame("");
            menu = true;
        }
    }
    if (game)
        game = nullptr;
    if (display) {
        display->close();
        display = nullptr;
    }
}
