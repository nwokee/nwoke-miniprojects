#include <vector>
#include <iostream>
#include "mem_mgr.h"

using namespace std;

//******************************************************************************

void requestTester(int fit) {
    // Print out the fit type being simulated
    if (fit == 1) {
        cout << "Fit Type: Next Fit" << endl;
    } else if (fit == 2) {
        cout << "Fit Type: Best Fit" << endl;
    } else if (fit == 3) {
        cout << "Fit Type: Worst Fit" << endl;
    } else {
        // reset fit type to ensure no issues
        fit = 0;
        cout << "Fit Type: First Fit" << endl;
    }

    cout << "-----------------------" << endl;

    srand(4); // Seed random number generator for consistency


    // Initialize performance parameters
    float avgExternalFragments = 0.0;
    float avgNodesTraversed = 0.0;
    float requestDenialRate = 0.0;
    int deniedRequests = 0;

    // Initialize memory manager
    MemoryManager *m = new MemoryManager(256, fit);

    // Establish a list to keep track of active processes
    vector<int> active;

    // Simulate the 10000 requests (75 25 chance of allocating or deallocating)
    for (int i = 0; i < 10000; i++) {
        if (active.empty() || rand() % 4 < 3) {
            // make a random process id, and allocate it
            int newProcess = rand() % 10000 + i;
            int unitSize = rand() % 8 + 3;

            int allocated = m->allocate_mem(newProcess, unitSize);

            if (allocated != -1) {
                // allocation was successful
                active.push_back(newProcess);
                avgNodesTraversed += allocated;
            } else {
                // allocation failed
                deniedRequests++;
            }
        } else {
            // deallocate a random process from the active list
            int indx = rand() % active.size();
            int toDealloc = active[indx];

            
            int deallocated = m->deallocate_mem(toDealloc);
            if (deallocated == 1) {
                // deallocation was successful; remove from list
                active.erase(active.begin() + indx);
            } else {
                // deallocation failed
                deniedRequests++;
            }
        }

        // update fragment counter
        avgExternalFragments += m->fragment_count();


    }

   
    // clear final process list
    for(int i = 0; i < (int)active.size(); i++) {
        m->deallocate_mem(active[i]);
    }

    // calculate final stats
    avgExternalFragments /= 10000;
    avgNodesTraversed /= (10000 - deniedRequests);

    // divided by 10000 multiplied by 100
    requestDenialRate = (float)deniedRequests / 100.0; 

    // print out statistics
    cout << "Average External Fragments: " 
                << avgExternalFragments << endl;

    cout << "Average Nodes Traversed: " << avgNodesTraversed << endl;

    cout << "Request Denial Rate: " << requestDenialRate 
                << "%" << endl << endl;
}




//******************************************************************************

int main() {
    cout << "------Memory Allocation Simulator------" << endl;
    cout << "---------------------------------------" << endl;
    cout << endl << endl;
    // Run the tester for each fit type
    requestTester(0); // First Fit
    requestTester(1); // Next Fit
    requestTester(2); // Best Fit
    requestTester(3); // Worst Fit
    return 0;
}