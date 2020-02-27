#!/usr/bin/python

# Starting from 0 on a number line,
# you would like to make a series of jumps that lead to the integer N.
# On the ith jump, you may move exactly i places to the left or right.
# Find a path with the fewest number of jumps required to get from 0 to N.


# 2^n time complexity
def find_jumps(s,i,n):
    if s == n: return [s]
    if i > n: return None
    left = find_jumps(s-i, i+1, n)
    right = find_jumps(s+i, i+1, n)
    if left == None and right == None: return None
    if left == None: return [s] + right
    if right == None: return [s] + left
    if len(left) < len(right): return [s] + left
    return [s] + right

def jump(N):
    return find_jumps(0,1,N)

import sys


print( jump(int(sys.argv[1]) ))



