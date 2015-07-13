#!/bin/python2
# python2 -i gen_audi.py -a binary.aif -d 4

import sys
import argparse
import random

# [y]arg[hhhhhhhh]
ap = argparse.ArgumentParser()
ap.add_argument("-a", "--audi", required = True, help = "Name of the AUDI file")
ap.add_argument("-d", "--depth", required = True, help = "Generated complete binary tree depth")
args = vars(ap.parse_args())

# the necessary data structures
line = []
bit_width = 8
inputs = ["inputs"]
outputs = ["outputs", 'o1', bit_width]
regs = ["regs"]
ops = []
nodes = pow(2,int(args["depth"]))

# generating file
audi = open(args["audi"], 'w')

for x in xrange(nodes/2, nodes):
	inputs.append('i' + str(x))
	inputs.append(bit_width)

for x in xrange(1, nodes/2):
	ops.append([])
	if x >= nodes/4 :
		ops[x-1].append('i' + str(x * 2))
		ops[x-1].append('i' + str(x * 2 + 1))
	else :
		ops[x-1].append('r' + str(x * 2 - 1))
		ops[x-1].append('r' + str(x * 2))
	if x != 1:
		ops[x-1].append('r' + str(x-1))
	else:
		ops[x-1].append('o' + str(x))
	if x != (nodes / 2) - 1: 
		regs.append('r' + str(x))
		regs.append(bit_width)

# comment out the following line for "pretty" .aif files
# random.shuffle(ops)
ops.reverse()

for x in xrange(1, nodes/2):
	ops[x-1].insert(0, 'op' + str(x))
	ops[x-1].insert(1, 'ADD')
	ops[x-1].insert(2, bit_width)

# writing stuff to a file
for item in inputs:
	audi.write("%s " % item)
audi.write("\n")

for item in outputs:
	audi.write("%s " % item)
audi.write("\n")

for item in regs:
	audi.write("%s " % item)
audi.write("\n")

for item in ops:
	for thingy in item:
		audi.write("%s " % thingy)
	audi.write("\n")
audi.write("end\n")

audi.close()

# print inputs
# print outputs
# print regs
# print ops
