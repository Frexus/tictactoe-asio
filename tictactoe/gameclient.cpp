#include "gameclient.h"

GameClient::GameClient(boost::asio::io_service *srv, char* host, char* port)
    :
      service(srv),
      board(COLS/2-42, LINES/2-15, 42, 15),
      query(tcp::v4(), host, port),
      socket(*service)
{
    tcp::resolver resolver(*service);
    iterator = resolver.resolve(query);
}

void GameClient::printMessage(const std::string &msg)
{
    clearMessage();
    mvprintw(5, COLS-50, "%s", msg.c_str());
}

void GameClient::clearMessage()
{
    move(5, COLS-50);
    clrtoeol();
}


void GameClient::processInput()
{
    int ch;
    bool done = false;
    while(!done)
    {
        ch = wgetch(stdscr);
        switch(ch)
        {
        case KEY_LEFT:
            board.moveLeft();
            break;
        case KEY_RIGHT:
            board.moveRight();
            break;
        case KEY_UP:
            board.moveUp();
            break;
        case KEY_DOWN:
            board.moveDown();
            break;
        case KEY_F(4):
            msg = SAVE;
            done = true;
            break;
        case KEY_F(6):
            msg = LOAD;
            done = true;
            break;
        case '\n':
            msg = board.getSelectedWindow();
            if(!board.getCharAtSelectedField())
            {
                clearMessage();
                board.putChar('X');
                done = true;
            }
            else
            {
                printMessage("You can't put X here.");
            }
            break;
        }
    }
}

void GameClient::connect()
{
    boost::asio::connect(socket, iterator);
}

void GameClient::disconnect()
{
    boost::system::error_code err;
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, err);
    socket.close();
}

void GameClient::sendMessage(const message &m)
{
    boost::asio::write(socket, boost::asio::buffer(&msg, sizeof(message)));
}


void GameClient::receiveMessage()
{
    boost::asio::read(socket, boost::asio::buffer(&msg, sizeof(message)));

}


void GameClient::printBoard()
{
    board.show();
    processInput();
}

void GameClient::mainLoop()
{
    connect();
    mvprintw(LINES-3,0,"Arrow keys to move.\nF4 to save game.\nF6 to load game.");
    board.show();
    //boost::asio::read(socket, boost::asio::buffer(&msg, sizeof(message)));
    receiveMessage();
    bool turn = msg == GO_FIRST ? 1 : 0;
    bool done = false;
    while(!done)
    {
        if(turn)
        {
            processInput();
            sendMessage(msg); // send my move
            if(msg == SAVE)
                continue;
            if(msg == LOAD)
            {
                loadGame();
                continue;
            }
        }
        else
        {
            receiveMessage(); // get enemy move
            if(msg == LOAD)
            {
                loadGame();
                continue;
            }
            board.putCharAt('O', msg);
        }
        char win = board.checkWin();
        if(win == 'X')
        {
            printMessage("You won! Press anything.");
            done = true;
        }
        else if (win == 'O')
        {
            printMessage("You lose. Press anything.");
            done = true;
        }
        turn = true ^ turn;
    }
    wgetch(stdscr);
    disconnect();
    board.clear();
    wclear(stdscr);
    werase(stdscr);
    refresh();
    printMenu();
}

void GameClient::printMenu()
{
    menu.show();
    menu_opt option = menu.getOption();
    if(option == MENU_START_GAME)
    {
        menu.erase();
        mainLoop();
    }
}


void GameClient::run()
{
    printMenu();
}

void GameClient::loadGame()
{
    std::array<std::array<char, 3>, 3> arr;
    boost::asio::read(socket, boost::asio::buffer(&arr, sizeof(char)*3*3));
    board.setChars(arr);
    printMessage("Game loaded.");
}
