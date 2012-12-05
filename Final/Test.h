#ifndef TESTS_H
#define TESTS_H

#include "TestFramework.h"
#include "Move.h"

using namespace std;

class Tests{
    TestFramework tf;

    void VerifyMove()
    {
        string expected = "Moving Left, with 2 missionaries, and 1 cannibals.";

        Move m = Move(false, 2, 1);
        tf.ASSERT_STRING_EQUALS( expected,m.str(), "VerifyMove");     
    }
public:

    // Execute all configured unit tests.
    void RunTests()
    {
        VerifyMove();
        cout << tf.GetPassCount() << "/" << tf.GetPassCount() + tf.GetFailCount() << endl;
    }
};
#endif
