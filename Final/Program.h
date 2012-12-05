#ifndef PROGRAM_H
#define PROGRAM_H

#include <sstream>
#include <algorithm>
#include <vector>

#include "CrossingState.h"
#include "Move.h"

using namespace std;

/*
The search implementation.
*/
class Program
{
    /*
    Set of visited states.
    */
    vector<CrossingState> history;

    // Gets the command line argument at the specified poistion, or returns
    // a default value if no argument is found at that position.
    string GetArgumentAt(
        int argc,
        const char *argv[],
        int position,
        string defaultValue)
    {
        if(position < argc)
        {
            return string(argv[position]);
        }

        return defaultValue;
    }


public:
    // Gets a value indicating whether the user has requested a test run.
    bool ShouldRunTests(int argc, const char *argv[])
    {
        return GetArgumentAt(argc, argv, 1, "").compare("TEST") == 0;
    }

    vector<Move> GenerateMoves()
    {
        vector<Move> v;
        v.push_back(Move(false, 1, 0));
        v.push_back(Move(false, 2, 0));
        v.push_back(Move(false, 1, 1));
        v.push_back(Move(false, 0, 2));
        v.push_back(Move(false, 0, 1));
        v.push_back(Move(true, 1, 0));
        v.push_back(Move(true, 2, 0));
        v.push_back(Move(true, 1, 1));
        v.push_back(Move(true, 0, 2));
        v.push_back(Move(true, 0, 1));

        return v;
    }

    CrossingState SelectNext(CrossingState current)
    {
        Expand(current);

        history.push_back(current);
        int min_estimate = 4092;
        CrossingState min;

        vector<Move> moves = GenerateMoves();
        for (std::vector<Move>::iterator it = moves.begin(); it != moves.end(); ++it)
        {
            if(current.IsApplicableMove(*it))
            {
                CrossingState successor = current.GenerateSuccessor(*it);
                int estimate = successor.EstimateCost(history);

                Consider(successor, estimate);
                
                if(estimate < min_estimate)
                {
                    min_estimate = estimate;
                    min = successor;
                }
            }
            
        }
        return min;
    }

    void Expand(CrossingState current)
    {
        cout << "Expanding: " << current.str() << endl;
    }

    void Consider(CrossingState successor, int estimate)
    {
        cout << "Considering: (" << estimate << ") for " << successor.str() << endl;
    }
    void Evaluate()
    {

    }

};
#endif
