/*
** Graphicals.cpp for B-OOP-400-COT-4-1-arcade-berenger.sessou-1 [WSL: Ubuntu] in /home/ramziath/B-OOP-400-COT-4-1-arcade-berenger.sessou-1/src/Graphicals
**
** Made by ramziathzakari@epitech.eu
** Login   <ramziathzakari@epitech.eu>
**
** Started on  Thu Mar 27 2:50:18 PM 2025 ramziathzakari@epitech.eu
** Last update Mon Apr 13 2:30:30 AM 2025 ramziathzakari@epitech.eu
*/

#include <ncurses.h>
#include "../../include/Ncurses.hpp"

void NCursesDisplay::rectangle(WINDOW *win, int y1, int x1, int y2, int x2)
{
    mvwhline(win, y1, x1, 0, x2-x1);
    mvwhline(win, y2, x1, 0, x2-x1);
    mvwvline(win, y1, x1, 0, y2-y1);
    mvwvline(win, y1, x2, 0, y2-y1);
    mvwaddch(win, y1, x1, ACS_ULCORNER);
    mvwaddch(win, y2, x1, ACS_LLCORNER);
    mvwaddch(win, y1, x2, ACS_URCORNER);
    mvwaddch(win, y2, x2, ACS_LRCORNER);
    wrefresh(win);
}

void NCursesDisplay::init()
{   
    initscr();
    noecho(); 
    curs_set(0); 
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    }

    _isOpen = true;
}

bool NCursesDisplay::isOpen()
{
    return _isOpen;
}

std::string NCursesDisplay::handleEvents(std::string &direction)
{
    int ch = getch();
    switch (ch) {
        case KEY_UP:
            direction = "UP";
            return direction;
            break;
        case KEY_DOWN:
            direction = "DOWN";
            return direction;
            break;
        case KEY_LEFT:
            direction = "LEFT";
            return direction;
            break;
        case KEY_RIGHT:
            direction = "RIGHT";
            return direction;
            break;
        case '1':
            direction = "SWITCH_LIB:arcade_sdl.so";
            return direction;
            break;
        case '2':
            direction = "SWITCH_LIB:arcade_sfml.so";
            return direction;
            break;
        case 'n':
            direction = "NEXT_GAME";
            return direction;
            break;
        case 'q':
            direction = "QUIT";
            return direction;
            break;
        case 'm':
        case 'M':
            direction = "m";
            return direction;
            break;
        default:
            break;
    }
    return direction;
}

void NCursesDisplay::setActualGame(std::string game)
{
    actualgame = game;
}

void NCursesDisplay::setActualLibrary(std::string library)
{
    actualLibrary = library;
}

std::string NCursesDisplay::getActualGame()
{
    return actualgame;
}

std::string NCursesDisplay::getActualLibrary()
{
    return  actualLibrary;
}

void NCursesDisplay::display_game_over() {
    clear();
    int y = LINES / 2 - 4;
    int x = (COLS - 53) / 2;

    mvprintw(y++, x, "   ____                         ___                 ");
    mvprintw(y++, x, "  / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __ ");
    mvprintw(y++, x, " | |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|");
    mvprintw(y++, x, " | |_| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |   ");
    mvprintw(y++, x, "  \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   ");
    mvprintw(y + 2, (COLS - 34) / 2, "Appuyez sur M pour retourner au menu");
    refresh();
}

void NCursesDisplay::clear()
{
    ::clear();
}

void NCursesDisplay::display_score(int score)
{
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    int start_x = cols - 30;
    int start_y = 1;
    
    rectangle(stdscr, start_y, start_x, start_y + 2, start_x + 28);
    mvprintw(start_y + 1, start_x + 2, "SCORE: %d", score);
    refresh();
}


