#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include "messages.h"
#include <array>

#define BOARD_SIZE 3

class Board
{
private:
    WINDOW* segments[BOARD_SIZE][BOARD_SIZE];
    char chars[BOARD_SIZE][BOARD_SIZE];
    int segment_width;
    int segment_height;
    int start_x;
    int start_y;
    bool can_go_left, can_go_right, can_go_up, can_go_down;
    int selected_x, selected_y;

public:
    Board(int x, int y, int width, int height);
    void show();
    void putChar(char ch);
    void putCharAt(char ch, message field);
    ~Board();
    char checkWin();
    char getCharAtSelectedField();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    message getSelectedWindow();
    void clear();
    void setChars(std::array<std::array<char, 3>, 3> &arr);

private:
    WINDOW* createWindow(int startx, int starty, int height, int width);
    void deleteWindow(WINDOW* local_win);
    void selectWindow(int x, int y);
    void updateMove();
};

#endif // BOARD_H
