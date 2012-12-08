#ifndef CROSSINGSTATE_H
#define CROSSINGSTATE_H

#include "Move.h"

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

	/*
	Initializes a new instance of the CrossingState class.
	*/
	void Initialize(
		bool boat_on_right, 
		int missionaries_on_right, 
		int cannibals_on_right)
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

public:
	/*
	Initializes a new instance of the CrossingState class.
	Remarks: Creates the initial state by default.
	*/
	CrossingState()
	{
		Initialize(true, 3, 3);		
	}

	/*
	Initializes a new instance of the CrossingState class.
	boat_on_right:         true if the boat is located on the right bank; 
							otherwise false.
	missionaries_on_right: count of missionaries on the right bank; assume 
							others are on the left bank.
	cannibals_on_right:    count of cannibals on the right bank; assume others 
							are on the left bank.
	Remarks: There cannot be more than six people in a CrossingState.  Maximum 
				of 3 missionaries and 3 cannibals.  Since the state only stores 
				the status of the right bank, there can be a minimum of 0 people
				if everyone has crossed sucessfully.
	*/
	CrossingState(
		bool boat_on_right, 
		int missionaries_on_right, 
		int cannibals_on_right)
	{
		Initialize(boat_on_right, missionaries_on_right, cannibals_on_right);
	}

	~CrossingState(){}

	/*
	Return a value indicating whether the provided Move is possible from this 
	state.
	*/
	bool IsApplicableMove(Move m)
	{
		// The boat must be on this side
		// There must be enough missionaries on this side
		// There must be enough cannibals on this side
		return 		boat == m.BoatOnRight() 
				&& 	m.MissionariesOnBoat() <= MissionariesHere()
				&&  m.CannibalsOnBoat() <= CannibalsHere();
	}

	/*
	Return a value indicating whether the state is safe for the missionaries.
	*/
	bool IsSafe()
	{
		bool safeHere  =    (0 == MissionariesHere()) 
						|| (CannibalsHere() <= MissionariesHere());
		bool safeThere =    (0 == MissionariesThere()) 
						|| (CannibalsThere() <= MissionariesThere());

		return safeHere && safeThere;
	}

	/*
	Gets the count of cannibals on the river bank that has the boat.
	*/
	int CannibalsHere()
	{
		return (boat ? CannibalsOnRight() : 3 - CannibalsOnRight());
	}

	/*
	Gets the count of cannibals on the river bank that does not have the boat.
	*/
	int CannibalsThere()
	{
		return 3 - CannibalsHere();
	}

	/* 
	Gets the count of cannibals on the right river bank.
	*/
	int CannibalsOnRight()
	{
		return cannibals;
	}

	/*
	Estimates the cost of reaching the goal state through this state.
	*/
	int EstimateCost(vector<CrossingState> visited)
	{		
		// The actual cost g(n) = 1 because it will take at least one trip to 
		// reach *this* state, 
		int cost = 1;

		// The estimated cost h(n) = Total people on the right bank.  It will
		// require *at least* one trip across the river to move each person,
		// and on average more than one is required.
		cost += MissionariesOnRight() + CannibalsOnRight();

		// h(n) must include an additional trip if we return to a previously 
		// visited state.  If we move backward, we must make at least one more
		// trip to move forward again.
		cost += WasVisited(visited) ? 1 : 0;

		// h(n) must include a suffciently large death penalty to prevent the 
		// missionaries from ever choosing an unsafe state.  In terms of "trips"
		// we can rationalize this by saying that when a missionary dies, they 
		// wont be able to reach the goal state--even if allowed an infinite 
		// number of trips across the river.
		cost = IsSafe() ? cost : 4092;

		return cost;
	}

	/*
	Generates the state that would result from making the provided move
	from this state.
	*/
	CrossingState GenerateSuccessor(Move m)
	{
		int missionaries_on_right = (	m.MovingRight() ?
			MissionariesOnRight() + m.MissionariesOnBoat() : 
			MissionariesOnRight() - m.MissionariesOnBoat());	
		int cannibals_on_right 	  = (	m.MovingRight() ?
			CannibalsOnRight() + m.CannibalsOnBoat() :
			CannibalsOnRight() - m.CannibalsOnBoat());
		return CrossingState(
			m.MovingRight(), 
			missionaries_on_right, 
			cannibals_on_right);
	}

	/*
	Gets the count of missionaries on the river bank that has the boat.
	*/
	int MissionariesHere()
	{
		return (boat ? MissionariesOnRight() : 3 - MissionariesOnRight());
	}

	/*
	Gets the count of missionaries on the river bank that does not have the 
	boat.
	*/
	int MissionariesThere()
	{
		return 3 - MissionariesHere();
	}

	/*
	Gets the count of missionaries on the right river bank.
	*/
	int MissionariesOnRight()
	{
		return missionaries;
	}

	/*
	Gets a value indicating whether this state has already been visited.
	*/
	bool WasVisited(vector<CrossingState> visited)
	{
		vector<CrossingState>::iterator it;
		it = find(visited.begin(), visited.end(), *this);
		return it != visited.end();
	}

    /*
    Creates a string representation of the object for display and testing.
    */
    string str()
    { 
    	stringstream ss;
    	ss << "Boat on " << (boat ? "Right" : "Left") << " bank, with ";
    	ss << MissionariesHere() << " missionaries, and ";
    	ss << CannibalsHere() << " cannibals.";
    	return ss.str();
    }

	/*
	When the string representation of two states are equal, then the states are 
	equivalent.
	*/
	bool operator==(CrossingState other)
	{
		return str().compare(other.str()) == 0;
	}

	/*
	When the string representations of two states are not equal, then the states
	are not equivalent.
	*/
	bool operator!=(CrossingState other)
	{
		return !(*this == other);
	}

};
#endif

