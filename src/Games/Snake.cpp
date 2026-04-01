/*
** Games.cpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/src/Games
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:49:26 PM 2025 ramziathzakari@epitech.eu
** Last update Sat Apr 11 8:51:07 AM 2025 ramziathzakari@epitech.eu
*/

#include "Snake.hpp"

Snake::Snake() {
    _height = 25;
    _width = 50;
    _score = 0;
    _life = 1;
    _map = std::vector<std::vector<int>>(_height, std::vector<int>(_width, 0));
    _tailsC = std::make_pair(std::vector<int>(), std::vector<int>());
    _tailsN = 0;
    _gameOver = false;
}

void Snake::generatePrey() {
    _prey.first = 1 + rand() % (_width - 2);
    _prey.second = 1 + rand() % (_height - 2);
}

void Snake::renderMap() {
    for (int i = 0; i < _height; i++)
        for (int j = 0; j < _width; j++) {
            if (i == 0 || i == _height - 1 || j == 0 || j == _width - 1)
                _map[i][j] = 1;
            else
                _map[i][j] = 0;
        }
    _map[_snake.second][_snake.first] = 2;
    _map[_prey.second][_prey.first] = 3;
    for (int k = 0; k < _tailsN; k++)
        _map[_tailsC.second[k] - 1][_tailsC.first[k] - 1] = 4;
}

void Snake::init()
{
    _snake.first = _width / 2;
    _snake.second = _height / 2;
    generatePrey();
    for (int i = 0; i < 3; i++) {
        generateTail();
        _tailsN++;
        if (_tailsN == 1) {
            _tailsC.first.push_back(_snake.first);
            _tailsC.second.push_back(_snake.second);
        } else {
            _tailsC.first.push_back(_tailsC.first.back());
            _tailsC.second.push_back(_tailsC.second.back());
        }
    }
    renderMap();
}

void Snake::generateTail()
{
    if (_tailsN > 0) {
        int prevx = _snake.first +1;
        int prevy = _snake.second +1;
        int temp_x, temp_y;

        for (int i = 0; i < _tailsN; i++) {
            temp_x = _tailsC.first[i];
            temp_y = _tailsC.second[i];
            _tailsC.first[i] =  prevx;
            _tailsC.second[i] = prevy;
            prevx = temp_x;
            prevy = temp_y;
        }
    }
}

void Snake::update(std::string key)
{
    generateTail();
    if (key == "UP")
        _snake.second--;
    else if (key == "DOWN")
        _snake.second++;
    else if (key == "LEFT")
        _snake.first--;
    else if (key == "RIGHT")
        _snake.first++;
    if (_snake.first == _prey.first && _snake.second == _prey.second) {
        _score++;
        generatePrey();
        _tailsN++;
        _tailsC.first.push_back(_tailsC.first.back());
        _tailsC.second.push_back(_tailsC.second.back());
    }
    renderMap();
    if (_snake.second == 0 || _snake.second == _height - 1 || _snake.first == 0 || _snake.first == _width - 1) {
        _life--;
        if (_life < 0)
            _life = 0;
        _gameOver = true;
    }
    for (int k = 4; k < _tailsN; k++)
        if (_tailsC.first[k] == _snake.first && _tailsC.second[k] == _snake.second)
            _gameOver = true;
}
IGames *create()
{
    return new Snake();
}
