#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

/*
An implication rule
*/
class Rule
{
	/*
	Set of facts
	*/
	vector<string> predicates;
	
	/*
	Set of facts
	*/
	vector<string> implications;

public:
	/*
	Initialize a new rule instance.  

	predicates   - If all predicates are facts then
	implications - All implications are facts.
	*/
	Rule(vector<string> predicates, vector<string> implications)
	{
		this->predicates = predicates;
		this->implications = implications;
	}

	/*
	Read the implication collection.
	*/
	vector<string> GetImplications()
	{
		return implications;
	}

	/*
	Returns a true value when this rule's predicates are satisfied.
	*/
	bool Match(vector<string> facts)
	{
		// Iterate over the predicates.
		for (int i = 0; i < (int)predicates.size(); ++i)
		{
			// If any predicate is not found
			vector<string>::iterator it;
			it = find(facts.begin(), facts.end(), predicates[i]);
			if(it == facts.end())
			{
				// The rule does not match.
				return 0;
			}
		}

		// The rule matches.
		return 1;
	}

	/*
	Format the rule as a readable string.
	*/
	string str()
	{
		stringstream ss;
		for (int i = 0; i < (int)predicates.size(); ++i)
		{
			ss << "[" << predicates[i] << "] ";
		}

		ss << "[IMPLIES] ";

		for (int i = 0; i < (int)implications.size(); ++i)
		{
			ss << "[" << implications[i] << "] ";
		}

		return ss.str();
	}

	/*
	When the string representation of two rules are equal, the the rules are equivalent.
	*/
	bool operator==(Rule other)
	{
		return str().compare(other.str()) == 0;
	}
};

/*
Decomposes text input into rules and facts.
*/
class Parser{
	/*
	Set of facts
	*/
	vector<string> facts;
	
	/*
	Set of rules
	*/
	vector<Rule> rules;
	
	//	int state;
public:
	/*
	Parser()
	{
		state = 0;
	}*/

	/* 
	Read the facts.
	*/
	std::vector<string> GetFacts()
	{
		return facts;
	}

	/* 
	Read the rules.
	*/
	std::vector<Rule> GetRules()
	{
		return rules;
	}

	/*
	Format the facts as a readable string.
	*/
	string FormatFacts()
	{
		stringstream ss;
		for (int i = 0; i < (int)facts.size(); ++i)
		{
			ss << "[" << facts[i] << "] ";
		}
		return ss.str();
	}

	/*
	Format the rules as a readable string.
	*/
	string FormatRules()
	{
		stringstream ss;
		for (int i = 0; i < (int)rules.size(); ++i)
		{
			ss << "[" << rules[i].str() << "] ";
		}

		return ss.str();
	}

	/*
	Finds rules and facts in the input string.
	*/
	void Parse(string input)
	{
		stringstream ss(input);
		string line;

		// Go line by line.
		while(getline(ss, line))
		{
			// if there is no arrow
			if(line.find("->") == string::npos)
			{
				// it is a fact
				facts.push_back(line);
			}
			else
			{
				// it is a rule
				stringstream tt(line);
				vector<string> predicates;
				vector<string> implications;
				string buffer;

				// A rule has two parts.
				int rule_state = 0;
				while(tt >> buffer)
				{
					// The arrow divides the two parts.
					if(buffer.compare("->") == 0)
					{
						// After the arrow we have implications.
						rule_state = 1;
					}
					else
					{
						// Before the arrow we have predicates.
						// The caret is useless, we ignore it.
						if(buffer.compare("^") != 0)
						{
							// If we are reading predicates
							if(rule_state == 0)
							{
								// We add another predicate.
								predicates.push_back(buffer);
							}
							else
							{
								// Or we are reading implications, 
								// so we add an implication.
								implications.push_back(buffer);
							}
						}
					}
				}

				// We build a rule from the predicates and implications.
				Rule r(predicates, implications);
				rules.push_back(r);
			}
		}
	}
};
#endif