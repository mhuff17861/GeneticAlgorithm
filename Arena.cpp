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

#include "Arena.h"

direction Arena::robotOrientation = direction::SOUTH;
double Arena::median = 0.0;
double Arena::best = 0.0;
int Arena::generation = 0;

void Arena::setMedian(double m) {
	median = m;
}

void Arena::setBest(double b) {
	best = b;
}

void Arena::setGeneration(int g) {
	generation = g;
}

double Arena::runSimulation(Maze& maze, Robot& r) {
	//reset maze
	maze.clearVisited();
	maze.clearValues();

	//set needed values after reset
	Cell* curCell = maze.getStartCell();
	robotOrientation = direction::SOUTH;
	unsigned int move;
	double score;

	//while the robot is not in the same cell facing the same direction
	while (!repeat(robotOrientation, curCell->getValue()) && !(curCell == maze.getEndCell())) {
		//set current cell to visited and update it's value
		curCell->setVisited();
		curCell->setValue(curCell->getValue() + robotOrientation);

		//send the robot the environment and get it's next move
		move = r.getMove(getEnv(robotOrientation, curCell));

		//perform next move

		//find rotation
		if (move == 3 || move == 7) {
			robotOrientation = Direction::left(robotOrientation);
		}
		else if (move == 2 || move == 6) {
			robotOrientation = Direction::opposite(robotOrientation);
		}
		else if (move == 1 || move == 5) {
			robotOrientation = Direction::right(robotOrientation);
		}
		else {
			//no rotation
		}

		//move forwards
		if (!curCell->hasWall(robotOrientation) && !curCell->hasEdge(robotOrientation)) {
			curCell = maze.getCell(curCell->getRow() + Direction::row(robotOrientation), curCell->getCol() + Direction::col(robotOrientation));
		}
	}

	//calculate score    
	//score is a 1 if the end has been reached, else it is 1 - (distance from end * 0.01)
	if (curCell == maze.getEndCell()) {
		score = 1.0;
	}
	else {
		score = (double)getNumberOfVisitedCells(maze) / (double)((double)maze.getRows() * (double)maze.getCols());
	}
	//return score
	return score;
}

int Arena::getEnv(direction& dir, Cell* cell) { 
    int env = 0;
    //create environment
    //only add to the env if there is an edge or wall
    //set int to values retrieved from direction
    //use the direction of robot orientation 
    //to determine how to present the cell to the robot
    //as which way it is facing is considered "north" to it
        
   if (cell->hasWall(direction::NORTH) || cell->hasEdge(direction::NORTH)) {    
       if (robotOrientation == direction::NORTH) {
           env += direction::NORTH;
       } else if (robotOrientation == direction::EAST) {
           env+= Direction::left(direction::NORTH);
       } else if (robotOrientation == direction::SOUTH) {
           env+= Direction::opposite(direction::NORTH);
       } else {
           env+= Direction::right(direction::NORTH);
       }
   }
   if (cell->hasWall(direction::SOUTH) || cell->hasEdge(direction::SOUTH)) {    
        if (robotOrientation == direction::NORTH) {
            env += direction::SOUTH;
       } else if (robotOrientation == direction::EAST) {
           env+= Direction::left(direction::SOUTH);
       } else if (robotOrientation == direction::SOUTH) {
           env+= Direction::opposite(direction::SOUTH);
       } else {
           env+= Direction::right(direction::SOUTH);
       }    
   }
   if (cell->hasWall(direction::EAST) || cell->hasEdge(direction::EAST)) {    
        if (robotOrientation == direction::NORTH) {
           env += direction::EAST;
       } else if (robotOrientation == direction::EAST) {
           env+= Direction::left(direction::EAST);
       } else if (robotOrientation == direction::SOUTH) {
           env+= Direction::opposite(direction::EAST);
       } else {
           env+= Direction::right(direction::EAST);
       }    
   }
   if (cell->hasWall(direction::WEST) || cell->hasEdge(direction::WEST)) {    
        if (robotOrientation == direction::NORTH) {
           env += direction::WEST;
       } else if (robotOrientation == direction::EAST) {
           env+= Direction::left(direction::WEST);
       } else if (robotOrientation == direction::SOUTH) {
           env+= Direction::opposite(direction::WEST);
       } else {
           env+= Direction::right(direction::WEST);
       }    
   }
    //return environement in int form
    return env;
}

