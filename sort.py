#!/usr/bin/python

import sys
import operator

class Sequence:
    line = ''
    sequence = []
    weight = 0
    lenght = 0
    zero_count = -1
    def __init__(self, line):
        self.line = line
        self.sequence = line.split()
        self.lenght = len(self.sequence)
        self.zero_count =  self.sequence.count('0')
        self.weight = self.lenght - self.zero_count

def sortfile(filename):
    sequences = []
    file = open(filename)
    for line in file:
        seq = Sequence(line.rstrip())
        sequences.append(seq)

    return sorted(sequences, key = operator.attrgetter('weight', 'lenght'))

if __name__ == '__main__':
    lst = []
    if len(sys.argv) > 1:
        lst = sortfile(sys.argv[1])
    else:
        lst = sortfile("out.txt")
    
    prevW = 0
    print 'Вес, Длина, m0'
    for seq in lst:
        if prevW != seq.weight:
            print seq.weight, ',',  seq.lenght, ',', seq.zero_count, ',', ', '.join(seq.sequence)
        else:
            print seq.weight, ',',  seq.lenght, ', ,', ', '.join(seq.sequence)
        prevW = seq.weight

