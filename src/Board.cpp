/*
 *  Board.cpp
 *  CIS 250
 *  David Klick
 *  2014-03-12
 *    
 *  This is part of a program that creates a maze. This class represents 
 *  the maze itself, which consists of Cell objects.
 *
 * Modified By: Micah Huff
 * Date: 3-28-2016
 */
#include "Board.h"

void Board::getUnvisitedConnectedNeighbors(Cell* c, vector<direction>& v) {
    v.erase(v.begin(), v.end());   
    vector<direction> neighbors; 
    getConnectedNeighbors(c, neighbors);
    //use loop to go through connected neighbors and discover unvisted
    for (unsigned int i = 0; i<neighbors.size(); i++) {
	Cell* chk;
	//still need to figure this out!
	chk = getCell(c->getRow() + Direction::row(neighbors.at(i)),c->getCol() + Direction::col(neighbors.at(i)));
	if (!chk->isVisited()) v.push_back(neighbors.at(i));
    }
}

void Board::getConnectedNeighbors(Cell* c, vector<direction>& v) {
    v.erase(v.begin(), v.end());   
    if (!c->hasWall(NORTH) && !c->hasEdge(NORTH)) v.push_back(NORTH);
    if (!c->hasWall(SOUTH) && !c->hasEdge(SOUTH)) v.push_back(SOUTH);
    if (!c->hasWall(EAST) && !c->hasEdge(EAST)) v.push_back(EAST);
    if (!c->hasWall(WEST) && !c->hasEdge(WEST)) v.push_back(WEST);
}

void Board::getUnvisitedNeighbors(Cell* c, vector<direction>& v) {
    v.erase(v.begin(), v.end());   
    vector<direction> neighbors; 
    c->getNeighbors(neighbors);
    //use loop to go through connected neighbors and discover unvisted
    for (unsigned int i = 0; i<neighbors.size(); i++) {
	Cell* chk;
	//still need to figure this out!
	chk = getCell(c->getRow() + Direction::row(neighbors.at(i)),c->getCol() + Direction::col(neighbors.at(i)));
	if (!chk->isVisited()) v.push_back(neighbors.at(i));
    }
}

Board::Board(const int r, const int c) {
    if (r<1 || r>MAX_ROWS) throw "Error: Rows value out of bounds";
    if (c<1 || c>MAX_COLS) throw "Error: Columns value out of bounds";
    rows = r;
    cols = c;
    board = new Cell[rows*cols];
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            Cell* cl = (board + i*cols + j);
            cl->setRow(i);
            cl->setCol(j);
            if (i == 0) cl->setEdge(NORTH);
            if (i == rows-1) cl->setEdge(SOUTH);
            if (j == cols-1) cl->setEdge(EAST);
            if (j == 0) cl->setEdge(WEST);
        }
    }
}

Cell* Board::getStartCell() { return startCell; }
Cell* Board::getEndCell() { return endCell; }
void Board::setStartCell(Cell* c) { startCell = c; }
void Board::setEndCell(Cell* c) { endCell = c; }
Cell* Board::getCell(const int r, const int c) const { return board + r * cols + c; }

Cell* Board::getAdjacentCell(Cell* cl, direction d) {
    int r = cl->getRow() + Direction::row(d);
    int c = cl->getCol() + Direction::col(d);
    return (board + r*cols + c);
}

void Board::connect(Cell* cell1, direction d) {
    cell1->clearWall(d);
    getAdjacentCell(cell1, d)->clearWall(Direction::opposite(d));
}

int Board::getRows() const { return rows; }
int Board::getCols() const { return cols; }
void Board::clearVisited() {
    for (int i=0; i<rows*cols; i++) (board+i)->setVisited(false);
}
void Board::clearValues() {
    for (int i=0; i<rows*cols; i++) (board+i)->setValue(0);
}

ostream& operator<<(ostream& strm, Board& b) {
    int r, c;
    Cell* x;
    for (c=0; c<b.cols; c++) {
        if (b.startCell->getCol() == c) strm << "  ";
        else strm << " _";
    }
    strm << "\n";
    for (r=0; r<b.rows-1; r++) {
        for (c=0; c<b.cols; c++) {
            x = b.getCell(r, c);
            if (x->hasWall(WEST)) strm << '|';
            else strm << ' ';
            if (x->hasWall(SOUTH)) strm << '_';
            else strm << ' ';
        }
        strm << "|\n";
    }
    for (c=0; c<b.cols; c++) {
        x = b.getCell(b.rows-1, c);
        if (x->hasWall(WEST)) strm << '|';
        else strm << ' ';
        if (b.endCell->getCol() == c) strm << ' ';
        else strm << '_';
    }
    strm << "|\n";
    return strm;
}
