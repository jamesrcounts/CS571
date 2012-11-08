eagle(bill).
airplane(dc10).
find(Who) :- wings(Who), write(Who).
wings(X) :- fly(X).
fly(mary).
fly(X) :- airplane(X).
fly(Y) :- bird(Y).
bird(Z) :- eagle(Z).
