/*
 *  Maze.h
 *  CIS 250
 *  David Klick/Micah Huff
 *  2016-2-4
 *
 *  
 * This part of the program extends Board.h to randomly generate mazes 
 * to either the default size, or a size specified by the programmer/user
 *
 *
 */

#ifndef __MAZE_H__
#define __MAZE_H__


#include "Board.h"
#include "Cell.h"
#include "Direction.h"
#include <iomanip>
#include <iostream>
#include <cstring>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using std::boolalpha;
using std::stack;
using std::vector;
using std::cin;
using std::cout;

class Maze : public Board { 
 private:
    Cell *startCell;
    Cell *endCell;
    static int DEFAULT_ROWS;
    static int DEFAULT_COLS;
    static bool randInit;
    
    //maze generation
    void createMaze();
    bool checkMaze();
    void setupMaze();
    static void initRand();


    //checks during maze generation
    bool allBoundariesCorrect() const;
    bool allCellsReachable();
    
    
 public:
    //mutators
    static void setRows(const int r);
    static void setCols(const int c);
    static void setSize(const int r, const int c);
    
    //constructors
    Maze();
    Maze(const int rows, const int cols);
    
    //check for maze gen. and running robots through maze
    bool allCellsVisited() const;

};

#endif