int Arena::getNumberOfVisitedCells(Maze& m) {
    int count = 0;
    //for each cell in the maze
    for (int i = 0; i < m.getRows(); i++) {
        for (int j = 0; j < m.getCols(); j++) {
            //if cell has been visited, increase count
            if (m.getCell(i,j)->isVisited()) count++;
        }
    }
    return count;
}

bool Arena::repeat(direction& dir, int prevDir) {
    unsigned int d = dir;
    unsigned int check = prevDir;
    if ((d & check) > 0) return true;
    else return false;
}

double Arena::runSimulation(Maze& maze, Robot& r, sf::RenderWindow& window) {
	sf::Font f;

	if (!f.loadFromFile("fonts/Oswald-Regular.ttf")) return 0;

	const int ROWS = maze.getRows();
	const int COLS = maze.getCols();
	const int CELL_SIZE = 30, OFFSET = 150;
	sf::RectangleShape rectangles[10][10];
	vector<sf::RectangleShape> lines;
	
	//text for display of info
	sf::Text bst;
	sf::Text med;
	sf::Text gen;
	//set fonts
	bst.setFont(f);
	med.setFont(f);
	gen.setFont(f);
	bst.setColor(sf::Color::Black);
	med.setColor(sf::Color::Black);
	gen.setColor(sf::Color::Black);
	//set sizes
	bst.setCharacterSize(24);
	med.setCharacterSize(24);
	gen.setCharacterSize(24);
	//set positions
	gen.setPosition(10, 10);
	bst.setPosition(10, 40);
	med.setPosition(10, 70);
	//set strings
	stringstream stream;
	stream.str("");
	string out;

	stream << generation;
	stream >> out;
	out = "Generation: " + out;
	gen.setString(out);

	stream.str(string());
	stream.clear();
	out.clear();
	stream << setprecision(2) << median;
	stream >> out;
	out = "Median Score: " + out;
	med.setString(out);

	stream.str(string());
	stream.clear();
	out.clear();
	stream << setprecision(2)  << best;
	stream >> out;
	out = "Best Score: " + out;
	bst.setString(out);
	
	//Cell used to find borders for the board spaces
	Cell* c;
	//populate rectangles as board spaces
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			//add board spaces, set color and position
			rectangles[i][j] = sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			rectangles[i][j].setFillColor(sf::Color::White);
			rectangles[i][j].setPosition((j * CELL_SIZE) + OFFSET, (i * CELL_SIZE) + OFFSET);
			
			//set cell to find borders and highlight end cell
			c = maze.getCell(i, j);
			if (c == maze.getEndCell()) rectangles[i][j].setFillColor(sf::Color::Blue);

			if (c->hasWall(direction::NORTH) || c->hasEdge(direction::NORTH)) {
				lines.push_back(sf::RectangleShape(sf::Vector2f(CELL_SIZE, 2)));
				lines[lines.size() - 1].setPosition(rectangles[i][j].getPosition());
				lines[lines.size() - 1].setFillColor(sf::Color::Black);
			}
			if (c->hasWall(direction::WEST) || c->hasEdge(direction::WEST)) {
				lines.push_back(sf::RectangleShape(sf::Vector2f(2, CELL_SIZE)));
				lines[lines.size() - 1].setPosition(rectangles[i][j].getPosition());
				lines[lines.size() - 1].setFillColor(sf::Color::Black);
			}
			if (c->hasWall(direction::SOUTH) || c->hasEdge(direction::SOUTH)) {
				lines.push_back(sf::RectangleShape(sf::Vector2f(CELL_SIZE, 2)));
				lines[lines.size() - 1].setPosition(rectangles[i][j].getPosition() + sf::Vector2f(0, CELL_SIZE));
				lines[lines.size() - 1].setFillColor(sf::Color::Black);
			}
			if (c->hasWall(direction::EAST) || c->hasEdge(direction::EAST)) {
				lines.push_back(sf::RectangleShape(sf::Vector2f(2, CELL_SIZE)));
				lines[lines.size() - 1].setPosition(rectangles[i][j].getPosition() + sf::Vector2f(CELL_SIZE, 0));
				lines[lines.size() - 1].setFillColor(sf::Color::Black);
			}
		}
	}
	
	//reset maze
	maze.clearVisited();
	maze.clearValues();

	//set needed values after reset
	Cell* curCell = maze.getStartCell();
	robotOrientation = direction::SOUTH;
	unsigned int move;
	double score;

	//clock for delays 
	sf::Clock clock;
	sf::Time delay = sf::milliseconds(50);

	//DRAW WINDOW INITIALLY WITH START CELL HIGHLIGHTED AS CURRENT
	window.clear(sf::Color::White);

	//highlight start cell
	rectangles[curCell->getRow()][curCell->getCol()].setFillColor(sf::Color::Green);

	//add cells
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			window.draw(rectangles[i][j]);
		}
	}

	//add borders
	for (unsigned int i = 0; i < lines.size(); i++) {
		window.draw(lines[i]);
	}

	//add information
	window.draw(gen);
	window.draw(bst);
	window.draw(med);

	window.display();

	//while the robot is not in the same cell facing the same direction
	while (!repeat(robotOrientation, curCell->getValue()) && !(curCell == maze.getEndCell())) {
		//set current cell to visited and update it's value
		curCell->setVisited();
		curCell->setValue(curCell->getValue() + robotOrientation);

		//send the robot the environment and get it's next move
		move = r.getMove(getEnv(robotOrientation, curCell));

		//perform next move

		//find rotation
		if (move == 3 || move == 7) {
			robotOrientation = Direction::left(robotOrientation);
		}
		else if (move == 2 || move == 6) {
			robotOrientation = Direction::opposite(robotOrientation);
		}
		else if (move == 1 || move == 5) {
			robotOrientation = Direction::right(robotOrientation);
		}
		else {
			//no rotation
		}

		//reset clock and hold for display
		clock.restart();
		while (clock.getElapsedTime() < delay) {}

		//HIGHLIGHT CURRENT CELL AS VISITED
		rectangles[curCell->getRow()][curCell->getCol()].setFillColor(sf::Color::Red);

		//move forwards
		if (!curCell->hasWall(robotOrientation) && !curCell->hasEdge(robotOrientation)) {
			curCell = maze.getCell(curCell->getRow() + Direction::row(robotOrientation), curCell->getCol() + Direction::col(robotOrientation));
		}

		//REDRAW WINDOW WITH UPDATED CELLS
		window.clear(sf::Color::White);

		//highlight current visiting cell
		rectangles[curCell->getRow()][curCell->getCol()].setFillColor(sf::Color::Green);

		//add cells
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				window.draw(rectangles[i][j]);
			}
		}

		//add borders
		for (unsigned int i = 0; i < lines.size(); i++) {
			window.draw(lines[i]);
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				return -1;
		} 

		//add information
		window.draw(gen);
		window.draw(bst);
		window.draw(med);

		window.display();

	}

	//calculate score    
	//score is a 1 if the end has been reached, else it is 1 - (distance from end * 0.01)
	if (curCell == maze.getEndCell()) {
		score = 1.0;
	}
	else {
		score = (double)getNumberOfVisitedCells(maze) / (double)((double)maze.getRows() * (double)maze.getCols());
	}
	//reset clock and hold for display
	clock.restart();
	while (clock.getElapsedTime() < sf::milliseconds(1000)) {}

	//return score
	return score;
	
}