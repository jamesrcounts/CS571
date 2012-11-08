% cs571 Yoshii - HW5 program

eagle(bill).

wings(X) :- fly(X).
fly(Y) :- bird(Y).
bird(Z) :- eagle(Z).

