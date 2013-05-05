#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>
#include <array>
#include "messages.h"

#define BOARD_SIZE 3

class Board
{
    char chars[BOARD_SIZE][BOARD_SIZE];
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & chars;
    }

//    BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
    Board();
    void putCharAt(char ch, message field);
    char checkWin();
    std::array<std::array<char, 3>, 3> getChars();
};

#endif // BOARD_H
