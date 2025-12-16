#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "proc_sched.h"

using namespace std;

//******************************************************************************

pQueue::pQueue(int n) {
	// initialize variables and allocate memory for pQueue
	pCount = 0;
    first = 0;
    last = 0;
	capacity = n;
	processes = new int[n]; 

}

//******************************************************************************

pQueue::~pQueue() {
	// free pQueue memory and delete the object
    if(processes) {
        delete [] processes;
        processes = NULL;
    }
}

//******************************************************************************

bool pQueue::enq(int process) {
	// if pQueue isn't full, add new process at the end of the queue
	bool returnCode = (pCount < capacity); 
	if (returnCode) {
        //adjust last spot if queue wasn't empty
        if(pCount) {
            last = (last + 1) % capacity;
        }
        //increment last entry and append new process
        processes[last] = process;
        pCount++;
	}

	return returnCode;
}


//******************************************************************************

int pQueue::deq() {
	// if pQueue isn't empty, remove process at the beginning of the queue
	int returnCode = -1; 
	if (pCount > 0) {
		// store process to be removed
        returnCode = processes[first];
        // rotate start of the list and adjust pCount
        if(pCount > 1) {
            first = (first + 1) % capacity;
        }
        pCount--;
	}

	return returnCode;
}

//******************************************************************************

void pQueue::printIt() const {
    for (int i = 0; i < pCount; i++) {
        int index = (first + i) % capacity;
        cout << " " << processes[index];
    }
}

//******************************************************************************

void pQueue::clear() {
	pCount = 0;
}

//******************************************************************************

int pQueue::count() const {
	return pCount;
}

//******************************************************************************

void Scheduler::set(PCBEntry &proc, int val) {
    // set programs value to the provided value
    proc.value = val;
}

//******************************************************************************

void Scheduler::add(PCBEntry &proc, int val) {
    // add the provided value to the programs value
    proc.value += val;
}

//******************************************************************************

void Scheduler::deduct(PCBEntry &proc, int val) {
    // deduct the provided value from the programs value
    proc.value -= val;
}

//******************************************************************************

bool Scheduler::fork(PCBEntry &parent, int offset) {
    // check if there is space in the PCBTable
    bool returncode = PCBCount < PCBCapacity;
    if (returncode) {
        // create a new process with the first available processID
        PCBEntry newProcess;
        
        // modified next fit to work with a normal list instead of linked
        int current = nextFreePCB;
        int limit = PCBCapacity;
        while (current < limit) {
            if(PCBTable[current].processID == -1) {
                newProcess.processID = current;
                nextFreePCB = (current + 1) % PCBCapacity;
                break;
            }
            current++;
            // if we reach the end of the table and haven't found the free space
            // loop back to the start of the program
            if (current == PCBCapacity) {
                current = 0;
                limit = nextFreePCB;
            }
        }

        // initialize the new process's variables
        newProcess.progCounter = parent.progCounter + 1;
        newProcess.timeUsed = 0;
        newProcess.startTime = sysclock;
        newProcess.blockTime = 0;
        newProcess.priority = 0;
        newProcess.value = parent.value;
        newProcess.parentPID = parent.processID;

        // load the same instruction set
        newProcess.instructions = new INSTRUCTION[parent.instructionCount];
        for (int i = 0; i < parent.instructionCount; i++) {
            newProcess.instructions[i] = parent.instructions[i];
        }
        newProcess.instructionCount = parent.instructionCount;

        // offset the parent's instruction set
        if ((parent.progCounter + offset) >= parent.instructionCount) {
            // offset reaches past instruction set, set to last instruction
            parent.progCounter = parent.instructionCount - 1;
        } else {
            parent.progCounter = parent.progCounter + offset;
        }
        
        // load new process onto PCBTable
        PCBTable[current] = newProcess;
        PCBCount++;
        processCount++;

    }

    return returncode;

}

//******************************************************************************

void Scheduler::block(PCBEntry &proc, int ticks) {
    // set block time (it will always be 0 at this point) and increase priority
    proc.blockTime = ticks;
    if(proc.priority < prioCount - 1) {
        proc.priority++;
    }
}

//******************************************************************************

