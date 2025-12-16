#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "mem_mgr.h"

using namespace std;

//******************************************************************************

node::node(int process_id, int starting_address, int length, 
        node* prev, node* next) {
    this->process_id = process_id;
    this->starting_address = starting_address;
    this->length = length;
    this->prev = prev;
    this->next = next;
}

//******************************************************************************

int MemoryManager::first_fit(int pid, int num_units) {
    int returnCode = -1;

    // initialize required variables
    int requiredSize = num_units * unitSize;
    node *current = first;
    int nodesTraversed = 0;

    while (current != NULL) {
        nodesTraversed++;
        if (current->process_id == -1 && current->length >= requiredSize) {
            // found space, helper method to insert
            processInsert(current, requiredSize, pid);
            returnCode = nodesTraversed;

            // insert occured, break out of the loop
            break;
        }
        current = current->next;
    }
    return returnCode;
}

//******************************************************************************

int MemoryManager::next_fit(int pid, int num_units) {
    int returnCode = -1;

    // initialize required variables
    int requiredSize = num_units * unitSize;
    int nodesTraversed = 0;
    node *limit = NULL;
    node *current = nextFitptr;

    while (current != limit) {
        nodesTraversed++;
        if (current->process_id == -1 && current->length >= requiredSize) {
            // found space, helper method to insert
            processInsert(current, requiredSize, pid);
            returnCode = nodesTraversed;
            nextFitptr = current->next;

            // insert occured, break out of the loop
            break;
        }
        current = current->next;
        if (current == NULL && limit == NULL) {
            current = first;
            limit = nextFitptr;
        }
    }

    if (nextFitptr == NULL){
        nextFitptr = first;
    }

    return returnCode;
}

//******************************************************************************

int MemoryManager::best_fit(int pid, int num_units) {
    int returnCode = -1;
    int requiredSize = num_units * unitSize;
    node* bestFit = NULL;
    node* current = first;

    while(current != NULL) {
        // If it is a large enough hole to be considered.
        if (current->process_id == -1 && current->length >= requiredSize) {
            // There is no better fit than the exact size so we will 
            // automatically take the first perfect fit.
            if (current->length == requiredSize) {
                bestFit = current;
                break;
            } 
            // Not a perfect fit but a fit so we want to see if it is a better
            // fit than what we have previously found(it is shorter in length).
            if (!bestFit || current->length < bestFit->length) {
                // We also want to set it if it is the first hole found.
                bestFit = current;
            }
        }
        current = current->next;
    }
    // If we did find a hole large enough for the process.
    if (bestFit) {
        returnCode = nCount;
        processInsert(bestFit, requiredSize, pid);
    }
    return returnCode;
}

//******************************************************************************

int MemoryManager::worst_fit(int pid, int num_units) {
    int returnCode = -1;
    int requiredSize = num_units * unitSize;
    node* worstFit = NULL;
    node* current = first;
    while(current != NULL) {
        // If it is a large enough hole to be considered.
        if (current->process_id == -1 && current->length >= requiredSize) {
            // A fit so we want to see if it is a worse
            // fit than what we have previously found(it is longer in length).
            if (!worstFit || current->length > worstFit->length) {
                // We also want to set it if it is the first hole found.
                worstFit = current;
            }
        }
        current = current->next;
    }
    // If we did find a hole large enough for the process.
    if (worstFit) {
        returnCode = nCount;
        processInsert(worstFit, requiredSize, pid);
    }
    return returnCode;
}
   
//******************************************************************************

node* MemoryManager::processInsert(node* current, int requiredSize, int pid){
    if (current->length > requiredSize) {
        // more space than needed, create new hole
        node *newHole = new node(-1,
                current->starting_address + requiredSize,
                current->length - requiredSize,
                current, current->next);

        
        //attach new hole to rest of process list
        if (current->next != NULL) {
            current->next->prev = newHole;
        } else {
            last = newHole;
        }
        current->next = newHole;

        // we split a hole: update nCount as a result
        nCount++;
    }
    // new process either fits perfectly into the hole or it was just
    // modified to fit, so now we update current node to be the process
    current->length = requiredSize;
    current->process_id = pid;

    // adjust remaining space
    usedMemory += requiredSize;
    return current;
    
}

//******************************************************************************

