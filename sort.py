#!/usr/bin/python
# coding=utf-8
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

    return sorted(sequences, key = operator.attrgetter('lenght', 'weight'))

if __name__ == '__main__':
    lst = []
    if len(sys.argv) > 1:
        lst = sortfile(sys.argv[1])
    else:
        lst = sortfile("out.txt")
    
    prev_len = 0
    prev_w = 0
    print 'Длина, Вес, m0'
    for seq in lst:
        if (prev_len != seq.lenght) or (prev_w != seq.weight):
            print seq.lenght, ',', seq.weight, ',', seq.zero_count, ',', ', '.join(seq.sequence)
        else:
            print seq.lenght, ',', seq.weight, ', ,', ', '.join(seq.sequence)
        prev_len = seq.lenght
        prev_w = seq.weight 
