#ifndef BOARDCONTAINER_H
#define BOARDCONTAINER_H

#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/vector.hpp>
#include <array>
#include "messages.h"
#include "board.h"

#define BOARD_SIZE 3

class BoardContainer
{

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boards;
    }

//    BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
    std::vector<Board> boards;
    BoardContainer();

};

#endif // BOARDCONTAINER_H
