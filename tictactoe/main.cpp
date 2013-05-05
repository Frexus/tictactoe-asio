#include <iostream>
#include <ncurses.h>
#include "board.h"
#include "mainmenu.h"
#include "gameclient.h"

using namespace std;

int main(int argc, char* argv[])
{
    initscr();
    start_color();
    refresh();
    cbreak();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_GREEN, COLOR_WHITE);
    curs_set(0);

    GameClient g(new boost::asio::io_service(), argv[1], argv[2]);
    g.run();

    endwin();
}

