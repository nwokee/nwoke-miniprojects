#include <cstdio>
#include <iostream>
#include <cstdlib>

#ifndef __MEMMGR_H
#define __MEMMGR_H


class node {
    private:
        int process_id; // ID of the process that owns this block; -1 if hole
        int starting_address; // the starting address of block
        int length; // size of the memory block (in KB)
        node *prev, *next; // pointers to next and previous nodes

    public:
        node(int process_id = -1, int starting_address = 0, int length = 0, 
            node* prev = NULL, node* next = NULL);
    
    // Declaring MemoryManager as a friend class
    friend class MemoryManager;
};


class MemoryManager {

    private:
        int totalMemory; // Total available memory in the system (in KB)
        int usedMemory; // Total memory currently allocated (in KB)
        int unitSize; // Size of each memory unit (in KB)
        int unitMin, unitMax; // Size limitations of each memory unit
        int fitType; // 0 for first fit, 1 for next fit,
                     // 2 for best fit, 3 for worst fit
        node *first, *last; // Pointers to the first and last nodes of the list
        node *nextFitptr; // pointer to the last allocated node for next fit
        int nCount; // Stores the number of processes in the list

        int first_fit(int pid, int num_units); // first fit memory allocator
        int next_fit(int pid, int num_units);  // next fit memory allocator
        int best_fit(int pid, int num_units);  // best fit memory allocator
        int worst_fit(int pid, int num_units); // worst fit memory allocator
        node* processInsert(node* current, int requiredSize, int pid); // helper function
    
    public:
        MemoryManager(int total = 256, int fitType = 0);
        ~MemoryManager();

        int allocate_mem(int process_id, int num_units); // allocates num_units
        // units of memory to a process. If successful, it returns the number 
        // of nodes traversed in the linked list, returning -1 otherwise.

        int deallocate_mem(int process_id); // deallocates the memory allocated
        // to the process whose id is process_id. It returns 1 or -1.

        int fragment_count(); // returns the number of fragments in the memory.

        void switchFitType(int newType); // allows user to switch from the 4 fit
        // types; if the value is not 0-3, fit resets to 0;

        void printList();


        
};

#endif