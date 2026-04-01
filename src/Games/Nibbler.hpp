/*
** Games.cpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/src/Games
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:49:26 PM 2025 ramziathzakari@epitech.eu
** Last update Sat Apr 11 8:52:02 AM 2025 ramziathzakari@epitech.eu
*/

#include "../../include/Games.hpp"

class Nibbler : public AGames
{
    public:
        Nibbler();
        ~Nibbler() = default;
        void init() override;
        void update(std::string) override;
        void renderMap();
        void generatePrey();
        void generateTail();
        void genMap();
        void avoidWall(std::string &key);
    private:    
        int _height;
        int _width;
        int _tailsN;
        std::pair<std::vector<int>, std::vector<int>> _tailsC;
        std::pair<int, int> _snake;
        std::pair<int, int> _prey;
};
extern "C" {
    IGames *create();
};