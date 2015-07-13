#!/bin/python2

'''
Relevant commands:

python2 gen_audi.py -a binary.aif -d 7
python2 parse_audi.py -a binary.aif -d binary.dot
dot -Tps binary.dot -o binary.ps
epstopdf binary.ps
'''

import sys
import argparse
import networkx as nx
import matplotlib.pyplot as plt

# [y]arg[hhhhhhhh]
ap = argparse.ArgumentParser()
ap.add_argument("-a", "--audi", required = True, help = "Name of the .aif file")
ap.add_argument("-d", "--dot", required = True, help = "Name of the .dot file")
args = vars(ap.parse_args())

# the necessary data structures
line = []
inputs = []
outputs = []
regs = []
ops = []
go = True
G = nx.DiGraph()

# parsing file
audi      = open(args["audi"], 'r')
inputs    = audi.readline().strip().split(' ')[1:]
outputs   = audi.readline().strip().split(' ')[1:]
regs      = audi.readline().strip().split(' ')[1:]
bit_width = int(inputs[1])                                 # assumming a globally uniform bit width
inputs    = filter(lambda a: a != str(bit_width), inputs)  # will cause problems if bit width
outputs   = filter(lambda a: a != str(bit_width), outputs) # shares the same value as an op_input,
regs      = filter(lambda a: a != str(bit_width), regs)    # op_output, or register name

while go:
	line = audi.readline().strip().split(' ')
	if len(line) > 2:
		line = filter(lambda a: a != str(bit_width), line)
		line[0] = line[0][2:]
		ops.append(line)
		# print line
	go = len(line) > 2

# generating the sequencing graph (not locked to time steps)
for a in inputs:
	G.add_node(a)   # (('in',a))
for b in outputs:
	G.add_node(b)   # (('out',b))
for c in regs:
	G.add_node(c)   # (('reg',c))
for d in ops:
	G.add_node(d[0])   # (('op',d[0]))

for a in ops:
	G.add_edge(a[2], a[0])
	G.add_edge(a[3], a[0])
	G.add_edge(a[0], a[4])

# call upon the ancient lords of the underworld
# remember the term "topological sort" and "directed acyclic graph"
nx.draw_graphviz(G)
# plt.savefig('matplotlib.png')
nx.write_dot(G,args["dot"])
