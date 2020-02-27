#!/usr/bin/python

# 3x3 board with pieces 1-8.
## get to the point
## [[1,2,3],[4,5,6],[7,8,None]]

SOLVED_L = [[1,2,3],[4,5,6],[7,8,None]]

class Board:
    def __init__(self, data, count=0):
        self.data = data
        self.count = count
    def moves(self):
        none_i,none_j = self.find(None)
        for i in range(3):
            if abs(i-none_i) == 1:
                for j in range(3):
                    if abs(j-none_j) == 1:
                        yield self.data[i][j]
    def find(self,el):
        for i in range(3):
            for j in range(3):
                if self.data[i][j] == el:
                    return (i,j)

    def clone(self):
        o=Board([ list(row) for row in self.data ], self.count)
        print(o)
        return o

    def apply(self,move):
        i,j = self.find(move)
        ni,nj = self.find(None)
        self.swap(i,j,ni,nj)
        self.count += 1

    def c_apply(self,move):
        other=self.clone()
        other.apply( move )
        return other

    def swap(self, i,j,oi,oj):
        tmp = self.data[i][j]
        self.data[i][j] = self.data[oi][oj]
        self.data[oi][oj] = tmp
    def __str__(self):
        s = ''
        for l in self.data:
            for el in l:
                s += str(el) + ' ' if el != None else '  '
            s += '\n'
        return s
    def __lt__(self,other):
        return self.count < other.count
    def __le__(self,other):
        return self.count <= other.count
    def __gt__(self,other):
        return self.count > other.count
    def __ge__(self,other):
        return self.count >= other.count
    def __eq__(self,other):
        return self.count == other.count

    def neighbors(self):
        for m in self.moves():
            yield self.c_apply(m)

def solve(board, target):
    visited = []
    current = [ board ]
    while len(current) > 0 and current[0].data != target:
        current.sort()
        curr = current.pop()
        visited.append(curr.data)
        ns = [ neighbor for neighbor in curr.neighbors() if neighbor.data not in visited ]
        print("ns:")
        for n in ns:
            print(n)
        print(ns)
    if len(current) > 0:
        return current[0]
    return None

if __name__ == '__main__':
    print("main")
    a=Board([[1,2,3],[4,5,6],[7,8,None]])
    b=Board([[1,3,2],[4,5,6],[7,8,None]])
    print(a,b)
    print()
    print(solve(b,a))

