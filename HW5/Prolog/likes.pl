% cs571 Yoshii - backtracking example using likes


likes(john,bill).
likes(john,wine).
likes(mary,bill).
likes(sue,john).

likes(john,X) :- likes(X,wine).              
likes(john,X) :- female(X), likes(X,john).   

female(mary).
female(sue).
