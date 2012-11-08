#ifndef TESTS_H
#define TESTS_H

#include "Parser.h"
#include "TestFramework.h"

using namespace std;

class Tests{
    TestFramework tf;
public:
    string InvokeParse(string input)
    {
        Parser p;
        p.Parse(input);
        string result = p.FormatFacts();
        return result;
    }

    string InvokeParseRule(string input)
    {
        Parser p; 
        p.Parse(input);
        string result = p.FormatRules();
        return result;
    }

    // Parse a single fact
    void ParseFact()
    {
        string result = InvokeParse("FACT");    
        tf.ASSERT_STRING_EQUALS(
            "[FACT] ", 
            result, 
            "Parse Single Fact");
    }

    // Parse two facts
    void ParseTwoFacts()
    {
        string expected = "[PASSED-AI] [NICE] ";
        tf.ASSERT_STRING_EQUALS(
            expected,
            InvokeParse("PASSED-AI\nNICE"),
            "ParseTwoFacts");
    }

    void ParseSimpleRule()
    {
        string expected = "[[NICE] [IMPLIES] [SWEET] ] ";
        tf.ASSERT_STRING_EQUALS(
            expected,
            InvokeParseRule("NICE -> SWEET"),
            "ParseSimpleRule");
    }

    void ParseCompoundRule()
    {
        string expected = "[[SWEET] [SMART] [IMPLIES] [SUCCESSFUL] [UGLY] ] ";
        tf.ASSERT_STRING_EQUALS(
            expected,
            InvokeParseRule("SWEET ^ SMART -> SUCCESSFUL ^ UGLY"),
            "ParseCompoundRule");
    }

    // Execute all configured unit tests.
    void RunTests()
    {
        ParseFact();
        ParseTwoFacts();
        ParseSimpleRule();
        ParseCompoundRule();
        cout << tf.GetPassCount() << "/" << tf.GetPassCount() + tf.GetFailCount() << endl;

    }
};
#endif