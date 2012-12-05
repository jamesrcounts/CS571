#ifndef TESTS_H
#define TESTS_H

#include "TestFramework.h"
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
        {  for (int i = 0; i < (int)expected.size(); ++i)
            {
                tf.ASSERT_STRING_EQUALS(expected[i], actual[i].str(), expected[i]);
            }
        }
    }
public:

    // Execute all configured unit tests.
    void RunTests()
    {
        GenerateAllMoves();
        VerifyMoveException();
        VerifyMoveLeft();
        VerifyMoveRight();
        cout << tf.GetPassCount() << "/" << tf.GetPassCount() + tf.GetFailCount() << endl;
    }
};
#endif
