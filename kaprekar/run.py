#!/usr/bin/python

KAPREKAR_CONST=6174

def ddig(n):
    l=list(str(n))
    l.sort()
    l.reverse()
    return int(''.join(l))

def adig(n):
    l=list(str(n))
    l.sort()
    return int(''.join(l))

def valid(n):
    l=list(str(n))
    s=set(str(n))
    return len(l) != 4 or len(s) <= 1

def next_kaprekar(n):
    if valid(n):
        return None
    return ddig(n) - adig(n)

def count_kaprekar(n):
    count = 0
    while n != KAPREKAR_CONST and n != None:
        n = next_kaprekar(n)
        count += 1
    if n == None:
        return -1
    return count


print( [ (n,count_kaprekar(n)) for n in range(1000,9999) ] )
