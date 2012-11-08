#ifndef PROGRAM_H
#define PROGRAM_H

#include <sstream>
#include <algorithm>
#include "Parser.h"

using namespace std;

/*
The production system
*/
class Program
{
    Parser parser;  

    /*
    All Known Facts
    */
    std::vector<string> facts;  
    //std::vector<string> derived_facts;
    
    /*
    Set of rules that have not been matched yet.
    */
    std::vector<Rule> unused_rules;

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
        return GetArgumentAt(argc, argv, 2, "").compare("TEST") == 0;
    }

    /*
    Read-only property returns the collection of facts.
    */
    vector<string> GetFacts()
    {
        return facts;
    }

    /*
    Get a specific fact by index or empty string if out of range.
    */
    string GetFact(int i)
    {
        if(i < (int)facts.size())
        {
            return facts[i];
        }

        return "";
    }

    /*
    Additional formatting for facts - deprectaed.
    */
    string FormatFact(int i)
    {
        return GetFact(i);
    }

    /*
    Use the parser to read the input.
    */
    void Parse(string input)
    {
        parser.Parse(input);
        facts = parser.GetFacts();
        unused_rules = parser.GetRules();
    }

    /*
    Invoke the evaluation function until no more facts can be derived from the knowledge base.
    */
    void Evaluate()
    {
        while(EvaluateOnce()){}
    }

    /*
    The evaluation function tries to find the first rule that matches the known facts, then use
    it to derive additional facts.

    Returns a true value when new facts have been derived; otherwise returns a false value.
    */
    int EvaluateOnce()
    {
        // Iterate over a copy of the unused rules.
        std::vector<Rule> working_set(unused_rules.begin(), unused_rules.end());
        for (int i = 0; i < (int)working_set.size(); ++i)
        {
            // If the rule matches the known facts.
            if(working_set[i].Match(facts))
            {
                // Use it to derive new facts.
               std::vector<string> implications;
               implications = working_set[i].GetImplications();
               for (int j = 0; j < (int)implications.size(); ++j)
               {
                   facts.push_back(implications[j]);
               }
               
               // Delete it from the set of unused rules.
               vector<Rule>::iterator it;
               it = find(unused_rules.begin(), unused_rules.end(), working_set[i]);
               if(it != unused_rules.end())
               {
                   unused_rules.erase(it);
               }

               // Stop iterating; indicate that a rule matched.
               return 1;
            }
        }

        // When we get here it means none of the rules matched the facts
        // (or there were no rules)
        return 0;
    }
};
#endif