bool Scheduler::replace(PCBEntry &proc, string fname) {
    // attach txt so we can find the file
    fname += ".txt";

    bool rc = false;
    ifstream inputFile(fname);
    if (inputFile.is_open()) {
        rc = true;
        int iCount = 0;
        string line;
        // From the beginning of the file to the end count the number of lines
        do { // catch the off chance that the process instruction is just "E"
            iCount++;
            getline(inputFile, line);
        } while (line[0] != 'E');
        
        // Use counted lines to create array to store instructions from file
        proc.instructions = new INSTRUCTION[iCount];
        proc.instructionCount = iCount;
        // Rewind the file so that the instruction can be read in
        inputFile.seekg(0);
        iCount = 0;
        string instruct;
        // Loop through entire file one line at a time
        do {
            getline(inputFile, instruct);
            // seperate instruction in line and put into type
            proc.instructions[iCount].type = instruct[0];
            if (instruct[0] != 'E'){
                // if it isn't an exit we also need to add the parameter
                proc.instructions[iCount].param = instruct.substr(2);
            }
            iCount++;
        } while (instruct[0] != 'E');
        // close the file
        inputFile.close();
        proc.progCounter = 0;
    }
    return rc;   
}

//******************************************************************************

void Scheduler::exit(PCBEntry &proc) {
    // reset the processID indicating it has terminated
    proc.processID = -1;
    cpu.processID = -1;
    PCBCount--;
    
}

//******************************************************************************

Scheduler::Scheduler(int capacity) {
    // initialize variables
    this->sysclock = 0;
    this->cpu = {-1, 0}; // no process is running at the start
    this->PCBCapacity = capacity;
    this->PCBCount = 0;
    this->PCBTable = new PCBEntry[capacity];
    this->processCount = 0;
    this->nextFreePCB = 0;

    // initialize the readystate queues
    this->readyState = new pQueue*[prioCount];
    for (int i = 0; i < prioCount; i++) {
        readyState[i] = new pQueue(capacity);
    }

    // empty out PCBTable
    for (int i = 0; i < capacity; i++) {
        PCBTable[i].processID = -1;
        PCBTable[i].isReady = false;
    }

}

//******************************************************************************

Scheduler::~Scheduler() {
    // free the memory of the PCBTable and readystate pQueue
    if(PCBTable) {
        delete [] PCBTable;
        PCBTable = NULL;
    }
    if(readyState) {
        for (int i = 0; i < prioCount; i++) {
            delete readyState[i];
        }
        delete[] readyState;
        readyState = NULL;
    }
}

//******************************************************************************

void Scheduler::kickOff(string fname) {
    // initialize first process using replace to load instructions
    PCBEntry start;
    this->replace(start, fname);
    start.processID = 0;
    this->PCBTable[0] = start;
    this->PCBCount = 1;
    processCount++;

    // load first process on the cpu (no need to queue it in)
    cpu.processID = 0;
    cpu.timeslice = 1;
}

//******************************************************************************

void Scheduler::step() {
    cout << "System Clock: " << sysclock << endl;
    // check if a process is currently running, and execute 
    // its next instruction if so
    if (cpu.processID >= 0) {
        // process is running, grab it
        PCBEntry* temp = &PCBTable[cpu.processID];

        char type;
        string param;

        // check if the process still has left over instructions
        if(temp->progCounter < temp->instructionCount) {
            type = temp->instructions[temp->progCounter].type;
            param = temp->instructions[temp->progCounter].param;
        } else {
            // no more instructions, make process exit
            type = 'E';
            param = " ";
        }

        switch(type) {
            case 'S':
                set(*temp, stoi(param));
                break;
            case 'A':
                add(*temp, stoi(param));
                break;
            case 'D':
                deduct(*temp, stoi(param));
                break;
            case 'F':
                fork(*temp, stoi(param));
                break;
            case 'B':
                block(*temp, stoi(param));
                break;
            case 'R':
                replace(*temp, param);
                // replaced with new file, reset progCounter
                temp->progCounter = -1;
                break;
            case 'E':
                exit(*temp);
                break;
        }
    
        // update time used if a process didnt exit
        if(type != 'E'){
            temp->timeUsed++;
            // update time slice (of the process and cpu so they stay in sync)
            temp->timeslice--;
            cpu.timeslice--;
            
            // update PC
            temp->progCounter++;
        }
    }
    // update system clock
    sysclock++; 
}

