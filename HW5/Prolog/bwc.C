
// Backward Chanining Engine

//*****************************************************************************
// IMPLEMENTATION OF PROOFS:  using BWC (=backward chaining)  CS571
//
//Your knowledge base:
//
//   PASSED-AI
//   NICE
//
//   SWEET ^ SMART -> SUCCESSFUL
//   SWEET ^ SMART -> POPULAR
//   NICE -> SWEET
//   PASSED-AI -> SMART
//
// BWC with Propositional Logic  

// Algorithm:
//  Start with POPULAR and match
//  While stack is not empty  (more subgoals to do)
//    Retrieve the top of the stack as current goal.
//    Match it against facts.
//      If a match occurs, pop the current goal.
//    Match it against the RHS of the above rules
//      If a match occurs, pop the current goal, LHS pushed as subgoals 
//    If no match occured, stop the loop

//  This algorithm does not take into account multiple rules
//  matching a current goal.  That is why, I can accumulate all
//  subgoals before pushing them.  

// If I were to account for multiple matches,
//   as soon as a match is found
//      pop the goal and push it on Backup_Stack along with
//      information on which rule it matched, and
//      push the subgoals onto Goal_Stack
//  and when a goal fails,
//    pop the failed goal,
//    pop Backup_Stack and it becomes the current goal
//    knowing which rule it matched before
//     start the match further down the rule base
//

#include "sv.h"
#include <stdlib.h>

int main() {

  stack Goal_stack;    	      // a new stack object to hold goals
  el_t goal;	      	      // used to check for subgoals or if fact
  int i=1;    	              // counter for generated subgoals
  el_t Subgoals[10];          // array used to store generated subgoals 
  el_t key;                   // user inputted goal
  int fact;                   // flag used to see if subgoal matched fact
  
  cout << "Enter goal: ";
  cin  >> key;  
  Goal_stack.push(key);     
  
  // a valid goal will exhaust the entire stack

  while (!Goal_stack.isEmpty()) {
    // the top element is not removed from stack; just look at it
    Goal_stack.topElem(goal); 

    i=0;       // number of generated subgoals must be reset every loop
    fact=0;    // fact flag must be cleared every loop
    
    // match against facts first
    if (goal == "PASSED-AI") {fact=1;}  // the goal matched a fact
    if (goal=="NICE")        {fact=1;}  // the goal matched a fact

    // rules generate subgoals if goal matches the conclusion part
    if (goal =="SMART") {Subgoals[i]="PASSED-AI"; i++;}
    if (goal=="SWEET")  {Subgoals[i]="NICE"; i++;}
    if (goal=="POPULAR") {
      Subgoals[i]="SMART";
      i++;
      Subgoals[i]="SWEET";
      i++;
    }
    if (goal == "SUCCESSFUL") {
      Subgoals[i]="SMART";
      i++;
      Subgoals[i]="SWEET";
      i++;
    }

    if (fact) cout << "Matched a fact!" << endl;

    // if the current goal created subgoals or matched a fact it is popped
    if ((i>0) || (fact))
        { Goal_stack.pop(goal); cout << "Pop " << goal << endl; }

    // otherwise that particular goal fails and execution is stopped
    else { cout << "goal failed." << endl; exit(0); }

    // all generated subgoals are pushed onto the stack
    for(int c=0;c<i;c++) {
        cout << "Pushing new sugoal: " << Subgoals[c] << endl;
        Goal_stack.push(Subgoals[c]);
    }
  }// end of while

  cout << "Success!!" << endl;

}// end of main()


