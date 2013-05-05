#include "board.h"

Board::Board()
{
    for(int i=0; i < 3; ++i)
    {
        for(int j=0; j < 3; ++j)
        {
            chars[i][j] = 0;
        }
    }
}

void Board::putCharAt(char ch, message field)
{
    int x = (field+BOARD_SIZE-1)/BOARD_SIZE-1;
    int y = field - x*3 - 1;
    chars[x][y] = ch;
}

char Board::checkWin()
{
    if((chars[0][0] == 'X' && chars[1][0] == 'X' && chars[2][0] == 'X') ||
            (chars[0][0] == 'X' && chars[0][1] == 'X' && chars[0][2] == 'X') ||
            (chars[2][0] == 'X' && chars[2][1] == 'X' && chars[2][2] == 'X') ||
            (chars[0][2] == 'X' && chars[1][2] == 'X' && chars[2][2] == 'X') ||
            (chars[0][0] == 'X' && chars[1][1] == 'X' && chars[2][2] == 'X'))
    {
        return 'X';
    }
    else if((chars[0][0] == 'O' && chars[1][0] == 'O' && chars[2][0] == 'O') ||
            (chars[0][0] == 'O' && chars[0][1] == 'O' && chars[0][2] == 'O') ||
            (chars[2][0] == 'O' && chars[2][1] == 'O' && chars[2][2] == 'O') ||
            (chars[0][2] == 'O' && chars[1][2] == 'O' && chars[2][2] == 'O') ||
            (chars[0][0] == 'O' && chars[1][1] == 'O' && chars[2][2] == 'O'))
    {
        return 'O';
    }
    else return 0;
}

std::array<std::array<char, 3>, 3> Board::getChars()
{
    std::array<std::array<char, 3>, 3> arr;
    for(int i=0; i < 3; ++i)
    {
        for(int j=0; j < 3; ++j)
        {
            arr[i][j] = chars[i][j];
        }
    }
    return arr;
}

