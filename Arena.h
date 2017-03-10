/*
 *  Arena.h
 *  CIS 250
 *  David Klick/Micah Huff
 *  2016-2-4
 *
 *
 *  This is the portion of the program that runs robots through mazes, and 
 *  gives the robot both it's environment and tracks the number of visited cells.
 *  Once the simulation is over, a fitness score is calculated and returned. 
 *
 */

#ifndef __ARENA_H__
#define __ARENA_H__

#include "Direction.h"
#include "Maze.h"
#include "Cell.h"
#include "Robot.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using std::vector;
using std::stringstream;
using std::setprecision;

class Arena {
private:
    static direction robotOrientation;
	static double median;
	static double best;
	static int generation;

    //uses an int to describe the robot's environment
    static int getEnv(direction& dir, Cell* cell);
    //keeps track of the number of cells visited
    static int getNumberOfVisitedCells(Maze& m);
    //checks to see if the robot has already visited a cell facing the same direction
    static bool repeat(direction& dir, int prevDir);
public:
	//run simulation
    static double runSimulation(Maze& maze, Robot& r);
	//display simulation
	static double runSimulation(Maze& maze, Robot& r, sf::RenderWindow& window);
	static void setMedian(double m);
	static void setBest(double b);
	static void setGeneration(int g);
};

#endif
