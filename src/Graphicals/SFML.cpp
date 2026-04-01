
/*
** Graphicals.cpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/src/Graphicals
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:50:18 PM 2025 ramziathzakari@epitech.eu
** Last update Wed Apr 15 7:17:09 PM 2025 ramziathzakari@epitech.eu
*/

#include <vector>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../../include/SFML.hpp"

sf::RectangleShape case_m(sf::Vector2f position, sf::Vector2f size)
{
    sf::RectangleShape rect(size);
    rect.setPosition(position);

    return rect;
}

bool SfmlDisplay::isOpen()
{
    return _isOpen;
}

std::string SfmlDisplay::handleEvents(std::string &direction)
{
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            std::cout << "Closing window..." << std::endl;
            direction = "QUIT";
            _isOpen = false;
            _window->close();
            return direction;
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    direction = "UP";
                    return direction;
                case sf::Keyboard::Down:
                    direction = "DOWN";
                    return direction;
                case sf::Keyboard::Left:
                    direction = "LEFT";
                    return direction;
                case sf::Keyboard::Right:
                    direction = "RIGHT";
                    return direction;
                case sf::Keyboard::Num1:
                    direction = "SWITCH_LIB:arcade_sdl.so";
                    return direction;
                case sf::Keyboard::Num2:
                    direction = "SWITCH_LIB:arcade_sfml.so";
                    return direction;
                case sf::Keyboard::N:
                    direction = "NEXT_GAME";
                    return direction;
                case sf::Keyboard::Q:
                    direction = "QUIT";
                    return direction;
                case sf::Keyboard::M:
                    direction = "m";
                    return direction;
                default:
                    break;
            }
        }
    }
    return direction;
}

void SfmlDisplay::display_game_over() 
{
    _window->clear();

    sf::Font font;
    font.loadFromFile("src/font/d.ttf");
    sf::Text text("GAME_OVER", font, 150);
    text.setFillColor(sf::Color::Red);
    text.setPosition(580, 300);
    _window->draw(text);

    sf::Font font1;
    font1.loadFromFile("src/font/font3.ttf");
    sf::Text text1("Appuyez sur M pour retourner au menu", font1, 25);
    text1.setPosition(680, 525);
    _window->draw(text1);
    _window->display();

}

void SfmlDisplay::display_menu()
{
    sf::Event event;
    loadFonts();
    setupMenuOptions();
    while (_window->isOpen()) {
        if(!_isOpen) break;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << "Closing window from menu..." << std::endl;
                _isOpen = false;
                _window->close();
            }
            handleUserInput(event);
            if (!getActualGame().empty()) {
                return;
            }
            _window->clear();
	    drawUIElements(*_window);
            _window->display();
        }
    }
};

void SfmlDisplay::display_state(const std::vector<std::vector<int>> &map)
{
    _window->clear();
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 1 || map[i][j] == 5) {

                sf::Sprite bordure;
                bordure.setTexture(_bordureTexture);
                bordure.setPosition(j * 32, i * 32);
                bordure.scale({0.05f, 0.05f});
                _window->draw(bordure);

            } else if (map[i][j] == 2) {

                sf::Vector2f position;
                position.x = j * 32;
                position.y = i * 32;
                sf:: RectangleShape mm = case_m(position, {20, 20});
                mm.setFillColor(sf::Color::Green);
                _window->draw(mm);

            } else if (map[i][j] == 3) {

                sf::Vector2f position;
                position.x = j * 32;
                position.y = i * 32;
            
                sf::CircleShape circle(05);
                circle.setPosition(position);
                circle.setFillColor(sf::Color::Blue);
                circle.setOutlineThickness(2);
            
                _window->draw(circle);
            
            } else if (map[i][j] == 4) {

                sf::Vector2f position;
                position.x = j * 32;
                position.y = i * 32;
                sf::RectangleShape mm = case_m(position, {20, 20});
                mm.setFillColor(sf::Color::Red);
                _window->draw(mm);

            }
        }
    }
    //_window->display();
    //_window->clear(sf::Color::Black);
};


void SfmlDisplay::loadFonts()
{
    if (!fontMain.loadFromFile("src/font/Dimbo.ttf") || 
        !fontSecondary.loadFromFile("src/font/font3.ttf")) {
        throw std::runtime_error("Error !!");
    }
}


void SfmlDisplay::setupMenuOptions()
{
    std::vector<std::vector<std::string>> options = {
        {"arcade_ncurses.so", "arcade_nibbler.so"},
        {"arcade_sdl2.so", "arcade_snake.so"},
        {"arcade_sfml.so", ""}
    };
    
    for (size_t i = 0; i < options.size(); i++) {
        std::vector<sf::Text> row;
        for (size_t j = 0; j < options[i].size(); j++) {
            sf::Text text(options[i][j], fontMain, 30);
            text.setPosition(500 + j * 370, 580 + i * 50);
            text.setFillColor(sf::Color::White);
            row.push_back(text);
        }
        menuOptions.push_back(row);
    }
}

