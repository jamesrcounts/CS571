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

string Slurp(string file)
{
    ifstream in;
    in.open(file.c_str());
    stringstream sstr;
    sstr << in.rdbuf();
    string allText = sstr.str();
    string punctuation = "'[](){}:,_.!?\";\\/@#$%&*+|~`<";
    string result;
    for(int i = 0; i < (int)allText.size(); i++)
    {
        char p = allText[i];
        if(punctuation.find_first_of(p) == string::npos)
        {
            result.push_back(p);
        }
    }

    return result;
}

int main(int argc, const char * argv[])
{
	cout << endl << "CS571 HW 5" << endl;
	cout << "Jim Counts and Jeremy Villegas" << endl;

	Program p;
	bool test = p.ShouldRunTests(argc, argv);
	string input = Slurp(argv[1]);
	if(test)
	{
		Tests t;
		t.RunTests(input);
	}
	else 
	{
		p.Parse(input);		
	    p.Evaluate();
	    std::vector<string> facts;
	    facts = p.GetFacts();
	    for (int i = 0; i < (int)facts.size(); ++i)
	    {
	    	cout << facts[i] << endl;
	    }
	}

	return 0;
}
