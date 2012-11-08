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

    void ParseAll(string input)
    {
        Parser p;
        p.Parse(input);
        tf.ASSERT_STRING_EQUALS(
            "[PASSED-AI] [NICE] ",
            p.FormatFacts(),
            "ParseAll Facts");
        tf.ASSERT_STRING_EQUALS(
            "[[SWEET] [SMART] [IMPLIES] [SUCCESSFUL] ] [[SWEET] [SMART] [IMPLIES] [POPULAR] ] [[NICE] [IMPLIES] [SWEET] ] [[PASSED-AI] [IMPLIES] [SMART] ] ",
            p.FormatRules(),
            "ParseAll Rules");
    }

    void ParseWithProgram(string input)
    {
        std::vector<string> expected;
        expected.push_back("PASSED-AI");
        expected.push_back("NICE");

        Program p;
        p.Parse(input);
        for (int i = 0; i < (int)expected.size(); ++i)
        {
            tf.ASSERT_STRING_EQUALS(expected[i], p.FormatFact(i), expected[i]);
        }
    }

    void EvaluateOnce(string input)
    {
        std::vector<string> expected;
        expected.push_back("PASSED-AI");
        expected.push_back("NICE");
        expected.push_back("SWEET");

        Program p;
        p.Parse(input);
        p.EvaluateOnce();
        for (int i = 0; i < (int)expected.size(); ++i)
        {
            tf.ASSERT_STRING_EQUALS(expected[i], p.FormatFact(i), expected[i]);
        }
    }

    void EvaluateTwice(string input)
    {
        std::vector<string> expected;
        expected.push_back("PASSED-AI");
        expected.push_back("NICE");
        expected.push_back("SWEET");
        expected.push_back("SMART");

        Program p;
        p.Parse(input);
        p.EvaluateOnce();
        p.EvaluateOnce();
        for (int i = 0; i < (int)expected.size(); ++i)
        {
            tf.ASSERT_STRING_EQUALS(expected[i], p.FormatFact(i), expected[i]);
        }
    }

    void EvaluateAll(string input)
    {
        std::vector<string> expected;
        expected.push_back("PASSED-AI");
        expected.push_back("NICE");
        expected.push_back("SWEET");
        expected.push_back("SMART");
        expected.push_back("SUCCESSFUL");
        expected.push_back("POPULAR");

        Program p;
        p.Parse(input);
        p.Evaluate();
        for (int i = 0; i < (int)expected.size(); ++i)
        {
            tf.ASSERT_STRING_EQUALS(expected[i], p.FormatFact(i), expected[i]);
        }   
    }

    // Execute all configured unit tests.
    void RunTests(string input)
    {
        ParseFact();
        ParseTwoFacts();
        ParseSimpleRule();
        ParseCompoundRule();
        ParseAll(input);
        ParseWithProgram(input);
        EvaluateOnce(input);
        EvaluateTwice(input);
        EvaluateAll(input);
        cout << tf.GetPassCount() << "/" << tf.GetPassCount() + tf.GetFailCount() << endl;

    }
};
#endif