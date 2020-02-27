#!/usr/bin/python

nn = 9

a = [ nnn for nnn in reversed(list(range(1,nn+1))) ]
b = []
c = []

def p_stack(s):
    m = 60
    for n in reversed(s):
        print((' ' * int(( m-2*n+1 ) / 2)) +  str(n)*(2*n-1) + (' ' * int((m - 2*n+1)/2) ))

def dump():
    print()
    print()
    print('===== DUMP =====')
    print('A')
    p_stack(a)
    print('B')
    p_stack(b)
    print('C')
    p_stack(c)

def move(N, A, B):
    B.append(A.pop())
    dump()
    print('moved disk',N)

def hanoi(N, A, B, C):
    if N == 0: return
    hanoi(N-1, A, C, B)
    move(N, A, C)
    hanoi(N-1, B, A, C)

dump()
hanoi(len(a), a,b,c)

