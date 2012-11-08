#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <sstream>
#include <algorithm>

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

	vector<string> GetImplications()
	{
		return implications;
	}

	bool Match(vector<string> facts)
	{
		for (int i = 0; i < (int)predicates.size(); ++i)
		{
			vector<string>::iterator it;
			it = find(facts.begin(), facts.end(), predicates[i]);
			if(it == facts.end())
			{
				return 0;
			}
		}
		return 1;
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

	bool operator==(Rule other)
	{
		return str().compare(other.str()) == 0;
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

	std::vector<string> GetFacts()
	{
		return facts;
	}

	std::vector<Rule> GetRules()
	{
		return rules;
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