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

    void VerifyMoves(
        vector<string> expected, 
        vector<Move> actual, 
        string message)
    {        
        tf.ASSERT_INT_EQUALS(
            expected.size(), 
            actual.size(), 
            tf.GetSizeMessage(message));
        if(expected.size() == actual.size())
        {  
            for (int i = 0; i < (int)expected.size(); ++i)
            {
                tf.ASSERT_STRING_EQUALS(
                    expected[i], 
                    actual[i].str(), 
                    expected[i]);
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
        VerifyMoves(expected, actual, "GenerateAllMoves");
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
        tf.ASSERT_STRING_EQUALS(
            expected, 
            c.str(), 
            "VerifyIntermediateRightState");
    }

    void VerifyIntermediateLeftState()
    {
        string expected = "Boat on Left bank, with 1 missionaries, and 2 cannibals.";

        CrossingState c = CrossingState(false, 2, 1);
        tf.ASSERT_STRING_EQUALS(
            expected, 
            c.str(), 
            "VerifyIntermediateLeftState");
    }

    void VerifyStateException(
        int missionaries, 
        int cannibals, 
        bool for_missionaries, 
        string message)
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

    void VerifySelectedMoves(
        vector<string> expected,
        bool right_boat, 
        int missionaries, 
        int cannibals,
        string message)
    {
        Program p;
        CrossingState c = CrossingState(right_boat, missionaries, cannibals);  
        vector<Move> allMoves = p.GenerateMoves();
        vector<Move> actual;
        for (
            std::vector<Move>::iterator it = allMoves.begin(); 
            it != allMoves.end(); 
            ++it)
        {
            if(c.IsApplicableMove(*it))
            {
                actual.push_back(*it);
            }
        }  
        VerifyMoves(expected, actual, message);
    }

    void SelectMovesFromTheRight()
    {
        vector<string> expected;
        expected.push_back("Moving Left, with 1 missionaries, and 0 cannibals.");
        expected.push_back("Moving Left, with 2 missionaries, and 0 cannibals.");
        expected.push_back("Moving Left, with 1 missionaries, and 1 cannibals.");
        expected.push_back("Moving Left, with 0 missionaries, and 2 cannibals.");
        expected.push_back("Moving Left, with 0 missionaries, and 1 cannibals.");
        VerifySelectedMoves(expected, true, 2, 2, "SelectMovesFromTheRight");
    }

    void SelectMissionaryMovesFromLeft()
    {
        vector<string> expected;
        expected.push_back("Moving Right, with 1 missionaries, and 0 cannibals.");
        expected.push_back("Moving Right, with 2 missionaries, and 0 cannibals.");
        VerifySelectedMoves(expected, false, 0, 3, "SelectMissionaryMovesFromLeft");
    }

    void SelectMovesWithMixedFromRight()
    {
        vector<string> expected;
        expected.push_back("Moving Left, with 1 missionaries, and 0 cannibals.");
        expected.push_back("Moving Left, with 1 missionaries, and 1 cannibals.");
        expected.push_back("Moving Left, with 0 missionaries, and 1 cannibals.");
        VerifySelectedMoves(expected, true, 1, 1, "SelectMixedMoveFromRight");      
    }

    void SelectMovesWithMixedFromLeft()
    {
        vector<string> expected;
        expected.push_back("Moving Right, with 1 missionaries, and 0 cannibals.");
        expected.push_back("Moving Right, with 1 missionaries, and 1 cannibals.");
        expected.push_back("Moving Right, with 0 missionaries, and 1 cannibals.");
        VerifySelectedMoves(expected, false, 2, 2, "SelectMovesWithMixedFromLeft");
    }

    void MoveTwoCannibalsLeft()
    {
        CrossingState c = CrossingState(true, 3, 3);
        CrossingState expected = CrossingState(false, 3, 1);
        Move m = Move(false, 0, 2);
        CrossingState actual = c.GenerateSuccessor(m);
        tf.ASSERT_STRING_EQUALS(
            expected.str(), 
            actual.str(), 
            "MoveTwoCannibalsLeft");
    }

    void MoveTwoMissionariesRight()
    {
        CrossingState c = CrossingState(false, 0, 0);
        CrossingState expected = CrossingState(true, 2, 0);
        Move m = Move(true, 2, 0);
        CrossingState actual = c.GenerateSuccessor(m);
        tf.ASSERT_STRING_EQUALS(
            expected.str(), 
            actual.str(), 
            "MoveTwoMissionariesRight");
    }

    void MoveMixedLeft()
    {
        Move m = Move(false, 1, 1);

        CrossingState c         = CrossingState(true, 1, 1);
        CrossingState expected  = CrossingState(false, 0, 0);
        CrossingState actual    = c.GenerateSuccessor(m);
        
        tf.ASSERT_STRING_EQUALS(expected.str(), actual.str(), "MoveMixedLeft");
    }

    void FatalRightState()
    {
        CrossingState c = CrossingState(true, 1, 2);
        tf.ASSERT_FALSE(c.IsSafe(), "FatalRightState");
    }

    void SafeLeftState()
    {
        CrossingState c = CrossingState(false, 1, 1);
        tf.ASSERT_TRUE(c.IsSafe(), "SafeLeftState");
    }

    void EstimateInitialStateCost()
    {
        CrossingState c = CrossingState(true, 3, 3);
        vector<CrossingState> visited;

        int expected = 7;
        int actual   = c.EstimateCost(visited);
        tf.ASSERT_INT_EQUALS(expected, actual, "EstimateInitialStateCost");
    }

    void EstimateReturnToInitialStateCost()
    {
        CrossingState c = CrossingState(true, 3, 3);
        vector<CrossingState> visited;
        visited.push_back(c);

        int expected = 8;
        int actual   = c.EstimateCost(visited);
        tf.ASSERT_INT_EQUALS(
            expected, 
            actual, 
            "EstimateReturnToInitialStateCost");
    }

    void EstimateUnsafeStateCost()
    {
        CrossingState c = CrossingState(true, 2, 3);
        vector<CrossingState> visited;

        int expected = 4092;
        int actual   = c.EstimateCost(visited);
        tf.ASSERT_INT_EQUALS(expected, actual, "EstimateUnsafeStateCost");
    }

    void ChooseFirstSuccessor()
    {
        CrossingState c        = CrossingState(true, 3, 3);
        CrossingState expected = CrossingState(false, 2, 2);

        Program p;
        CrossingState actual   = p.SelectNext(c);
        tf.ASSERT_STRING_EQUALS(
            expected.str(), 
            actual.str(), 
            "ChooseFirstSuccessor");
    }

    void SafeLeftRightFatal()
    {
        CrossingState c = CrossingState(false, 1, 2);

        tf.ASSERT_FALSE(c.IsSafe(), "SafeLeftRightFatal");
    }

    void DoNotBacktrack()
    {
        CrossingState c        = CrossingState(true, 3, 1);
        CrossingState expected = CrossingState(true, 2, 2);

        Program p;
        CrossingState first    = p.SelectNext(c);
        CrossingState actual   = p.SelectNext(first);
        tf.ASSERT_STRING_EQUALS(
            expected.str(), 
            actual.str(), 
            "DoNotBacktrack");
    }

    void SafeNoMissionariesHere(){
        CrossingState c = CrossingState(true, 0, 3);
        tf.ASSERT_TRUE(c.IsSafe(), "SafeNoMissionariesHere");
    }

    void SafeNoMissionariesThere(){
        CrossingState c = CrossingState(true, 3, 2);
        tf.ASSERT_TRUE(c.IsSafe(), "SafeNoMissionariesThere");
    }

public:

    // Execute all configured unit tests.
    void RunTests()
    {
        SafeNoMissionariesHere();
        SafeNoMissionariesThere();
        DoNotBacktrack();
        ChooseFirstSuccessor();
        EstimateUnsafeStateCost();
        EstimateReturnToInitialStateCost();
        EstimateInitialStateCost();
        SafeLeftRightFatal();
        SafeLeftState();
        FatalRightState();
        MoveMixedLeft();
        MoveTwoMissionariesRight();
        MoveTwoCannibalsLeft();
        SelectMovesWithMixedFromLeft();
        SelectMovesWithMixedFromRight();
        SelectMissionaryMovesFromLeft();
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
        cout << tf.GetPassCount() << "/";
        cout << tf.GetPassCount() + tf.GetFailCount() << endl;
    }
};
#endif
