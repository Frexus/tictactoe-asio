#include "board.h"

WINDOW* Board::createWindow(int startx, int starty, int height, int width)
{
    WINDOW* local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);		/* 0, 0 gives default characters
                     * for the vertical and horizontal
                     * lines			*/
    return local_win;
}

void Board::deleteWindow(WINDOW* local_win)
{
    //wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    //wrefresh(local_win);
    delwin(local_win);
}

void Board::selectWindow(int x, int y)
{
    wattron(segments[selected_x][selected_y], COLOR_PAIR(0));
    box(segments[selected_x][selected_y],0,0);
    wrefresh(segments[selected_x][selected_y]);
    wattroff(segments[selected_x][selected_y], COLOR_PAIR(0));

    selected_x = x;
    selected_y = y;

    wattron(segments[selected_x][selected_y], COLOR_PAIR(1));
    box(segments[selected_x][selected_y],0,0);
    wrefresh(segments[selected_x][selected_y]);
    wattroff(segments[selected_x][selected_y], COLOR_PAIR(1));
    //wbkgd(segments[selected_x][selected_y], COLOR_PAIR(1));
}


Board::Board(int x, int y, int width, int height)
    : can_go_down(true),
      can_go_up(false),
      can_go_right(true),
      can_go_left(false),
      selected_x(0),
      selected_y(0)
{
    segment_width = width / BOARD_SIZE;
    segment_height = height / BOARD_SIZE;
    start_x = x;
    start_y = y;
}

void Board::show()
{
    for(int i=0; i < BOARD_SIZE; ++i)
    {
        for(int j = 0; j < BOARD_SIZE; ++j)
        {
            if(i == 0)
            {
                char tmp[2];
                sprintf(tmp, "%d", j+1);
                mvaddstr(start_y, start_x + j * segment_width + segment_width/2 + 2, tmp);
            }
            segments[i][j] = createWindow(j * segment_width + start_x + 2, i * segment_height + start_y + 2, segment_height, segment_width);
            chars[i][j] = 0;
        }
        //mvaddch(start_x, i * segment_height, 'A');
        mvaddch(start_y + i * segment_height + segment_height/2 + 2, start_x, 'A' + i);
    }
    selectWindow(selected_x, selected_y);
    for(int i=0; i < BOARD_SIZE; ++i)
    {
        for(int j = 0; j < BOARD_SIZE; ++j)
        {
            wrefresh(segments[i][j]);
        }
    }
}

void Board::putChar(char ch)
{
//    for(int i=0; i < segment_width-2; ++i)
//    {
//        for(int j = 0; j < segment_height-2; ++j)
//        {
//            mvwprintw(segments[selected_x][selected_y], j+2, i+2, "%c", ch);
//            mvwprintw(segments[selected_x][selected_y], segment_height-j-2, segment_width-i-2, "%c", ch);
//        }
//    }
    mvwinsch(segments[selected_x][selected_y], segment_height/2, segment_width/2, ch);
    //box(segments[selected_x][selected_y], 0, 0);
    wrefresh(segments[selected_x][selected_y]);
    chars[selected_x][selected_y] = ch;
}

void Board::putCharAt(char ch, message field)
{
    int x = (field+BOARD_SIZE-1)/BOARD_SIZE-1;
    int y = field - x*3 - 1;
    mvwinsch(segments[x][y], segment_height/2, segment_width/2, ch);
    wrefresh(segments[x][y]);
    chars[x][y] = ch;
}

char Board::getCharAtSelectedField()
{
    return chars[selected_x][selected_y];
}

void Board::moveLeft()
{
    if(can_go_left)
    {
        selectWindow(selected_x, selected_y-1);
    }
    updateMove();
}

void Board::moveRight()
{
    if(can_go_right)
    {
        selectWindow(selected_x, selected_y+1);
    }
    updateMove();
}

void Board::moveUp()
{
    if(can_go_up)
    {
        selectWindow(selected_x-1, selected_y);
    }
    updateMove();
}

void Board::moveDown()
{
    if(can_go_down)
    {
        selectWindow(selected_x+1, selected_y);
    }
    updateMove();
}

message Board::getSelectedWindow()
{
    return static_cast<message>(selected_y+selected_x*BOARD_SIZE+1);
}

void Board::clear()
{
    for(int i=0 ; i < BOARD_SIZE; ++i)
    {
        for(int j = 0; j < BOARD_SIZE; ++j)
        {
            werase(segments[i][j]);
            wrefresh(segments[i][j]);
        }
    }
}

void Board::setChars(std::array<std::array<char, 3>, 3> & arr)
{
    for(int i=0; i < BOARD_SIZE; ++i)
    {
        for(int j = 0; j < BOARD_SIZE; ++j)
        {
            chars[i][j] = arr[i][j];
            if(arr[i][j] != 0)
            {
                putCharAt(arr[i][j], static_cast<message>(j+i*BOARD_SIZE+1));
            }
        }
    }
}

Board::~Board()
{
    for(int i=0; i < BOARD_SIZE; ++i)
    {
        for(int j = 0; j < BOARD_SIZE; ++j)
        {
            deleteWindow(segments[i][j]);
        }
    }
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


void Board::updateMove()
{
    if(selected_y == 2)
        can_go_right = false;
    else if(selected_y == 0)
        can_go_left = false;
    else
        can_go_left = can_go_right = true;

    if(selected_x == 2)
        can_go_down = false;
    else if(selected_x == 0)
        can_go_up = false;
    else
        can_go_up = can_go_down = true;
}



