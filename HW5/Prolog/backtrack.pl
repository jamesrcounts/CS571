% cs571 Yoshii - Prolog Backtracking example


d(apple).
d(apricot).

e(orange).

f(apricot).
f(orange).

a(X) :- b(X), c(X).

b(X) :- d(X).

b(X) :- e(X).

c(X) :- f(X).

