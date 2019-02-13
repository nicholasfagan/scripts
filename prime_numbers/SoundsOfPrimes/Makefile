
#default values
N=100000
MOD=88
DUR=1000
SCALE=0.05

all: prime_seive
primes: primes.c
	gcc -lm -std=c99 -Ofast -o primes primes.c
fib: fib.c
	gcc -std=c99 -Ofast -o fib fib.c
modseq: modseq.c
	gcc -lm -std=c99 -Ofast -o modseq modseq.c


prime_listen: primes modseq
	./primes $(N) | ./modseq $(MOD) $(DUR) $(SCALE) | aplay
fib_listen: fib modseq
	./fib | ./modseq $(MOD) $(DUR) $(SCALE) | aplay

