#ifndef TESTS_H
#define TESTS_H

#include "TestFramework.h"
#include "CrossingState.h"
#include "Move.h"

using namespace std;

class Tests{
    TestFramework tf;

    void VerifyMoveLeft()
    {
        string expected = "Moving Left, with 1 missionaries, and 1 cannibals.";

        Move m = Move(false, 1, 1);
        tf.ASSERT_STRING_EQUALS( expected,m.str(), "VerifyMoveLeft");     
    }

    void VerifyMoveRight()
    {
        string expected = "Moving Right, with 0 missionaries, and 2 cannibals.";
        Move m = Move(true, 0, 2);
        tf.ASSERT_STRING_EQUALS(expected, m.str(), "VerifyMoveRight");
    }

    void VerifyMoveException()
    {
        string expected = "Too many people in the boat!";
        try
        {
            Move m = Move(true, 2, 1);            
            tf.ASSERT_TRUE(false, "VerifyMoveException Excpected Exception.");
        }
        catch(exception& e)
        {
            tf.ASSERT_STRING_EQUALS(expected, e.what(), "VerifyMoveException");
        }
    }

    void VerifyMoves(vector<string> expected, vector<Move> actual, string message)
    {        
        tf.ASSERT_INT_EQUALS(expected.size(), actual.size(), tf.GetSizeMessage(message));
        if(expected.size() == actual.size())
        {  
            for (int i = 0; i < (int)expected.size(); ++i)
            {
                tf.ASSERT_STRING_EQUALS(expected[i], actual[i].str(), expected[i]);
            }
        }
    }

    void GenerateAllMoves()
    {
        vector<string> expected;
        expected.push_back("Moving Left, with 1 missionaries, and 0 cannibals.");
        expected.push_back("Moving Left, with 2 missionaries, and 0 cannibals.");
        expected.push_back("Moving Left, with 1 missionaries, and 1 cannibals.");
        expected.push_back("Moving Left, with 0 missionaries, and 2 cannibals.");
        expected.push_back("Moving Left, with 0 missionaries, and 1 cannibals.");
        expected.push_back("Moving Right, with 1 missionaries, and 0 cannibals.");
        expected.push_back("Moving Right, with 2 missionaries, and 0 cannibals.");
        expected.push_back("Moving Right, with 1 missionaries, and 1 cannibals.");
        expected.push_back("Moving Right, with 0 missionaries, and 2 cannibals.");
        expected.push_back("Moving Right, with 0 missionaries, and 1 cannibals.");

        Program p;
        vector<Move> actual = p.GenerateMoves();
        
        tf.ASSERT_INT_EQUALS(expected.size(), actual.size(), tf.GetSizeMessage("GenerateAllMoves"));
        if(expected.size() == actual.size())
        {  
            for (int i = 0; i < (int)expected.size(); ++i)
            {
                tf.ASSERT_STRING_EQUALS(expected[i], actual[i].str(), expected[i]);
            }
        }
    }

    void VerifyInitialState()
    {
        string expected = "Boat on Right bank, with 3 missionaries, and 3 cannibals.";
        
        CrossingState c = CrossingState(true, 3, 3);
        tf.ASSERT_STRING_EQUALS(expected, c.str(), "VerifyInitialState");
    }

    void VerifyGoalState()
    {
        string expected = "Boat on Left bank, with 3 missionaries, and 3 cannibals.";
        CrossingState c = CrossingState(false, 0, 0);
        tf.ASSERT_STRING_EQUALS(expected, c.str(), "VerifyGoalState");
    }

    void VerifyIntermediateRightState()
    {
        string expected = "Boat on Right bank, with 2 missionaries, and 1 cannibals.";

        CrossingState c = CrossingState(true, 2, 1);
        tf.ASSERT_STRING_EQUALS(expected, c.str(), "VerifyIntermediateRightState");
    }

    void VerifyIntermediateLeftState()
    {
        string expected = "Boat on Left bank, with 1 missionaries, and 2 cannibals.";

        CrossingState c = CrossingState(false, 2, 1);
        tf.ASSERT_STRING_EQUALS(expected, c.str(), "VerifyIntermediateLeftState");
    }

    void VerifyStateException(int missionaries, int cannibals, bool for_missionaries, string message)
    {
        string expected = "Too many or too few ";
        expected += (for_missionaries ? "missionaries" : "cannibals");
        expected += " on the river banks!";

        try
        {
            CrossingState c = CrossingState(true, missionaries, cannibals); 
            tf.ASSERT_TRUE(false, message + " expected exception.");            
        }
        catch(exception& e)
        {
            tf.ASSERT_STRING_EQUALS(expected, e.what(), message);
        }
    }

    void VerifyMissonaryException(int missionaries, string message)
    {
        VerifyStateException(missionaries, 3, true, message);
    }

    void VerifyCannibalException(int cannibals, string message)
    {
        VerifyStateException(3, cannibals, false, message);
    }

    void VerifyMissonaryOverpopulation()
    {
        VerifyMissonaryException(6, "MissionaryOverpopulation");
    }

    void VerifyMissonaryUnderpopulation()
    {
        VerifyMissonaryException(-1, "MissionaryUnderpopulation");
    }

    void VerifyCannibalOverpopulation()
    {
        VerifyCannibalException(6, "CannibalOverpopulation");
    }

    void VerifyCannibalUnderpopulation()
    {
        VerifyCannibalException(-1, "CannibalUnderpopulation");
    }

    void SelectMovesFromTheRight()
    {
        vector<string> expected;
        expected.push_back("Moving Left, with 1 missionaries, and 0 cannibals.");
        expected.push_back("Moving Left, with 2 missionaries, and 0 cannibals.");
        expected.push_back("Moving Left, with 1 missionaries, and 1 cannibals.");
        expected.push_back("Moving Left, with 0 missionaries, and 2 cannibals.");
        expected.push_back("Moving Left, with 0 missionaries, and 1 cannibals.");

        Program p;
        CrossingState c = CrossingState(true, 2, 2);  
        vector<Move> allMoves = p.GenerateMoves();
        vector<Move> actual;
        for (std::vector<Move>::iterator it = allMoves.begin(); it != allMoves.end(); ++it)
        {
            if(c.IsApplicableMove(*it))
            {
                actual.push_back(*it);
            }
        }      
        VerifyMoves(expected, actual, "SelectMovesFromTheRight");
    }

    void VerifyBoatPositionForMoveFromRight()
    {
        Move m = Move(true, 1, 1);
        tf.ASSERT_FALSE(m.BoatOnRight(), "VerifyBoatPositionForMoveFromRight");
    }

    void VerifyBoatPositionForMoveFromLeft()
    {
        Move m = Move(false, 1 , 1);
        tf.ASSERT_TRUE(m.BoatOnRight(), "VerifyBoatPositionForMoveFromLeft");
    }
public:

    // Execute all configured unit tests.
    void RunTests()
    {
        VerifyBoatPositionForMoveFromRight();
        VerifyBoatPositionForMoveFromLeft();
        SelectMovesFromTheRight();
        VerifyCannibalUnderpopulation();
        VerifyCannibalOverpopulation();
        VerifyMissonaryUnderpopulation();
        VerifyMissonaryOverpopulation();
        VerifyIntermediateLeftState();
        VerifyIntermediateRightState();
        VerifyGoalState();
        VerifyInitialState();
        GenerateAllMoves();
        VerifyMoveException();
        VerifyMoveLeft();
        VerifyMoveRight();
        cout << tf.GetPassCount() << "/" << tf.GetPassCount() + tf.GetFailCount() << endl;
    }
};
#endif