//******************************************************************************

void Scheduler::schedule() {
    // check for a running process, and dequeue one if there is not, loading it 
    // into the cpu
    if (cpu.processID != -1) {
        //there was a process, check it's time or if it's block
        if (cpu.timeslice == 0) {
        // if current timeslice = 0, swap out, decrease priority and enqueue
        if (PCBTable[cpu.processID].priority < prioCount - 1) {
            PCBTable[cpu.processID].priority++;
        }
        swapOut();
        } else if (PCBTable[cpu.processID].blockTime) {
        // if the running process is blocked, swap it out
        swapOut();
        }
    }
    swapIn();
}

//******************************************************************************

void Scheduler::printState() {

    // print out the state of all the PCBs
    if (cpu.processID != -1) {
        cout << "CPU PID = " << cpu.processID << 
            "  CPU timeslice = " << cpu.timeslice << endl;
    } else {
        cout << "There is no active process" << endl;
    }

    cout << "pid  ppid  pri  pc  value  timeStart" <<  
            "  timeslice  timeUsed  blocked" << endl;
    for (int i = 0; i < PCBCapacity; i++) {
        if (PCBTable[i].processID != -1) {
            cout << right << setw(3) << PCBTable[i].processID << "  ";
            cout << right << setw(4) << PCBTable[i].parentPID << "  ";
            cout << right << setw(3) << PCBTable[i].priority << "  ";
            cout << right << setw(2) << PCBTable[i].progCounter << "  ";
            cout << right << setw(5) << PCBTable[i].value << "  ";
            cout << right << setw(9) << PCBTable[i].startTime << "  ";
            cout << right << setw(9) << PCBTable[i].timeslice << "  ";
            cout << right << setw(8) << PCBTable[i].timeUsed << "  ";
            cout << right << setw(7) << PCBTable[i].blockTime << "  ";
            cout << endl;
        }
    }

    // Separator for each clock tick
    cout << "**********************************";
    cout <<"********************************" << endl;
}

//******************************************************************************

bool Scheduler::swapIn() {
    bool returnCode = false;
    // Retrieve the highest priority process from the readystate queue
    int pID = -1;
    
    // determine the highest priority with entries
    int i;
    for (i = 0; i < prioCount; i++) {
        if(readyState[i]->count() > 0) {
            // we found a non empty process queue at index i
            returnCode = true;
            pID = readyState[i]->deq();
            PCBTable[pID].isReady = false;
            cpu.processID = pID;

            // check if it has a timeslice and adjust if needed
            if(!PCBTable[pID].timeslice) {
                PCBTable[pID].timeslice = (int)pow(2,PCBTable[pID].priority);
            }
            cpu.timeslice = PCBTable[pID].timeslice;
            break;
        }
    }
    // on success, adjust the timeslice and load on to the cpu


    return returnCode;
}

//******************************************************************************

void Scheduler::swapOut() {

    // grab the process being ran
    PCBEntry *proc = &PCBTable[cpu.processID];

    // enqueue the process onto readystate
    readyState[PCBTable[proc->processID].priority]->enq(proc->processID);
    proc->isReady = true;

    // reset cpu variables;
    this->cpu = {-1, 0};
    
    
}

//******************************************************************************

void Scheduler::processBlockedStates() {
    // iterate through all the PCBs
    for (int i = 0; i < PCBCapacity; i++) {
        // ignore any running or empty program
        if(i != cpu.processID && PCBTable[i].processID != -1) {
            // decrement the block time if it is blocked
            if (PCBTable[i].blockTime > 0) {
                PCBTable[i].blockTime--;
            }
            // enqueued unblocked processes
            if (PCBTable[i].blockTime == 0 && !PCBTable[i].isReady) {
                readyState[PCBTable[i].priority]->enq(i);
                PCBTable[i].isReady = true;
            }
        }
    }

}

//******************************************************************************

void Scheduler::runSystem() {
    // Run the entire process system as long as there are allocated PCBs
    while (PCBCount > 0) {
        step();
        schedule();
        processBlockedStates();
        printState();
    }
    
}