% Functii pentru a selecta dintr-o pereche elementul dorit.
first([A,_], F) :- F=A.
second([_,B], F) :- F=B.


% Functii de prelucrare si verificare a formulei.
get(C,C).
get(global(C), C).
get(future(C), C).
get(not(C), C).
get(next(C), C).
get(and(F1, F2), F1, F2).
get(or(F1, F2), F1, F2).
get(until(C1, C2), C1, C2).

getAtom(atom(_), atom).
getAtom(X,X).
getAtom(atom,atom).

check(Atom,_,_) :- Atom = valid.
check(Atom,G,L) :- Atom = global(Color), try(Color, G, L),!.

try(Color, [C,E], [H|T]) :- colorOfNode(H,Color,C), try(Color, [C,E], T).


% Aux
contains(E, [E|_]) :- !.
contains(E, [H|T]) :- E \= H, contains(E, T).


% LISTA C
containsNode(N, [H|_]) :- first(H, F), F = N, !.
containsNode(N, [H|T]) :- first(H, F), F \= N, containsNode(N, T).

containsColor(C, [H|_]) :- second(H,S), S = C, !.
containsColor(C, [H|T]) :- second(H,S), S \= C, containsColor(C,T).

colorOfNode(N, C, [H|_]) :- first(H, F), F = N, second(H,C), !.
colorOfNode(N, C, [H|T]) :- first(H, F), F \= N, colorOfNode(N, C, T).

% LISTA E
member(E, [E|_]).
member(E, [_|T]) :- member(E, T).

node(X, [C,_]) :- containsNode(X,C).
edge(X, Y, [_,E]) :- member([X,Y], E).            


% Fin
minlist([H], H).
minlist([H|T],R) :- minlist(T,MR), length(MR,L1), length(H, L2), (L1 > L2, R=H ; R=MR),!.

dfs(X,Y,G,Visited, [Y|Visited]) :- edge(X,Y,G), not(member(Y, Visited)).
dfs(X,Y,G,Visited, P) :- edge(X,Z,G), not(member(Z, Visited)), 
                              dfs(Z, Y, G, [Z|Visited], P).

getAllPath(X,Y,G,Visited,L) :- findall(P, dfs(X,Y,G,Visited,P),L).

getPath(From, To, Graph, _, Path) :-getAllPath(From,To,Graph,[From],RList), 
					maplist(reverse,RList,List),
					minlist(List,Path),!.
