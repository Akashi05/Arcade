/*
** Games.hpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/include
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:48:48 PM 2025 ramziathzakari@epitech.eu
** Last update Sat Apr 11 8:45:52 AM 2025 ramziathzakari@epitech.eu
*/

#ifndef GAMES_HPP_
# define GAMES_HPP_


#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <iostream>
class IGames {
    public:
        IGames() {}
        ~IGames() = default;
        virtual void init() = 0;
        virtual int getPlayerLive() = 0;
        virtual int getPlayerScore() = 0;
        virtual void update(std::string key) = 0;
        virtual std::vector<std::vector<int>> getState() = 0;
        virtual bool is_gameEnd() = 0;
        //virtual void setPlayerScore(int score) = 0;
        //virtual void saveState() = 0;
    protected:
    private:
};
class AGames : public IGames
{
    public:
        AGames() {}
        ~AGames() = default;
        int getPlayerLive() override {
            return _life;
        }
        int getPlayerScore() override {
            return _score;
        }
        std::vector<std::vector<int>> getState() override {
            return _map;
        }
        bool is_gameEnd() {
            return _gameOver;
        }
    protected:
        std::vector<std::vector<int>> _map;
        int _score;
        int _life;
        bool _gameOver;
    private:
};

#endif /* !GAMES_HPP_ */
