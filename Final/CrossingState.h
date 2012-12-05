#ifndef CROSSINGSTATE_H
#define CROSSINGSTATE_H

using namespace std;

/*
An exception indicating the requested count of missionaries is not allowed.
*/
class MissionaryCrossingException : public exception
{
	virtual const char* what() const throw()
	{
		return "Too many or too few missionaries on the river banks!";
	}
} missxex;

/*
An exception indicating the requested count of cannibals is not allowed.
*/
class CannibalCrossingException : public exception
{
	virtual const char* what() const throw()
	{
		return "Too many or too few cannibals on the river banks!";
	}
} cannxex;

/*
Describes the state of the missionaries and cannibals as they attempt to
cross the river.
*/
class CrossingState
{
	/*
	True if the boat is on the right bank, otherwise false.
	*/
	bool boat;

	/*
	Count of missionaries on the right bank; assume others are on the left side.
	*/
	int missionaries;

	/*
	Count of cannibals on the right bank; assume others are on the left side.
	*/
	int cannibals;

public:
	/*
	Initializes a new instance of the CrossingState class.
	boat_on_right:         true if the boat is located on the right bank; otherwise false.
	missionaries_on_right: count of missionaries on the right bank; assume others are on the left bank.
	cannibals_on_right:    count of cannibals on the right bank; assume others are on the left bank.
	Remarks: There cannot be more than six people in a CrossingState.  Maximum of 3 missionaries
	and 3 cannibals.  Since the state only stores the status of the right bank, there can be a 
	minimum of 0 people if everyone has crossed sucessfully.
	*/
	CrossingState(bool boat_on_right, int missionaries_on_right, int cannibals_on_right)
	{
		if(3 < missionaries_on_right || missionaries_on_right < 0)
		{
			throw missxex;
		}

		if(3 < cannibals_on_right || cannibals_on_right < 0)
		{
			throw cannxex;
		}

		boat = boat_on_right;
		missionaries = missionaries_on_right;
		cannibals= cannibals_on_right;
	}

	~CrossingState(){}

	/*
	Return a value indicating whether the provided Move is possible from this state.
	*/
	bool IsApplicableMove(Move m)
	{
		// The boat must be on this side
		if (boat != m.BoatOnRight())
		{
			return false;
		}
		// There must be enough missionaries on this side
		// There must be enough cannibals on this side
		return true;
	}


    /*
    Creates a string representation of the object for display and testing.
    */
    string str()
	{ 
		stringstream ss;
		ss << "Boat on " << (boat ? "Right" : "Left") << " bank, with ";
		ss << (boat ? missionaries : 3 - missionaries) << " missionaries, and ";
		ss << (boat ? cannibals : 3 - cannibals) << " cannibals.";
		return ss.str();
	}
};
#endif