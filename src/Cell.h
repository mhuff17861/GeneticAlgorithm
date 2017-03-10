/*
 *  Cell.h
 *  CIS 250
 *  David Klick
 *  2014-03-12
 *    
 *  This is part of a program that creates a maze. This class is the header
 *  file for the class that represents a individual room/cell in the maze.
 */

#ifndef __CELL_H__
#define __CELL_H__

#include <string>
#include <vector>
#include <iostream>
#include "Direction.h"
using std::string;
using std::vector;
using std::ostream;

class Cell {
private:
    int row, col;
    bool wallN, wallE, wallS, wallW;
    bool edgeN, edgeE, edgeS, edgeW;
    bool visited;
    int value;
    string strValue;
    void init(const int r, const int c);
public:
    Cell();
    Cell(const int r, const int c);
    vector<direction>& getNeighbors(vector<direction>& v) const;
    int getRow() const;
    int getCol() const;
    void setRow(const int r);
    void setCol(const int c);
    int getValue() const;
    string getStringValue() const;
    bool isVisited() const;
    bool hasWall(direction d) const;
    bool hasEdge(direction d) const;
    void setValue(const int n);
    void setStrValue(const string s);
    void setVisited();
    void setVisited(const bool v);
    void clearVisited();
    void setWall(const direction d);
    void setWall(const direction d, const bool b);
    void clearWall(const direction d);
    void setEdge(const direction d);
    void setEdge(const direction d, const bool b);
    void clearEdge(const direction d);
    int getNumberOfWalls() const;
    friend ostream& operator<<(ostream& strm, const Cell& c);
    friend ostream& operator<<(ostream& strm, const Cell* c);
};

#endif

