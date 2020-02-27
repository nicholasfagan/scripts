#!/usr/bin/swipl -q -t program -s 

program :- pow(2,10,X),write(X),nl.

factorial(N,R) :- fact(1,N,R).
fact(A,0,R) :- R is A.
fact(A,N,R) :- NewA is A*N, NewN is N-1, fact(NewA,NewN,R).
choose(N,K,R) :- factorial(N,Nfact), factorial(K,Kfact), NK is N-K, factorial(NK,NKfact), R is Nfact / (Kfact * NKfact).
paths(A,B,R) :- N is A+B-2, K is B-1, choose(N,K,R).



odd(N) :- 1 is (N mod 2).
even(N) :- 0 is (N mod 2).


pow(_,0,R) :- R is 1.
pow(B,1,R) :- R is B.
pow(B,E,R) :- odd(E),
	NewE is E-1,
	pow(B,NewE,Rec),
	R is Rec * B.
pow(B,E,R) :- even(E),
	NewB is B*B,
	NewE is E/2,
	pow(NewB, NewE, R).


