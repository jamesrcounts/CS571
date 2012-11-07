#ifndef PROGRAM_H
#define PROGRAM_H

using namespace std;

class Program
{
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
        return GetArgumentAt(argc, argv, 1, "").compare("TEST") == 0;
    }
};
#endif