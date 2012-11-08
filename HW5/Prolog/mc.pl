% CS571 Yoshii - Missionary and Cannibals example in Prolog

membr(X,[X|L]).
membr(X,[Z|L]) :- membr(X,L).

path(Goal,Goal,Path) :- write(Path).
path(State,Goal,Sofar) :-
   move(State,Next),
   \+ membr(Next,Sofar),
   \+ bad(Next),
   path(Next,Goal,[Next|Sofar]).

move(state(Lm,Lc,Rm,Rc,l),state(Lma,Lc,Rma,Rc,r)) :-
   member(X,[1,2]), Lma is Lm-X, Lma >= 0, Rma is Rm + X.
move(state(Lm,Lc,Rm,Rc,r),state(Lma,Lc,Rma,Rc,l)) :-
   member(X,[1,2]), Rma is Rm-X, Rma >= 0, Lma is Lm + X.

move(state(Lm,Lc,Rm,Rc,l),state(Lm,Lca,Rm,Rca,r)) :-
   member(X,[1,2]), Lca is Lc-X, Lca >= 0, Rca is Rc + X.
move(state(Lm,Lc,Rm,Rc,r),state(Lm,Lca,Rm,Rca,l)) :-
   member(X,[1,2]), Rca is Rc-X, Rca >= 0, Lca is Lc + X.

move(state(Lm,Lc,Rm,Rc,l),state(Lma,Lca,Rma,Rca,r)) :-
   Lc > 0, Lm > 0, Lca is Lc-1, Lma is Lm-1, Rca is Rc + 1, Rma is Rm + 1.
move(state(Lm,Lc,Rm,Rc,r),state(Lma,Lca,Rma,Rca,l)) :-
   Rc > 0, Rm > 0, Rca is Rc-1, Rma is Rm-1, Lca is Lc + 1, Lma is Lm + 1.

bad(state(Lm,Lc,Rm,Rc,_)) :- Lc > Lm, Lm > 0.
bad(state(Lm,Lc,Rm,Rc,_)) :- Rc > Rm, Rm > 0.

