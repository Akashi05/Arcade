##
## Makefile for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1
##
## Made by ramziathzakari@epitech.eu
## Login   <ramziathzakari@epitech.eu>
##
## Started on  Mon Mar 31 4:22:51 AM 2025 ramziathzakari@epitech.eu
## Last update Tue Apr 21 4:18:53 PM 2025 ramziathzakari@epitech.eu
##

all:	core	games	graphicals

core:
	mkdir -p lib
	g++ -o arcade src/Core/main.cpp src/Core/Core.cpp

games:
	g++ -shared -o lib/arcade_snake.so src/Games/Snake.cpp -fPIC
	g++ -shared -o lib/arcade_nibbler.so src/Games/Nibbler.cpp -fPIC

graphicals:
	g++ -shared -o lib/arcade_sfml.so src/Graphicals/SFML.cpp -fPIC -lsfml-graphics -lsfml-window -lsfml-system
	g++ -shared -o lib/arcade_sdl2.so src/Graphicals/SDL2.cpp -fPIC -lSDL2
	g++ -shared -o lib/arcade_ncurses.so src/Graphicals/Ncurses.cpp -fPIC -lncurses

CFLAGS		=	-std=c++20 -Wall -Wextra -Werror -g3

clean:
	rm -f *.gcno
	rm -f *.gcda
	rm -f *~
	rm -rf build

fclean:	clean
	rm -f arcade lib/*.so

re:	fclean all

.PHONY: all clean fclean re

