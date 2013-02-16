#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

class TestFramework
{
    /*
    | The number of passing tests.
    */
    int pass;

    /*
    | The number of failing tests.
    */
    int fail;

public:
    /*
    | Initializes a new instance of the TestFramework class
    */
    TestFramework()
    {
        pass = 0;
        fail = 0;
    }

    // Prints PASS when the parameter is true, otherwise, false.
    void EVALUATE(bool equals)
    {
        if(equals)
        {
            pass++;
            cout << "PASS ";
        }
        else
        {
            fail++;
            cout << "FAIL ";
        }
    }

    // Converts an integer into a string.
    string ToString(int i)
    {
        stringstream ss;
        string s;
        ss << i;
        s = ss.str();
        return s;
    }

    /*
    | Converts an array of standard strings into an array of mutable c-style
    | strings.
    */
    void ToCStrArray(int size, string source[], char *argv[])
    {
        for(int i = 0; i < size; i++)
        {
            string j = source[i];
            argv[i] = new char[j.size()];
            strncpy(argv[i], j.c_str(), j.size());
            argv[i][j.size()] = '\0';
        }
    }

    // Gets a message to note a single item in a sequence.
    string GetItemMessage(string message, int i)
    {
        message += " [";
        message += ToString(i);
        message += "]";
        return message;
    }


    // Gets a message to note the size of a sequence.
    string GetSizeMessage(string message)
    {
        return message += " SIZE";
    }

public:
    // Asserts that the value is true.
    void ASSERT_TRUE(bool value, string message)
    {
        EVALUATE(value);
        cout << message << endl;
    }

    // Asserts that the value is false.
    void ASSERT_FALSE(bool value, string message)
    {
        ASSERT_TRUE(!value, message);
    }

    // Prints pass/fail with a message based on whether to integers are the
    // same.
    void ASSERT_INT_EQUALS(int expected, int actual, string message)
    {
        EVALUATE(expected == actual);
        cout << message << " Expected: [" << expected;
        cout << "] Actual: [" << actual << "]" << endl;
    }

    /*
    | Prints pass/fail messages based on whether two strings are the same.
    */
    void ASSERT_STRING_EQUALS(string expected, string actual, string message)
    {
        EVALUATE(expected.compare(actual) == 0);
        cout << message << " Expected: [" << expected;
        cout << "] Actual: [" << actual << "]" << endl;
    }

    // Evaluates two integer sequences and prints messages based on whether they
    // are the same.
    void ASSERT_INT_SEQUENCE_EQUALS(
        vector<int> expected,
        vector<int> actual,
        string message)
    {
        ASSERT_INT_EQUALS(
            expected.size(),
            actual.size(),
            GetSizeMessage(message));

        if(expected.size() == actual.size())
        {
            for(unsigned int i = 0; i < expected.size(); i++)
            {
                ASSERT_INT_EQUALS(
                    expected[i],
                    actual[i],
                    GetItemMessage(message, i));
            }
        }
    }

    // Evaluates the pointer and prings messages based on whether it is null.
    bool CHECK_NOT_NULL(void* ptr, string message)
    {
        bool result = ptr == NULL;
        ASSERT_FALSE(result, message += " null check.");
        return !result;
    }

    /*
    | Gets a value indicating how many tests passed.
    */
    int GetPassCount()
    {
        return pass;
    }

    /*
    | Gets a value indicating how many tests failed.
    */
    int GetFailCount()
    {
        return fail;
    }
};
#endif
