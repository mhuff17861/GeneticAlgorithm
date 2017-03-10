/*
 *  Direction.h
 *  CIS 250
 *  David Klick
 *  2014-03-12
 *    
 *  This is part of a program that creates a maze. This class is the
 *  header file for the class that represents directions in the maze.
 */
#ifndef __DIRECTION_H__
#define __DIRECTION_H__
#include <iostream>
using std::ostream;

enum direction { NORTH=1, EAST=2, SOUTH=4, WEST=8 };

ostream& operator<<(ostream& strm, const direction d);

class Direction {
public:
    static int row(direction d);
    static int col(direction d);
    static direction opposite(direction d);
    static direction right(direction d);
    static direction left(direction d);
    static char abbr(direction d);
};

#endif

