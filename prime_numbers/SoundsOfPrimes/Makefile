
#default values
N=100000
MOD=88
DUR=1000
SCALE=0.05
F0=0
F1=1
SMOOTH=10


all: prime_seive
primes: primes.c
	gcc -lm -std=c99 -Ofast -o primes primes.c
modseq: modseq.c
	gcc -lm -std=c99 -Ofast -o modseq modseq.c
fib: fib.c
	gcc -std=c99 -Ofast -o fib fib.c
blend: blend.c
	gcc -std=c99 -Ofast -o blend blend.c

prime_listen: primes modseq blend
	./primes $(N) | ./modseq $(MOD) $(DUR) $(SCALE) | ./blend $(SMOOTH) | aplay
fib_listen: modseq fib blend
	./fib $(F0) $(F1) | ./modseq $(MOD) $(DUR) $(SCALE) | ./blend $(SMOOTH) | aplay

