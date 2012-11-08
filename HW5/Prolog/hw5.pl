% cs571 Yoshii - HW5 program

eagle(bill).
fly(mary).
airplane(dc10).

find(Who) :- wings(Who), write(Who).
wings(X) :- fly(X).
fly(Y) :- bird(Y).
bird(Z) :- eagle(Z).
fly(X) :- airplane(X).
