/*
** Games.cpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/src/Games
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:49:26 PM 2025 ramziathzakari@epitech.eu
** Last update Sat Apr 11 8:51:07 AM 2025 ramziathzakari@epitech.eu
*/

#include "Nibbler.hpp"

Nibbler::Nibbler() {
    _height = 25;
    _width = 50;
    _score = 0;
    _life = 1;
    _map = std::vector<std::vector<int>>(_height, std::vector<int>(_width, 0));
    _tailsC = std::make_pair(std::vector<int>(), std::vector<int>());
    _tailsN = 0;
    _gameOver = false;
}

void Nibbler::generatePrey() {
    int x = 0;
    int y = 0;

    x = 1 + rand() % (_width - 2);
    y = 1 + rand() % (_height - 2);
    if (_map[y][x] != 0)
        generatePrey();
    _prey.first = x;
    _prey.second = y;
}

void Nibbler::renderMap() {
    genMap();
    _map[_snake.second][_snake.first] = 2;
    _map[_prey.second][_prey.first] = 3;
    for (int k = 0; k < _tailsN; k++)
        _map[_tailsC.second[k] - 1][_tailsC.first[k] - 1] = 4;
}

void Nibbler::genMap()
{
    _map = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,5,5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,1},
        {1,0,0,0,0,0,5,5,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,5,5,0,5,0,5,0,0,5,5,0,5,0,5,0,0,0,5,5,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,1},
        {1,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,1},
        {1,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,5,5,0,5,5,0,0,0,0,0,0,0,0,5,5,0,5,5,0,5,5,0,0,0,0,0,0,0,0,0,0,5,0,1},
        {1,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,5,5,0,5,5,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,1},
        {1,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,5,0,0,0,0,0,0,5,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,5,5,0,5,5,1},
        {1,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,5,5,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,5,5,0,0,0,5,5,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,5,5,0,0,0,5,5,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,5,5,0,0,5,5,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,5,5,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,5,5,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,5,5,0,0,5,5,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
}
void Nibbler::init()
{
    _snake.first = 25;
    _snake.second = 13;
    generatePrey();
    for (int i = 0; i < 4; i++) {
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

void Nibbler::generateTail()
{
    if (_tailsN > 0) {
        int prevx = _snake.first + 1;
        int prevy = _snake.second + 1;
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
void Nibbler::avoidWall(std::string &key)
{
    if (key == "RIGHT" && _map[_snake.second][_snake.first] == 5) {
        if (_map[_snake.second - 1][_snake.first] == 5) {
            _snake.second++;
            key = "DOWN";
        }
        else if (_map[_snake.second][_snake.first] == 5) {
            _snake.second--;
            key = "UP";
        }
        else
            _snake.first++;
    }
    if (key == "LEFT" && _map[_snake.second][_snake.first] == 5) {
        if (_map[_snake.second - 1][_snake.first] == 5) {
            _snake.second++;
            key = "DOWN";
        }
        else if (_map[_snake.second][_snake.first] == 5) {
            _snake.second--;
            key = "UP";
        }
        else
            _snake.first--;
    }
    if (key == "DOWN" && _map[_snake.second][_snake.first] == 5) {
        if (_map[_snake.second][_snake.first - 1] == 5) {
            _snake.first++;
            key = "RIGHT";
        }
        else if (_map[_snake.second][_snake.first + 1] == 5) {
            _snake.first--;
            key = "LEFT";
        }
        else
            _snake.second++;
    }
    if (key == "UP" && _map[_snake.second ][_snake.first] == 5) {
        if (_map[_snake.second][_snake.first - 1] == 5) {
            _snake.first++;
            key = "RIGHT";
        }
        else if (_map[_snake.second][_snake.first + 1] == 5) {
            _snake.first--;
            key = "LEFT";
        }
        else
        _snake.second--;
    }
}

void Nibbler::update(std::string key)
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
    avoidWall(key);
    
    if (_snake.first == _prey.first && _snake.second == _prey.second) {
        _score++;
        generatePrey();
        _tailsN++;
        _tailsC.first.push_back(_tailsC.first.back());
        _tailsC.second.push_back(_tailsC.second.back());
    }
    renderMap();
    if (_snake.second == 0)
        _snake.second = _height - 2;
    else if (_snake.second == _height - 1)
        _snake.second = 1;

    if (_snake.first == 0)
        _snake.first = _width - 2;
    else if (_snake.first == _width - 1)
        _snake.first = 1;

    for (int k = 4; k < _tailsN; k++)
        if (_tailsC.first[k] == _snake.first && _tailsC.second[k] == _snake.second)
            _gameOver = true;
}
IGames *create()
{
    return new Nibbler();
}
