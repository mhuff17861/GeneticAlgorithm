/*
 *  Maze.cpp
 *  CIS 250
 *  David Klick
 *  2014-03-12
 *    
 *  This program creates a maze.
 *  Note: Leave the commented program statements in for later inclusion
 *        in the maze-solving version of this program.
 *
 * Modified By: Micah Huff
 * Date: 4-2-2016
 * 
 */
#include "Maze.h"

//set static variables
int Maze::DEFAULT_ROWS = 10;
int Maze::DEFAULT_COLS = 10;
bool Maze::randInit = false;

Maze::Maze() : Board(Maze::DEFAULT_ROWS, Maze::DEFAULT_COLS) {
    initRand();
    setupMaze();    
}

Maze::Maze(const int ROWS, const int COLS) : Board(ROWS, COLS) {
    initRand();
    setupMaze();
}    
//create the cells for the maze
void Maze::createMaze() {
    stack<Cell*> cells;
    
    cells.push(getCell(rand()%getRows(), rand()%getCols()));
       
    while (!cells.empty()) {
	Cell* c1;
	c1 = cells.top();
	cells.pop();
	c1->setVisited();
	vector<direction> neighbors;
        getUnvisitedNeighbors(c1, neighbors);
	if (!neighbors.empty()) {
	    cells.push(c1);
	    int i = rand()%neighbors.size();
	    connect(c1, neighbors.at(i));
	    cells.push(getCell(c1->getRow() + Direction::row(neighbors.at(i)), c1->getCol() + Direction::col(neighbors.at(i))));
	}
    }
    
    setStartCell(getCell(0, rand() % getCols()));
    setEndCell(getCell(getRows()-1, rand() % getCols()));
    
    startCell = getStartCell();
    endCell = getEndCell();
    
}

//check to ensure that the maze is properly constructed
bool Maze::checkMaze() {
    if (allCellsVisited() && allBoundariesCorrect() && allCellsReachable()) return true;
    else return false;
}

//create the pathways as well as start and end cells for the maze
void Maze::setupMaze() {
    bool done = false;
    while (!done) {
        createMaze();
        done = checkMaze();
    }
}
 
/*
 *  Method used to test a maze to make sure all cells
 *  have been visited.
 *  
 */
bool Maze::allCellsVisited() const {
    for (int r=0; r < getRows(); r++) {
        for (int c=0; c < getCols(); c++) {
            if (!getCell(r,c)->isVisited()) return false;
        }
    }
    return true;
}

/*
 *  Method used to test a maze to make sure all edges
 *  on boundaries exist.
 *  
 */
bool Maze::allBoundariesCorrect() const {
    for (int r=0; r<getRows(); r++) {
        if (!getCell(r,0)->hasEdge(WEST)
            || !getCell(r,0)->hasWall(WEST)
            || !getCell(r,getCols()-1)->hasEdge(EAST)
            || !getCell(r,getCols()-1)->hasWall(EAST)) {
             
             cout << getCell(r,0) << '\n';
             cout << getCell(r,getCols()-1) << '\n';
             return false;
        }
    }
    for (int c=0; c<getCols(); c++) {
        if (!getCell(0,c)->hasEdge(NORTH)
            || !getCell(0,c)->hasWall(NORTH)
            || !getCell(getRows()-1,c)->hasEdge(SOUTH)
            || !getCell(getRows()-1,c)->hasWall(SOUTH)) {
             
             cout << '*' << c << "*\n";
             return false;
        }
    }
    return true;
}
    
/*
 *  Method used to test a maze to make sure all cells
 *  are reachable.
 *  
 */
bool Maze::allCellsReachable() {
    int r, c;
    int rows = getRows();
    int cols = getCols();
    // Set all cells to a unique value (starting with 1) and unvisit them
    clearVisited();
    for (r=0; r<rows; r++) {
        for (c=0; c<cols; c++) {
            getCell(r,c)->setValue(r*cols+c+1);
        }
    }
        
    // Now keep reducing connected cells to lowest value.
    // If all are connected, then all cells should end up as 1.
    bool changed = true, modify = false;
    vector<direction> lst;
    int min, v = 0, i;
    while (changed) {
        changed = false;
        for (r=0; r<rows; r++) {
            for (c=0; c<cols; c++) {
                modify = false;
                Cell* cell = getCell(r,c);
                getConnectedNeighbors(cell, lst);
                // Get minimum value for connected cells
                min = v = cell->getValue();
                for (i=0; i<(int)lst.size(); i++) {
                    v = getAdjacentCell(cell, lst.at(i))->getValue();
                    if (v < min) {
                        modify = true;
                        min = v;
                    }
                }
                // Change values in connected cells if needed
                if (modify) {
                    changed = true;
                    cell->setValue(min);
                    for (i=0; i<(int)lst.size(); i++) {
                        getAdjacentCell(cell, lst.at(i))->setValue(min);
                    }
                }
            }
        }
    }
    // Now find out if all cells have value 1 (all connected)
    for (r=0; r<rows; r++) {
        for (c=0; c<cols; c++) {
            if (getCell(r,c)->getValue() != 1) return false;
        }
    }
    return true;
}

void Maze::initRand() {
    if (!randInit) {
        srand(time(NULL));
        randInit = true;
    }
}

void Maze::setRows(const int r) { DEFAULT_ROWS = r; }

void Maze::setCols(const int c) { DEFAULT_COLS = c; }

void Maze::setSize(const int r, const int c) { 
    DEFAULT_ROWS = r;
    DEFAULT_COLS = c;
}
