/*
 *  Cell.cpp
 *  CIS 250
 *  David Klick
 *  2014-03-12
 *    
 *  This is part of a program that creates a maze. This class is the implementation
 *  file for the class that represents a individual room/cell in the maze.
 *
 * Modified by: Micah Huff
 * Data: 3-28-2015
 */
#include "Cell.h"

vector<direction>& Cell::getNeighbors(vector<direction>& v) const {
    v.erase(v.begin(), v.end());
    if (!edgeN) v.push_back(NORTH);
    if (!edgeS) v.push_back(SOUTH);
    if (!edgeE) v.push_back(EAST);
    if (!edgeW) v.push_back(WEST);
    
    return v;
}

Cell::Cell() { init(0, 0); }

Cell::Cell(const int r, const int c) { init(r, c); }

void Cell::init(const int r, const int c) {
    wallN = wallE = wallS = wallW = true;
    edgeN = edgeE = edgeS = edgeW = false;
    row = r;
    col = c;
    visited = false;
    value = 0;
    strValue = "";
}

int Cell::getRow() const { return row; }

int Cell::getCol() const { return col; }

void Cell::setRow(const int r) { row = r; }

void Cell::setCol(const int c) { col = c; }

int Cell::getValue() const { return value; }

string Cell::getStringValue() const { return strValue; }

bool Cell::isVisited() const { return visited; }

bool Cell::hasWall(direction d) const {
    bool result = false;
    switch (d) {
        case NORTH: result = wallN; break;
        case  EAST: result = wallE; break;
        case SOUTH: result = wallS; break;
        case  WEST: result = wallW; break;
    }
    return result;
}

bool Cell::hasEdge(direction d) const {
    bool result = false;
    switch (d) {
        case NORTH: result = edgeN; break;
        case  EAST: result = edgeE; break;
        case SOUTH: result = edgeS; break;
        case  WEST: result = edgeW; break;
    }
    return result;
}

void Cell::setValue(const int n) { value = n; }

void Cell::setStrValue(const string s) { strValue = s; }

void Cell::setVisited() { setVisited(true); }

void Cell::setVisited(const bool v) { visited = v; }

void Cell::clearVisited() { visited = false; }

void Cell::setWall(const direction d) { setWall(d, true); }

void Cell::setWall(const direction d, const bool b) {
    switch (d) {
        case NORTH: wallN = b; break;
        case  EAST: wallE = b; break;
        case SOUTH: wallS = b; break;
        case  WEST: wallW = b; break;
    }
}

void Cell::clearWall(const direction d) { setWall(d, false); }

void Cell::setEdge(const direction d) { setEdge(d, true); }

void Cell::setEdge(const direction d, const bool b) {
    switch (d) {
        case NORTH: edgeN = b; break;
        case  EAST: edgeE = b; break;
        case SOUTH: edgeS = b; break;
        case  WEST: edgeW = b; break;
    }
}

void Cell::clearEdge(const direction d) { setEdge(d, false); }

int Cell::getNumberOfWalls() const {
    return (wallN?1:0) + (wallE?1:0) + (wallS?1:0) + (wallW?1:0);
}

ostream& operator<<(ostream& strm, const Cell& c) {
    strm << "Cell[" << c.row << "][" << c.col << "] ";
    return strm;
}

ostream& operator<<(ostream& strm, const Cell* c) {
    strm << "Cell[" << c->row << "][" << c->col << "] ";
    return strm;
}

