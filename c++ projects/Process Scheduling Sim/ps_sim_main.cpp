#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "proc_sched.h"

using namespace std;

//******************************************************************************

void doWork() {
    
}

//******************************************************************************

int main() {
    cout << "------------------Process Schedul";
    cout << "ing Simulation-------------------" << endl;
    cout << "---------------------------------";
    cout << "---------------------------------" << endl;
    cout << "---------------------------------";
    cout << "---------------------------------" << endl;

    Scheduler *myScheduler = new Scheduler(10);
    myScheduler->kickOff("init");
    myScheduler->runSystem();
    return 0;
}