void SfmlDisplay::handleUserInput(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        menuOptions[selectedRow][selectedCol].setFillColor(sf::Color::White);
    
        if (event.key.code == sf::Keyboard::Up) {
            selectedRow = (selectedRow - 1 + menuOptions.size()) % menuOptions.size();
        } else if (event.key.code == sf::Keyboard::Down) {
            selectedRow = (selectedRow + 1) % menuOptions.size();
        } else if (event.key.code == sf::Keyboard::Left) {
            selectedCol = (selectedCol - 1 + menuOptions[selectedRow].size()) % menuOptions[selectedRow].size();
        } else if (event.key.code == sf::Keyboard::Right) {
            selectedCol = (selectedCol + 1) % menuOptions[selectedRow].size();
        } else if (event.key.code == sf::Keyboard::Enter &&
                   menuOptions[selectedRow][selectedCol].getString().toAnsiString() == "arcade_ncurses.so") {
            _window->close();
            actualLibrary = "./lib/arcade_ncurses.so";
        } else if (event.key.code == sf::Keyboard::Enter &&
            menuOptions[selectedRow][selectedCol].getString().toAnsiString() == "arcade_snake.so") {
            actualgame = "./lib/arcade_snake.so";
        } else if (event.key.code == sf::Keyboard::Enter &&
            menuOptions[selectedRow][selectedCol].getString().toAnsiString() == "arcade_nibbler.so") {
            actualgame = "./lib/arcade_nibbler.so";
        } else if  (event.key.code == sf::Keyboard::Key::Q) {
            _isOpen = false;
            _window->close();
        }
        menuOptions[selectedRow][selectedCol].setFillColor(sf::Color::Red);
    }
}

void SfmlDisplay::drawUIElements(sf::RenderWindow &window)
{
    sf::Sprite bordure;
    sf::Texture texture;
    texture.loadFromFile("src/font/arcade.png");
    bordure.setTexture(texture);

    sf::Vector2f position;
    position.x = 2.8;
    position.y = 1.45;
    bordure.scale(position);
    window.draw(bordure);

    sf::Text gameLibraries("Games libraries available", fontMain, 30);
    gameLibraries.setPosition(500, 500);
    gameLibraries.setFillColor(sf::Color::Black);
    window.draw(gameLibraries);

    sf::Text graphicLibraries("Graphics libraries available", fontMain, 30);
    graphicLibraries.setPosition(870, 500);
    graphicLibraries.setFillColor(sf::Color::Black);
    window.draw(graphicLibraries);

    sf::Text bestScore("Best Score", fontMain, 30);
    bestScore.setPosition(1300, 500);
    bestScore.setFillColor(sf::Color::Black);
    window.draw(bestScore);

    sf::Text bestScore1("Snake: Player Be score: 115 pts", fontMain, 30);
    bestScore1.setPosition(1220, 590);
    bestScore1.setFillColor(sf::Color::White);
    window.draw(bestScore1);

    sf::Text bestScore2("Nibble: Player King score: 61 pts", fontMain, 30);
    bestScore2.setPosition(1220, 640);
    bestScore2.setFillColor(sf::Color::White);
    window.draw(bestScore2);

    sf::Text Enter("Enter Your Name:", fontMain, 30);
    Enter.setPosition(800, 800);
    Enter.setFillColor(sf::Color::Black);
    window.draw(Enter);

    sf::RectangleShape case_for_enter = case_m({780, 800}, {500, 33});
    case_for_enter.setOutlineColor(sf::Color(135, 206, 235));
    case_for_enter.setFillColor(sf::Color::Transparent);
    case_for_enter.setOutlineThickness(2);
    window.draw(case_for_enter);

    for (auto &row : menuOptions) {
        for (auto &text : row) {
            window.draw(text);
        }
    }
}

void SfmlDisplay::display_score(int score)
{
    sf::Text scoreText;
    scoreText.setFont(fontMain);
    scoreText.setString("SCORE: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Green);

    sf::FloatRect text_rect = scoreText.getGlobalBounds();
    scoreText.setOrigin(text_rect.left + text_rect.width, 0);
    scoreText.setPosition(_window->getSize().x - 40.f, 40.f);

    _window->draw(scoreText);    
    _window->display();
}

void SfmlDisplay::init()
{
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Arcade Window");
    _bordureTexture.loadFromFile("src/font/bordure.png");
    _isOpen = true;
}

void SfmlDisplay::setActualGame(std::string game)
{
    actualgame = game;
}

void SfmlDisplay::setActualLibrary(std::string library)
{
    actualLibrary = library;
}

std::string SfmlDisplay::getActualGame()
{
    return actualgame;
}

std::string SfmlDisplay::getActualLibrary()
{
    return actualLibrary;
}

void SfmlDisplay::close()
{
    _window->close();
    _isOpen = false;
}

IDisplay *create()
{
    return new SfmlDisplay();
}
