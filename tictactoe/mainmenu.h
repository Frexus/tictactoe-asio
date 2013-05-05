#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <ncurses.h>
#include "messages.h"
#include <vector>
#include <string>

class MainMenu
{
private:
    WINDOW* menu;
    std::vector<std::string> options;
    int current_pos;
    bool can_go_up;
    bool can_go_down;

    void goDown();
    void goUp();
    void printOpts();

public:
    MainMenu();

    void createWindow(int startx, int starty, int height, int width);
    void show();
    void erase();
    menu_opt getOption();

};

#endif // MAINMENU_H
