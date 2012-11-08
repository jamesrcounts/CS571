% cs571 Yoshii - family relations as rules and facts

parent(pam,bob).
parent(tom,bob).
parent(tom,liz).
parent(bob,ann).
parent(bob,pat).
parent(pat,jim).



female(pam).
female(liz). 
female(pat).
female(ann).

male(tom).
male(bob). 
male(jim). 



mother(X,Y) :- parent(X,Y), female(X).
father(X,Y) :- parent(X,Y), male(X).


