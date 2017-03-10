/*
 *  ga.cpp
 *  CIS 250
 *  David Klick/Micah Huff
 *  2016-2-4
 *
 *
 *  This is the main portion of the genetic algorithm program. In it, we use
 *  the maze class to generate random mazes, which will have robots run through
 *  them. When they are finished, the best robots will be interbred and a new generation
 *  will be created, eventually creating the perfect (or really good) maze solving robots.
 *
 */

#include "Maze.h"
#include "Arena.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using std::cout;
using std::endl;
using std::setprecision;
using std::getline;

void heapsort(Robot a[], int len);
void heapify(Robot a[], int len);
void siftDown(Robot a[], int start, int end);
int main(int argc, char* argv[]) {
    cout << "yes this program does in fact start" << endl;

    //generation tracking
    const int MAX_GENERATIONS = 1000;
    const int MAX_MAZES = 100;
    const int MAX_ROBOTS = 499;
    const int NUM_TO_ELIM = 250;
    Robot::setMutationRate(20);
	//these are now used in the Arena class for the gui, but kept here for safe keeping
    int generation = 0;
    double best = 0.0, median = 0.0, fit = 0.0;
    //vectors of robots and mazes
    Maze  m[MAX_MAZES];
    Robot r[MAX_ROBOTS];
    Robot survivors[MAX_ROBOTS];
	//create window for display
	sf::RenderWindow window(sf::VideoMode(600, 600), "Maze Solving Genetic Algorithm");

    cout << "finished creating variables" << endl;

    //populate vectors
    for (int i = 0; i < MAX_MAZES; i++) {
        if (i == 0) cout << "generating mazes" << endl;
        m[i] = Maze::Maze();
    }
    
    cout << "finished mazes" << endl;
    
    for (int i = 0; i < MAX_ROBOTS; i++) {
        if (i == 0) cout << "generating robots" << endl;
        r[i] = Robot::Robot();
    }
    
    //run robots through mazes, then breed based on fitness scores
    while (generation<MAX_GENERATIONS && best != 1) {
        if (generation == 0) cout << "beginning test" << endl;
        
        //run all robots through all mazes
        for (int i = 0; i<MAX_ROBOTS; i++) {
            //reset variable to hold fitness score avg
            fit = 0.0;
            //maze loop
            for (int j = 0; j<MAX_MAZES; j++) {
                fit += Arena::runSimulation(m[j], r[i]);
            }
            r[i].setFitness(fit/(double) MAX_MAZES);
        }
        //reset best and median for new calc
        median =  0.0;
        best = 0.0;
        //find best and median scores
        heapsort(r, MAX_ROBOTS);
        Arena::setMedian(median = r[MAX_ROBOTS/2 - 1].getFitness());
		Arena::setBest(best = r[MAX_ROBOTS - 1].getFitness());
		Arena::setGeneration(generation + 1);
        //display generation with best and median fitness scores
        /*cout << "Generation: " << generation + 1 << endl
             << "Best Fitness Score: " << setprecision(2) << best << endl
             << "Median Fitness Score: " << setprecision(2) << median << endl;*/

		//show the robot going through the maze
		if (Arena::runSimulation(m[rand() % MAX_MAZES], r[MAX_ROBOTS - 1], window) == -1) return 0;
        //eliminate least fit robots and crossbreed the remainder
        int j = 0;
        for (int i = MAX_ROBOTS - 1; i > NUM_TO_ELIM; i--) {
            survivors[j] = r[i];
            j++;
        }
        j = 0;
        for (int i = 0; i<MAX_ROBOTS; i++) {
            if (i < MAX_ROBOTS - NUM_TO_ELIM) {
                r[i] = Robot::Robot(survivors[i], survivors[rand()%(MAX_ROBOTS - NUM_TO_ELIM)]);
            } else {
                r[i] = survivors[j];
                j++;
            }
        }
        //increase generation
        generation++;
    }
	/*cout << "Best Robot: " << endl << endl
		<< r[MAX_ROBOTS - 1];*/

	//leave open to disassemble the best robot
	window.clear(sf::Color::White);

	sf::Font f;
	if (!f.loadFromFile("fonts/Oswald-Regular.ttf")) return 0;
	sf::Text title;
	title.setString("The Best Robot: ");
	title.setFont(f);
	title.setCharacterSize(30);
	title.setPosition(10, 10);
	title.setColor(sf::Color::Black);
	window.draw(title);

	//split disassembled string into multiple texts
	string desc = r[MAX_ROBOTS - 1].disassemble();
	sf::Text disassembled[16];
	stringstream description(desc);

	for (int i = 0; i < 16; i++) {
		getline(description, desc, '\n');
		disassembled[i].setString(desc);
		disassembled[i].setFont(f);
		disassembled[i].setCharacterSize(20);
		disassembled[i].setPosition(10, 50 + (30 * i));
		disassembled[i].setColor(sf::Color::Black);
		window.draw(disassembled[i]);
	}

	window.display();

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

    return 0;
}

void heapsort(Robot a[], int len) {
    heapify(a, len);

    int end = len - 1;
    Robot tmp;
    while (end > 0) {
        tmp = a[end];
        a[end] = a[0];
        a[0] = tmp;
        end--;
        siftDown(a, 0, end);
    } 
}

void heapify(Robot a[], int len) {
    int start = len-1;
    while (start >= 0) {
        siftDown(a, start, len-1);
        start--;
    }
}

void siftDown(Robot a[], int start, int end) {
    Robot tmp;
    while ((2*start + 1) <= end) {
        int child = 2*start + 1;
        int swap = start;
        if (a[swap].getFitness() < a[child].getFitness()) {
            swap = child;
        } 
        if (((child+1) <= end) && (a[swap].getFitness() < a[child+1].getFitness())) {
            swap = child + 1;
        }
        if (swap == start) {
            break;
        } else {
            tmp = a[start];
            a[start] = a[swap];
            a[swap] = tmp;
            start = swap;
        }
    }
}