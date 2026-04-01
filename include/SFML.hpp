/*
** Graphicals.hpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/include
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:48:34 PM 2025 ramziathzakari@epitech.eu
** Last update Mon Apr 13 2:21:03 AM 2025 ramziathzakari@epitech.eu
*/

#ifndef _SFML_HPP_
#define _SFML_HPP_

#include <cstring>
#include <stdio.h>
#include <dlfcn.h>
#include <ostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ncurses.h>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>
#include <memory>
#include "IDisplay.hpp"

class SfmlDisplay : public IDisplay {
    public:
        SfmlDisplay() = default;
        ~SfmlDisplay() = default;
    
        void init() override;
        void close() override;
        bool isOpen() override;
        void clear();
        std::string getActualLibrary()override;
        std::string getActualGame()override;
        void setActualLibrary(std::string)override;
        void setActualGame(std::string)override;
        std::string handleEvents(std::string &direction) override;
        void display_menu() override;
        void display_game_over() override;
        void display_score(int score)override;
        void display_state(const std::vector<std::vector<int>> &map) override;

    protected:
    void loadFonts();                                
    void setupMenuOptions();                            
    void handleUserInput(sf::Event &event);
    void drawUIElements(sf::RenderWindow &window);

    std::vector<std::vector<sf::Text>> menuOptions; 
    std::shared_ptr<sf::RenderWindow> _window;      
    sf::Font fontSecondary;   
    sf::Font fontMain;
    int selectedRow = 0;
    int selectedCol = 0;
    bool _isOpen;

    std::string actualgame;
    std::string actualLibrary;

    sf::Texture _bordureTexture;
    
};

extern "C" {
    IDisplay *create();
}
#endif