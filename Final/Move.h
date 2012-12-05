#ifndef MOVE_H
#define MOVE_H

#include <exception>

using namespace std;

/*
An exception which indicates that the boat is over filled.
*/
class MoveException : public exception
{
    virtual const char* what() const throw()
    {
        return "Too many people in the boat!";
    }
} movex;

/*
Describes a move from one state to another.
*/
class Move
{
    /*
    True if the boat is moving to the right, otherwise assume boat is
    moving left.
    */
    bool boat_moving_right;

    /*
    Number of missionaries on the boat.
    */
    int missionaries_moving;

    /*
    Number of cannibals on the boat.
    */
    int cannibals_moving;

public:
    /*
    Initializes a new instance of the Move class.
    moving_to_right - true if the boat is moving right; false if left.
    missionaries    - how many missionaries in boat?
    cannibals       - how many cannibals in boat?
    Remarks: boat only seats 2.
    */
    Move(bool moving_to_right, int missionaries, int cannibals)
    {
        if(2 < missionaries + cannibals)
        {
            throw movex;
        }

        boat_moving_right = moving_to_right;
        missionaries_moving = missionaries;
        cannibals_moving = cannibals;
    }

    ~Move(){}

    /*
    Creates a string representation of the object for display and testing.
    */
    string str(){
        stringstream ss;
        ss << "Moving " << (boat_moving_right ? "Right" : "Left");
        ss << ", with " << missionaries_moving << " missionaries, and ";
        ss << cannibals_moving << " cannibals.";
        return ss.str();
    }
};
#endif