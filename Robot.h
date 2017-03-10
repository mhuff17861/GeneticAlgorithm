/*
 *  Robot.h
 *  CIS 250
 *  David Klick/Micah Huff
 *  2016-2-4
 *
 *
 * This part of the program creates the blueprint for a maze traversing robot, 
 * using a uint_least64_t to define the chromosome in bits, as well as methods 
 * to define it's "fitness score," or the chromosomes ability to solve a maze,
 * and to create new generations based on breeding and random mutations.
 *
 */

#include <string>
#include <cstdint>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
using std::uint_least64_t;
using std::ostream;
using std::string;

class Robot { 
 public:
    //constructors
    Robot();
    Robot(uint_least64_t chromo);
    Robot(const Robot& rbt);
    Robot(const Robot& rbt1, const Robot& rbt2);
    
    //fitness
    double getFitness() const;
    double setFitness(const double fit);

    //mutation
    static int getMutationRate();
    static int setMutationRate(const int rate);

    //movement
    unsigned int getMove(const int env) const;

	//convert bits to meaning 
	string disassemble() const;

    //operators
    Robot& operator=(const Robot& rbt);
    friend ostream& operator<<(ostream& strm, const Robot& rbt) { return strm << rbt.disassemble(); }

 private: 
    //variables
    double fitness;
    static int mutationRate;  // where 1 = 1%, 2 = 2%, etc.
    uint_least64_t chromosome;
    static bool randInit;
    static string walls[];

    //construction
    void init(const uint_least64_t chromo);
    uint_least64_t getRandomChromo();

    //mutation
    void mutate();

    //random
    static void initRand();
    uint_least64_t randomChromosome();
};
