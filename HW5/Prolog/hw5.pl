eagle(bill).
airplane(dc10).
find(Who) :- wings(Who), write(Who).
wings(X) :- fly(X).
fly(mary).
fly(Y) :- bird(Y).
fly(X) :- airplane(X).
bird(Z) :- eagle(Z).