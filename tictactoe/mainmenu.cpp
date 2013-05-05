#include "mainmenu.h"

MainMenu::MainMenu()
{
    createWindow(1, 1, 10, 10);
    options.push_back("PLAY");
    options.push_back("QUIT");
    can_go_up = false;
    can_go_down = true;
    current_pos = 1;
    init_pair(2, COLOR_RED, COLOR_BLUE);
}

void MainMenu::createWindow(int startx, int starty, int height, int width)
{
    menu = newwin(height, width, starty, startx);
    box(menu, 0 , 0);
}

void MainMenu::show()
{
    wrefresh(menu);
}

void MainMenu::erase()
{
    werase(menu);
    wrefresh(menu);
}

menu_opt MainMenu::getOption()
{
    int ch;
    printOpts();
    menu_opt chosen_opt;
    bool chosen = false;
    this->show();
    while(!chosen)
    {
        printOpts();
        ch = wgetch(stdscr);
        switch(ch)
        {
        case KEY_UP:
            goUp();
            break;
        case KEY_DOWN:
            goDown();
            break;
        case '\n':
            chosen_opt = static_cast<menu_opt>(current_pos);
            chosen = true;
            break;
        }
    }
    return chosen_opt;
}


void MainMenu::goDown()
{
    if(current_pos < options.size())
    {
        current_pos++;
    }

}

void MainMenu::goUp()
{
    if(current_pos >= 0)
    {
        current_pos--;
    }

}

void MainMenu::printOpts()
{
    werase(menu);
    for(int i=1; i <= options.size(); ++i)
    {
        if(i == current_pos)
        {
            mvwprintw(menu, i+2, 1+options[i-1].length()+1, "<<");
        }
        mvwprintw(menu, i+2, 1, options[i-1].c_str());
    }
    wrefresh(menu);
}
