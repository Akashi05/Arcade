/*
** Graphicals.hpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/include
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:48:34 PM 2025 ramziathzakari@epitech.eu
** Last update Tue Mar 31 11:47:47 AM 2025 ramziathzakari@epitech.eu
*/

#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>
#include <exception>

class Error: public std::exception
{
    private:
    std::string message;
    public:
    Error(const std::string &mess) : message(mess) {}
    const char* what() const throw () {
        return message.c_str();
    }
    Error() = default;
    ~Error() = default;
};

#endif