void NCursesDisplay::display_menu()
{
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    int start_x = cols - 90;
    int start_y = 1;
    clear();
    win = newwin(rows - 2, cols - 2, 1, 1);
    
    if (!win) {
        std::cerr << "Erreur : Impossible de créer la fenêtre !" << std::endl;
        endwin();
        return;
    }
    keypad(win, true);
    box(win, '*', '.');
    wrefresh(win);
    
    games = {"arcade_snake.so", "arcade_nibbler.so"};
    graphics = {"arcade_ncurses.so", "arcade_sdl2.so", "arcade_sfml.so"};

    rectangle(win, 5, 8, 15, 38);
    rectangle(win, 5, 50, 15, 80);
    rectangle(win, 5, 92, 15, 128);
    rectangle(win, 20, 8, 3, 128);

    mvwprintw(win, 6, 10, "%s", "Games libraries available");
    mvwhline(win, 7, 10, '-', 28);
    
    mvwprintw(win, 6, 52, "%s", "Graphics libraries available");
    mvwhline(win, 7, 52, '-', 28);
    
    mvwprintw(win, 6, 100, "%s", "Best Scores");
    mvwhline(win, 7, 94, '-', 32);
    mvwprintw(win, 9, 95, "%s", "Snake: Player Be score: 115 pts");
    mvwprintw(win, 12, 95, "%s", "Nibble: Player King score: 61 pts");
    
    mvwprintw(win, 21, 37, "%s", "Enter Your name:");
    mvwvline(win, 21, 35, 0, 1);
    mvwvline(win, 21, 85, 0, 1);
    mvwhline(win, 22, 35, '-', 50);
   
    for (int i = 0; i < 2; i++) {
	    if (row_high == i && col_high == 0)
            wattron(win, A_REVERSE);
	    mvwprintw(win, 9 + i * 2, 10,"%s", games[i].c_str());
	    wattroff(win, A_REVERSE);
    }
        
    for (int i = 0; i < 3; i++) {
	    if (row_high == i && col_high == 1)
            wattron(win, A_REVERSE);
	    mvwprintw(win, 9 + i * 2, 52, "%s", graphics[i].c_str());
	    wattroff(win, A_REVERSE);
    }

    std::string name;
    int state = wgetch(win);
    /*if (((state >= 'a' && state <= 'z') || (state >= 'A' && state <= 'Z')) && state != 'q')  {
        //name += state;
        wgetstr(win, name.data());
        mvwprintw(win, 21, 55, "%s", name.c_str());
    } else {*/
        switch (state) {
            case KEY_UP:
	            row_high--;
	            if (row_high < 0)
	                row_high = 0;
	            break;
            case KEY_DOWN:
	            row_high++;
	            if (col_high == 0 && row_high >= 2)
	                row_high = games.size() - 1;
	            if (col_high == 1 && row_high >= 3)
	                row_high = graphics.size() - 1;
	            break;
            case KEY_LEFT:
	            col_high--;
	            if (col_high < 0) {
	                col_high = 0;
	                row_high = 0;
	            }
	            break;
            case KEY_RIGHT:
	            col_high++;
	            if (col_high > 1) {
	                col_high = 1;
	                row_high = 0;
	            }
	            break;
            case '\n':
	            if (col_high == 0 && (games[row_high] == "arcade_snake.so"))
	                actualgame = "./lib/arcade_snake.so";
	            if (col_high == 0 && (games[row_high] == "arcade_nibbler.so"))
	                actualgame = "./lib/arcade_nibbler.so";
	            if (col_high == 1 && (graphics[row_high] == "arcade_sfml.so")) {
	                _isOpen = false;
	                actualLibrary = "./lib/arcade_sfml.so";
	            }
	            wrefresh(win);
	            break;
            case 'q':
	            _isOpen = false;
	            actualLibrary = "";
	            break;
            default:
	            break;
        }
        clear();
        wrefresh(win);
        clear();
        delwin(win);
}

void NCursesDisplay::close()
{
    endwin();
    _isOpen = false;
}

void NCursesDisplay::display_state(const std::vector<std::vector<int>> &map)
{
    clear();
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 1 || map[i][j] == 5) {
                attron(COLOR_PAIR(1));
                mvaddch(i, j, '#');
                attron(COLOR_PAIR(1));
            } else if (map[i][j] == 2) {
                mvaddch(i, j, 'O');
            } else if (map[i][j] == 3) {
                attron(COLOR_PAIR(2));
                mvaddch(i, j, 'P');
                attron(COLOR_PAIR(2));
            } else if (map[i][j] == 4) {
                attron(COLOR_PAIR(3));
                mvaddch(i, j, 'o');
                attron(COLOR_PAIR(3));
            } else
                mvaddch(i, j, ' ');
        }
    }
    refresh();
}

IDisplay *create()
{
    return new NCursesDisplay();
}
