

N=100000
MOD=88
DUR=1000
SCALE=0.05


all: prime_seive
prime_seive: prime_seive.c
	gcc -lm -std=c99 -Ofast -o prime_seive prime_seive.c

run: prime_seive
	./prime_seive $(N) $(MOD) $(DUR) $(SCALE) | aplay

