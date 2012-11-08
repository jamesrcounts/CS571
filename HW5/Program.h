#ifndef PROGRAM_H
#define PROGRAM_H

#include <sstream>
#include <algorithm>
#include "Parser.h"

using namespace std;

class Program
{
    Parser parser;  

    std::vector<string> facts;  
    std::vector<string> derived_facts;
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

    std::vector<string> GetFacts()
    {
        return facts;
    }

    string GetFact(int i)
    {
        if(i < (int)facts.size())
        {
            return facts[i];
        }

        return "";
    }

    string FormatFact(int i)
    {
        return GetFact(i);
    }

    void Parse(string input)
    {
        parser.Parse(input);
        facts = parser.GetFacts();
        unused_rules = parser.GetRules();
    }

    void Evaluate()
    {
        while(EvaluateOnce()){}
    }

    int EvaluateOnce()
    {
        std::vector<Rule> working_set(unused_rules.begin(), unused_rules.end());
        for (int i = 0; i < (int)working_set.size(); ++i)
        {
            if(working_set[i].Match(facts))
            {
               std::vector<string> implications;
               implications = working_set[i].GetImplications();
               for (int j = 0; j < (int)implications.size(); ++j)
               {
                   facts.push_back(implications[j]);
               }
               
               vector<Rule>::iterator it;
               it = find(unused_rules.begin(), unused_rules.end(), working_set[i]);
               if(it != unused_rules.end())
               {
                   unused_rules.erase(it);
               }

               return 1;
            }
        }

        // When we get here it means none of the rules matched the facts
        return 0;
    }
};
#endif