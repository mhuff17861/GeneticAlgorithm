/*
 *  Direction.cpp
 *  CIS 250
 *  David Klick
 *  2014-03-12
 *    
 *  This is part of a program that creates a maze. This class is the
 *  implementation file for the class that represents directions in
 *  the maze.
 */
#include "Direction.h"

int Direction::row(direction d) {
    int y;
    switch (d) {
        case NORTH: y = -1; break;
        case EAST:  y =  0; break;
        case SOUTH: y =  1; break;
        case WEST:  y =  0; break;
    }
    return y;
}

int Direction::col(direction d) {
    int x;
    switch (d) {
        case NORTH: x =  0; break;
        case EAST:  x =  1; break;
        case SOUTH: x =  0; break;
        case WEST:  x = -1; break;
    }
    return x;
}

direction Direction::opposite(direction d) {
    direction opp;
    switch (d) {
        case NORTH: opp = SOUTH; break;
        case EAST:  opp =  WEST; break;
        case SOUTH: opp = NORTH; break;
        case WEST:  opp =  EAST; break;
    }
    return opp;
}

direction Direction::right(direction d) {
    direction opp;
    switch (d) {
        case NORTH: opp = EAST; break;
        case EAST:  opp =  SOUTH; break;
        case SOUTH: opp = WEST; break;
        case WEST:  opp =  NORTH; break;
    }
    return opp;
}

direction Direction::left(direction d) {
    direction opp;
    switch (d) {
        case NORTH: opp = WEST; break;
        case EAST:  opp =  NORTH; break;
        case SOUTH: opp = EAST; break;
        case WEST:  opp =  SOUTH; break;
    }
    return opp;
}

char Direction::abbr(direction d) {
    char c;
    switch (d) {
        case NORTH: c = 'N'; break;
        case EAST:  c = 'E'; break;
        case SOUTH: c = 'S'; break;
        case WEST:  c = 'W'; break;
    }
    return c;
}

ostream& operator<<(ostream& strm, const direction d) {
    strm << Direction::abbr(d);
    return strm;
}
