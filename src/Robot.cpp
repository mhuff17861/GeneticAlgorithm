/*
 *  Robot.cpp
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
 * order of 3 bit pairs defined in walls array (goes up by int count, each of the 4 bits represents a wall in
 * this order N E S W)
 *
 * definition of what the robot will do in each situation can be printed with the dissassemble method
 */

#include "Robot.h"

bool Robot::randInit = false;
int Robot::mutationRate = 5;

string Robot::walls[] = { "No walls: ", "North wall:", "East wall: ", "North and East wall: ", "South wall: ",
                          "North and South Wall: ", "East and South wall: ", "North, East and South wall: ",
                          "West wall: ", "North and West wall: ", "East and West wall: ", 
                          "North, East and West wall: ", "South and West wall: ", "North, South and West wall: ",
                          "East, South and West wall: ", "All four walls: "};


Robot::Robot() {
    //create a random chromosome and send it to init
    init(randomChromosome());
}

Robot::Robot(uint_least64_t chromo) {
    init(chromo);
}

Robot::Robot(const Robot& rbt) {
    //copy given robot's chromosome and fitness score
    init(rbt.chromosome);
}

Robot::Robot(const Robot& rbt1, const Robot& rbt2) {
    initRand();
    //check to see if the chromosomes are the same
    if (rbt1.chromosome == rbt2.chromosome) {
        chromosome = rbt1.chromosome;
    } else {
        uint_least64_t mask = 0x01;
        int pos = rand()%48;
        for (int i = 0; i<pos; i++) mask = (mask << 1 | 0x01);
        chromosome = (rbt1.chromosome & mask) | (rbt2.chromosome & ~mask);
    }
    
    //perform a random mutation on the new chromosome based on mutationRate
    mutate();
}

//fitness related

double Robot::getFitness() const { return fitness; }
double Robot::setFitness(const double rate) { return fitness = rate; }

//mutation accessors... and mutators
int Robot::getMutationRate() { return mutationRate; }
int Robot::setMutationRate(const int rate) {return mutationRate = rate; }

unsigned int Robot::getMove(const int env) const {
    uint_least64_t move = 0X07;
    //shift bits to proper position for &'ing
    for (int i = 0; i < env; i++) {
        move = move << 3;
    }
    
    move = move & chromosome;
    //shift bits back for the return
    for (int i = 0; i < env; i++) {
        move = move >> 3;
    }

    //return an int describing in 2 bits the turn, and 1 bit whether to move forward
    return move;

}

string Robot::disassemble() const {
    string out = "";
    uint_least64_t check;
    //run throught the bits, and output their meaning in string form 
    for (int i = 0; i < 16; i++) {
        out += walls[i];
        //reset check so first 3 bits are 1's
        check = 0x07;
        
        //shift check to the correct position, done this way as no more than 32 bits may be shifted at a time
        for (int j = 0; j < i; j++) {
            check = check << 3;
        }
        //and together the chromosome and the check to get move
        check = check & chromosome;
        //shift back bits for the upcoming checks
        for (int j = 0; j < i; j++) {
            check = check >> 3;
        }
        //add the right move to the output
        if (check == 0) {
            out += "No rotation, no step forward.";
        } else if (check == 1) {
            out += "Rotate right, no step forward.";
        } else if (check == 2) {
            out += "Turn around, no step forward.";
        } else if (check == 3) {
            out += "Rotate left, no step forward.";
        } else if (check == 4) {
            out += "No rotation, one step forward.";
        } else if (check == 5) {
            out += "Rotate right, one step forward";
        } else if (check == 6) {
            out += "Turn around, one step forward";
        } else {
            out += "Rotate left, one step forward";
        }
        out += "\n";
    }
    return out;
}

Robot& Robot::operator=(const Robot& rbt) {
    //copy given robots chromosome and fitness score
    this->chromosome = rbt.chromosome;
    this->fitness = rbt.getFitness();
    return *this;
}

void Robot::init(const uint_least64_t chromo) {
    chromosome = chromo;
}

void Robot::mutate() {
    initRand();
    //check mutation rate, randomly mutate bits with that percentage chance of mutation
    uint_least64_t mask = 0x01;
    for (int i = 0; i<48; i++) {
        if ((rand() % 100) < Robot::mutationRate) {
            chromosome = chromosome ^ mask;
        }
        mask = mask << 1;
    }
}

void Robot::initRand() {
    if (!randInit) {
        srand(time(NULL));
        randInit = true;
    }
}

uint_least64_t Robot::randomChromosome() {
    initRand();
   
    // get three 16 bit random numbers
    // the & 0xffff makes sure we only get the last 16 bits
    // any other bits before the last 16 are erased by the bitwise AND
    uint_least64_t n1 = rand() & 0xffff;
    uint_least64_t n2 = rand() & 0xffff;
    uint_least64_t n3 = rand() & 0xffff;

    // now shift n3 to the left 16 bits: n3 << 16
    // bitwise OR it with n2 to fill in the 16 bits we just vacated: | n2
    // shift the combined new int 16 bits to the left: << 16
    // bitwise OR it with n1 to fill in the 16 bits we just vacated: | n1
    uint_least64_t chromo = ((n3 << 16) | n2) << 16 | n1;

    return chromo;
}