MemoryManager::MemoryManager(int totalMemory, int fitType) {
    // Initialize all private variables
    this->totalMemory = totalMemory;
    this->usedMemory = 0;
    this->fitType = fitType;
    this->unitSize = 2; 
    this->unitMin = 3; 
    this->unitMax = 10;

    // Initialize the memory with a single free block
    node *initialBlock = new node(-1, 0, totalMemory, NULL, NULL);
    first = initialBlock;
    last = initialBlock;
    nCount = 1;

    // For next fit: initiliaze pointer to first
    nextFitptr = first;
}

//******************************************************************************

MemoryManager::~MemoryManager() {
    // Free all nodes in the linked list
    node *current = first;

    while (current != NULL) {
        node *temp = current->next;
        delete current;
        current = temp;
    }

    first = NULL;
    last = NULL;
    nextFitptr = NULL;
    nCount = 0;

    // Reset all other member variables
    totalMemory = 0;
    usedMemory = 0;
    unitMin = 0;
    unitMax = 0;
    fitType = 0;
    
}

//******************************************************************************

int MemoryManager::allocate_mem(int process_id, int num_units) {
    int returnCode = -1;
    if (process_id >= 0 && num_units >= unitMin && num_units <= unitMax) {
        // valid process_id and unit size: use an if else to use the specified
        // fit type
        if (fitType == 1) {
            returnCode = next_fit(process_id, num_units);
        } else if (fitType == 2) {
            returnCode = best_fit(process_id, num_units);
        } else if (fitType == 3) {
            returnCode = worst_fit(process_id, num_units);
        } else {
            // reset to first fit
            fitType = 0;
            returnCode = first_fit(process_id, num_units);
        }
    }
    return returnCode;
}

//******************************************************************************

int MemoryManager::deallocate_mem(int process_id) {
    int returnCode = -1;

    // attempt to locate the process given
    node *current = first;
    while (current != NULL) {
        if (current->process_id == process_id) {
            // found the process; mark as a hole
            current->process_id = -1;

            // adjust memory used
            usedMemory -= current->length;

            // check if previous node was a hole, and merge if so
            if (current->prev != NULL && current->prev->process_id == -1) {
                node *merging = current->prev;
                merging->length += current->length;
                merging->next = current->next;

                // check if current was the last node in the list
                if (current->next != NULL) {
                    current->next->prev = merging;
                } else {
                    last = merging;
                }
                if (nextFitptr == current) {
                    nextFitptr = merging;
                }
                // adjust nCount and delete the useless node
                nCount--;
                delete current;
                current = merging;
            }

            // check if next node was a hole, and merge if so
            if (current->next != NULL && current->next->process_id == -1) {
                node *deleting = current->next;
                
                current->length += deleting->length;
                current->next = deleting->next;

                // check if the hole we're merging was the last node in the list
                if (deleting->next != NULL) {
                    deleting->next->prev = current;
                } else {
                    last = current;
                }

                // For NEXT FIT: reset nextfit pointer to a node that exists
                if (nextFitptr == deleting) {
                    nextFitptr = current;
                }

                // adjust nCount and delete the useless node
                nCount--;
                delete deleting;
            }

        
            // deallocation successful; adjust returncode and break
            returnCode = 1;
            break;

        }

        current = current->next;
    }
    

    return returnCode;
}

//******************************************************************************

int MemoryManager::fragment_count() {
    node* current = first;
    int count = 0;
    // Loop through entire list first - last looking at each node.
    while(current != NULL) {
        // Searching for holes with a size of 1 or 2 units(2 or 4KB length).
        if (current->process_id < 0 && current->length < 5){
            count++;
        }
        current = current->next;
    }
    // The number of fragments(holes too small for a process) is returned.
    return count;
}

//******************************************************************************

void MemoryManager::switchFitType(int newType) {
    // switch to new fit type if newType is valid, otherwise reset to first fit
    if (newType <= 3 && newType >= 0) {
        fitType = newType;
    } else {
        fitType = 0;
    }
}

//******************************************************************************

void MemoryManager::printList() {
    // used for debugging, but shows the entire process list at the moment
    node *current = first;
    while (current != NULL) {
        std::cout << "Process ID: " << current->process_id
            << ", Start Address: " << current->starting_address
            << ", Length: " << current->length << std::endl;
        current = current->next;
    }
}