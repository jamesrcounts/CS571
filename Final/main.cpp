//************************************************************************************
//  main.cpp
//  mysh
//
//  Created by Jim Counts and Jeremy Villegas 11/2012
//  CS 571 - AI
//  Homework 5
//  
//  This program acts as a basic shell and implements a Forward Chaining production 
//  system.
//*************************************************************************************

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
