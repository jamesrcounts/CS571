//******************************************************************************
//  main.cpp
//  mc
//
//  Created by Jim Counts
//  CS 571 - AI
//  Final Project
//  
//  This program implements an A* search to solve the Missinaries & Cannibals 
//  puzzle.
//******************************************************************************

#include <algorithm>
#include <iostream>
#include <fstream>
#include "Program.h"
#include "Test.h"

using namespace std;

/*
Bootstrapper for the application.
*/
int main(int argc, const char * argv[])
{
    cout << endl << "CS571 Final Project" << endl;
    cout << "Jim Counts" << endl << endl;

    Program p;

    // How were we called?
    bool test = p.ShouldRunTests(argc, argv);
    if(test)
    {
        // User wants to run tests.
        Tests t;
        t.RunTests();
    }
    else 
    {
        // User wants to run the program.
        p.Evaluate();
    }

    return 0;
}
