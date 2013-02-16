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

    /*
    Generate every theoretically possible move.
    */
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

    /*
    Expands the current node and selects the successor with the least estimated
    cost to reach the goal state.
    */
    CrossingState SelectNext(CrossingState current)
    {
        // Print the current node
        Expand(current);
        int min_estimate = 4092;
        CrossingState min;

        // Keep track of where we've been
        history.push_back(current);

        // Consider each possible move.
        vector<Move> moves = GenerateMoves();
        for (
            std::vector<Move>::iterator it = moves.begin();
            it != moves.end();
            ++it)
        {
            // Is the move legal from this node?
            if(current.IsApplicableMove(*it))
            {
                // Yes - see where it leads.
                CrossingState successor = current.GenerateSuccessor(*it);
                int estimate = successor.EstimateCost(history);

                Consider(successor, estimate, *it);

                // Is this better than moves we've already seen?
                if(estimate < min_estimate)
                {
                    // Yes, remember this one.
                    min_estimate = estimate;
                    min = successor;
                }
            }
        }

        // Select the best node I found.
        return min;
    }

    /*
    Prints a message about the current node.
    */
    void Expand(CrossingState current)
    {
        cout << endl << "*Expanding: " << current.str() << endl;
    }

    /*
    Prints a message about a candidate node.
    */
    void Consider(CrossingState successor, int estimate, Move m)
    {
        cout << endl << "Considering: (" << estimate << ") for ";
        cout << successor.str() << endl << "\tvia " << m.str() << endl;
    }

    /*
    Prints the path to the solution.
    */
    void Review()
    {
        cout << endl << "Path to solution:" << endl;
        for (std::vector<CrossingState>::iterator state = history.begin();
                state != history.end();
                ++state)
        {
            cout << state->str() << endl;
        }
    }

    /*
    Continuously expands the current node, selects the least costly, then moves
    to the selection, until the goal state is reached.
    */
    void Evaluate()
    {
        // Setup the inital and goal states.
        CrossingState goal_state = CrossingState(false, 0, 0);
        CrossingState current_state = CrossingState(true, 3, 3);

        // Are we there yet?
        while(current_state != goal_state)
        {
            // Move to the next best state.
            current_state = SelectNext(current_state);
        }

        // We're there.
        history.push_back(goal_state);

        // Print how we got here.
        Review();
    }

};
#endif
