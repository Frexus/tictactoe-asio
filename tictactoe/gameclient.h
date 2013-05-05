#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <iostream>
#include <boost/asio.hpp>
#include "messages.h"
#include "board.h"
#include "mainmenu.h"
#include <ncurses.h>
#include <fstream>
#include <array>

using boost::asio::ip::tcp;

class GameClient
{
private:
    boost::asio::io_service* service;
    tcp::resolver::query query;
    tcp::resolver::iterator iterator;
    tcp::socket socket;

    message msg;
    bool game_started;
    Board board;
    MainMenu menu;

public:
    GameClient(boost::asio::io_service *srv, char* host = "", char* port = "");

    void printMessage(const std::string& msg);
    void clearMessage();
    void printMenu();
    void printBoard();
    void mainLoop();
    void receiveMessage();
    void processInput();
    void connect();
    void disconnect();
    void sendMessage(const message &m);
    void run();
    void loadGame();

};

#endif // GAMECLIENT_H
