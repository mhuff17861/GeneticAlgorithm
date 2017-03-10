/*
 *  Board.h
 *  CIS 250
 *  David Klick
 *  2014-03-12
 *    
 *  This is part of a program that creates a maze. This class is the header
 *  file for the class that represents the maze itself, which consists of
 *  Cell objects.
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "Direction.h"
#include "Cell.h"
#include "vector"
#include <iostream>
using std::vector;
using std::ostream;

class Board {
private:
    int rows, cols;
    Cell* startCell;
    Cell* endCell;
    static const int MAX_ROWS = 100, MAX_COLS = 100;
public:
    Cell* board;
    Board(const int r, const int c);
    Cell* getStartCell();
    Cell* getEndCell();
    void setStartCell(Cell* c);
    void setEndCell(Cell* c);
    Cell* getCell(const int r, const int c) const;
    Cell* getAdjacentCell(Cell* c, direction d);
    void connect(Cell* cell1, direction d);
    int getRows() const;
    int getCols() const;
    void clearVisited();
    void clearValues();
    friend ostream& operator<<(ostream& strm, Board& b);
    void getUnvisitedConnectedNeighbors(Cell* c, vector<direction>& v);
    void getUnvisitedNeighbors(Cell* c, vector<direction>& v);
    void getConnectedNeighbors(Cell* c, vector<direction>& v);
};

#endif
