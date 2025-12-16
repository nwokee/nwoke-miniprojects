#include <cstdio>
#include <iostream>
#include <cstdlib>

#ifndef __PROCSCHED_H
#define __PROCSCHED_H
using namespace std;

//******************************************************************************

typedef struct CPU {
    int processID; // Process ID of the running process
    int timeslice; // Remaining timeslice of the running process
} CPU;

//******************************************************************************

typedef struct instruction {
    char type; // S, A, D, F, B, R, or E
    string param = " "; // parameter for instructions (will convert to int if needed)

}INSTRUCTION;

//******************************************************************************

typedef struct PCBEntry{
    int progCounter;
    int processID = -1;
    int parentPID = 999;
    int value;
    int priority = 0;
    int timeslice;
    int startTime = 0;
    int timeUsed = 0;
    int blockTime = 0;
    bool isReady = false; // tracks the PCB's ready status
    INSTRUCTION* instructions;
    int instructionCount;
} PCBEntry;

//******************************************************************************

class pQueue {
    private:
        int* processes;
        int capacity;
        int pCount;
        int first,last; // indices for cList queue

    public:
        pQueue(int n = 100); // constructor
        ~pQueue(); // destructor

        // adds new process to the queue if it was not already full
        bool enq(int process); 

        // removes process from queue if it wasn't already empty
        int deq();

        void clear(); // removes all items in the queue
        int count() const; // returns the number of items in the queue
        void printIt() const; // prints the contents of the queue


};

//******************************************************************************

class Scheduler {
    private:
        unsigned int sysclock; // system clock of the scheduler, in clock ticks
        CPU cpu; // CPU structure to hold the currently running process
        int PCBCapacity; // maximum number of processes allowed
        int PCBCount; // the number of active processes
        PCBEntry* PCBTable; // array of PCB entries
        int prioCount = 4; // number of priority levels (0-3)
        pQueue** readyState; // array of queues, one for each priority
        int processCount; // number of instantiated processes
        // next fit pointer to the next available space in the PCBTable
        int nextFreePCB; 

        void set(PCBEntry &proc, int val); // set the value of proc to *val*
        void add(PCBEntry &proc, int val); // add *val* to the process
        void deduct(PCBEntry &proc, int val); // deduct *val* from the process
        // create a new process with a parent 
        // of *parent*, skipping *offset* instruction lines
        bool fork(PCBEntry &parent, int offset); 
        // block the process for *ticks* amount of system clock ticks
        void block(PCBEntry &proc, int ticks); 
        // replace the instruction set of *proc* with 
        // the instructions from *fname*
        bool replace(PCBEntry &proc, std::string fname); 
        void exit(PCBEntry &proc); // terminate the process
    


    public:
        Scheduler(int capacity = 100);
        ~Scheduler();

        // initializes the very first program
        void kickOff(string fname);

        // moves ahead one clock tick, executing 
        // everything that happens in that time
        void step();

        // adjusts the cpu depnding on whether 
        // the process running has used up its timeslice
        void schedule();

        // prints all the current processes in the PCB table, as well
        // as their metadata
        void printState();

        // swaps in the highest priority process and loads 
        // it onto the cpu, adjusting the timeslice if needed
        bool swapIn();

        // removes the current process from the cpu and places it
        // back onto the appropriate ready state queue
        void swapOut();

        // adjusts the block time for all blocked processes,
        // putting recently unblocked ones on the readystate queues
        void processBlockedStates();

        // runs the process simulator, terminating once 
        // there are no more active processes
        void runSystem();
};

#endif