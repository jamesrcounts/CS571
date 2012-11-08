% cs571 Yoshii - Water Jug Program in Prolog

% Member function definition as two rules.
membr(X,[X|L]).
membr(X,[Z|L]) :- membr(X,L).

% Top level goal is path.
% e.g. Invoke it by saying path(state(0,0), state(_,2), []).

% To find a path from State to Goal accumulating the visited states in Sofar,
%    move from State to Next and
%    if Next has not been visited, 
%    find a path from Next to Goal. (note: Next is added so SoFar)
path(State,Goal,Sofar) :-
   move(State,Next),
   \+ membr(Next,Sofar),
   path(Next,Goal,[Next|Sofar]).

% When we have reached the goal state, display the Path
path(Goal,Goal,Path) :- write(Path).


% ------------------------------------------------------

% Here are the move rules.  
% Note that X is for the 3 gallon jug. Y is for the 4 gallon jug.

% rule 1: Dump the 4 gallon jug
move(state(X,Y),state(X,0)).

% rule 2: Dump the 3 gallon jug
move(state(X,Y),state(0,Y)).

% rule 3: Fill the 3 gallon jug  
move(state(X,Y),state(3,Y)).

% rule 4: Fill the 4 gallon jug
move(state(X,Y),state(X,4)).

% rule 5: If 4 gallon jug is not full, and 3 gallon jug has
%    enough water to fill the 4 gallon jug, do so
move(state(X,Y),state(X1,4)) :-
   A is 4-Y, A > 0, X1 is X-A, X1 >= 0.

% rule 6: Pour all water in the 3 gallon jug into 4 gallon jug
%         if doing so will not overflow the 4 gallon jug
move(state(X,Y),state(0,Y1)) :-
   Y1 is Y+X, Y1 =< 4.

% rule 7: If 3 gallon jug is not full, and 4 gallon jug has
%   enough water to fill the 3 gallon jug, do so
move(state(X,Y),state(3,Y1)) :-
   A is 3-X, A >0, Y1 is Y-A,Y1 >= 0.

% rule 8: Pour all water in the 4 gallon jug into 3 gallon jug
%         if doing so will not overflow the 3 gallon jug 
move(state(X,Y),state(X1,0)) :-
   X1 is X+Y, X1 =< 3.






