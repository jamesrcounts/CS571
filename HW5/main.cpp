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

#include <iostream>
#include "Program.h"
#include "Test.h"

using namespace std;
int main(int argc, const char * argv[])
{
	cout << endl << "CS571 HW 5" << endl;
	cout << "Jim Counts and Jeremy Villegas" << endl;

	Program p;
	bool test = p.ShouldRunTests(argc, argv);
	if(test)
	{
		Tests t;
		t.RunTests();
	}
	else 
	{
		cout << "No Test." << endl;
	}

	return 0;
}
