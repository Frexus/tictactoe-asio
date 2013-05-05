#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "messages.h"
#include "board.h"
#include "boardcontainer.h"

using boost::asio::ip::tcp;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

BoardContainer saves;

template<class T>
void swap(T& one, T& two)
{
    T tmp;
    tmp = one;
    one = two;
    two = tmp;
}

void session(socket_ptr player1, socket_ptr player2)
{
    try
    {
        Board b;
        message msg = GO_FIRST;
        boost::asio::write(*player1, boost::asio::buffer(&msg, sizeof(message)));
        char p1ch = 'X';
        msg = GO_SECOND;
        boost::asio::write(*player2, boost::asio::buffer(&msg, sizeof(message)));
        char p2ch = 'O';
        for (;;)
        {
            boost::asio::read(*player1, boost::asio::buffer(&msg, sizeof(message)));
            if(msg == SAVE)
            {
                std::ofstream ofs("saved_state.txt");
                boost::archive::text_oarchive oa(ofs);
                oa << b;
                std::cout << "SAVING GAME" << std::endl;
                continue;
            }
            if(msg == LOAD)
            {
                std::ifstream ifs("saved_state.txt");
                boost::archive::text_iarchive ia(ifs);
                ia >> b;
                std::cout << "LOADING GAME" << std::endl;
                boost::asio::write(*player2, boost::asio::buffer(&msg, sizeof(message)));
                std::array<std::array<char, 3>, 3> arr = b.getChars();
                boost::asio::write(*player1, boost::asio::buffer(&arr, sizeof(arr)));
                boost::asio::write(*player2, boost::asio::buffer(&arr, sizeof(arr)));
                assert(sizeof(arr) == 3*3*sizeof(char));
                continue;
            }
            b.putCharAt(p1ch, msg);
            boost::asio::write(*player2, boost::asio::buffer(&msg, sizeof(message)));
            boost::system::error_code error;
//            boost::asio::read(*player2, boost::asio::buffer(data, 3));
            if (!player1->is_open() || !player2->is_open())
            {
                player1->close();
                player2->close();
                break;
            }
            else if (error)
                throw boost::system::system_error(error);
//            boost::asio::write(*player1, boost::asio::buffer(data, 3));

            swap<socket_ptr>(player1, player2);
            swap<char>(p1ch, p2ch);
        }
    }
    catch (std::exception& e)
    {
        player1->close();
        player2->close();
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server(boost::asio::io_service& io_service, short port)
{
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
    for (;;)
    {
        socket_ptr player1(new tcp::socket(io_service));
        socket_ptr player2(new tcp::socket(io_service));
        a.accept(*player1);
        std::cout << "Accepted connection 1, waiting for more\n";
        a.accept(*player2);
        std::cout << "Accepted connection 2, running session\n";
        boost::thread t(boost::bind(session, player1, player2));
    }
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
            return 1;
        }
        std::cout << "Starting server\n";
        boost::asio::io_service io_service;

        using namespace std; // For atoi.
        server(io_service, atoi(argv[1]));
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
