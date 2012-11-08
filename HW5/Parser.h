#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <sstream>

using namespace std;

class Rule
{
	vector<string> predicates;
	vector<string> implications;

public:
	Rule(vector<string> predicates, vector<string> implications)
	{
		this->predicates = predicates;
		this->implications = implications;
	}

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
};

class Parser{
	vector<string> facts;
	vector<Rule> rules;
	int state;
public:
	Parser()
	{
		state = 0;
	}

	string FormatFacts()
	{
		stringstream ss;
		for (int i = 0; i < (int)facts.size(); ++i)
		{
			ss << "[" << facts[i] << "] ";
		}
		return ss.str();
	}

	string FormatRules()
	{
		stringstream ss;
		for (int i = 0; i < (int)rules.size(); ++i)
		{
			ss << "[" << rules[i].str() << "] ";
		}

		return ss.str();
	}

	void Parse(string input)
	{
		stringstream ss(input);
		string line;
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

				int rule_state = 0;
				while(tt >> buffer)
				{
					if(buffer.compare("->") == 0)
					{
						rule_state = 1;
					}
					else
					{
						if(buffer.compare("^") != 0)
						{
							if(rule_state == 0)
							{
							
								predicates.push_back(buffer);
							}
							else
							{
								implications.push_back(buffer);
							}
						}
					}
				}

				Rule r(predicates, implications);
				rules.push_back(r);
			}
		}
	}
};
#endif