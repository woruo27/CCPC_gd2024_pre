import os
import random
import math
import numpy as np

datapath = os.path.dirname(__file__)
probpath = os.path.dirname(datapath)

np.random.seed(1888)
random.seed(1888)

MAXN = int(3e5)
MAXV = int(1e9)
NCASE = 0

def printcase(lines: list[tuple], flip: bool):
	assert len(lines) <= MAXN
	global NCASE
	NCASE += 1
	with open(str(NCASE) + ".in", "w") as f:
		f.write("%d\n" % len(lines))
		random.shuffle(lines)
		for x1, y1, x2, y2 in lines:
			if flip:
				y1, x1, y2, x2 = x1, y1, x2, y2
			f.write("%d %d %d %d\n" % (x1, y1, x2, y2))
	os.system("std.exe < %d.in > %d.ans" % (NCASE, NCASE))
	print("Case %d Complete." % NCASE)

def zero(flip: bool):
	lines = []
	xs = random.sample(range(-MAXV, MAXV + 1), k = MAXN)
	for x in xs:
		y1, y2 = random.sample(range(-MAXV, MAXV), k=2)
		while y1 == y2:
			y1, y2 = random.randint(-MAXV, MAXV), random.randint(-MAXV, MAXV)
		lines.append((x, min(y1, y2), x, max(y1, y2)))
	printcase(lines, flip)

def largestAns():
	printcase([(i, -MAXV, i, MAXV) for i in range(MAXN // 2)] + [(-MAXV, i, MAXV, i) for i in range(MAXN // 2)], 0)

def strong():
	lines = []
	nhor, ncol = random.randint(MAXN // 3, MAXN // 2), random.randint(MAXN // 3, MAXN // 2)
	split = random.randint(0, 1000)
	useless = random.randint(0, 20)
	med = MAXN - nhor - ncol - split - useless
	
	interv = [random.randint(1, MAXV // MAXN // 2) * 2 for _ in range(random.randint(2, 5))]
	def genindex(num: int):
		indices = [0]
		pre = random.choice(interv)
		change_prob = random.choice([0, 1e-4, 1e-3, 1e-2, 3e-2, 0.1, 0.3, 1])
		while len(indices) < num:
			if random.random() < change_prob:
				pre = random.choice(interv)
			indices.append(indices[-1] + pre)
		start = random.randint(-MAXV, MAXV - indices[-1])
		indices = [x + start for x in indices]
		return indices
	xindex, yindex = genindex(ncol), genindex(nhor)
	def gentwoindex(indexs: list):
		y1, y2 = random.sample(range(indexs[0], indexs[-1] + 1), k=2)
		if random.random() < 0.99:
			y1, y2 = random.randint(indexs[0], indexs[MAXN // 10]), random.randint(indexs[-MAXN // 10], indexs[-1])
		return min(y1, y2), max(y1, y2)

	for x in xindex:
		y1, y2 = gentwoindex(yindex)
		lines.append((x, y1, x, y2))
	for y in yindex:
		x1, x2 = gentwoindex(xindex)
		lines.append((x1, y, x2, y))

	xmed = [(xindex[i] + xindex[i + 1]) // 2 for i in range(len(xindex) - 1)]
	ymed = [(yindex[i] + yindex[i + 1]) // 2 for i in range(len(yindex) - 1)]
	random.shuffle(xmed)
	random.shuffle(ymed)
	impindex = set(xindex + yindex + xmed + ymed)

	for _ in range(med):
		if random.random() < 0.5:
			# col
			x = xmed[-1]
			y1, y2 = gentwoindex(yindex)
			lines.append((x, y1, x, y2))
			del xmed[-1]
		else:
			# hor
			y = ymed[-1]
			x1, x2 = gentwoindex(xindex)
			lines.append((x1, y, x2, y))
			del ymed[-1]
	
	for _ in range(useless):
		dir = random.random() < 0.5
		samplemethod = random.random() < 0.5
		def sample():
			if samplemethod:
				return random.sample(range(-MAXV, MAXV), k=3)
			else:
				if dir:
					x = random.randint(xindex[0], xindex[-1])
					y, z = random.sample(range(yindex[0], yindex[-1]), k=2)
				else:
					x = random.randint(yindex[0], yindex[-1])
					y, z = random.sample(range(xindex[0], xindex[-1]), k=2)
				return x, y, z

		x, y, z = sample()
		while x in impindex or y in impindex or z in impindex:
			x, y, z = sample()
		impindex.add(x)
		impindex.add(y)
		impindex.add(z)
		y, z = min(y, z), max(y, z)
		lines.append((x, y, x, z) if dir else (y, x, z, x))
	
	for _ in range(split):
		index = random.randint(0, len(lines) - 1)
		while lines[index][3] + lines[index][2] - lines[index][1] - lines[index][0] <= 2:
			index = random.randint(0, len(lines) - 1)
		x1, y1, x2, y2 = lines[index]
		if x1 < x2:
			nx2, nx1 = random.sample(range(x1 + 1, x2), k=2)
			lines.append((x1, y1, min(nx1, nx2), y2))
			lines.append((max(nx1, nx2), y1, x2, y2))
		else:
			ny1, ny2 = random.sample(range(y1 + 1, y2), k=2)
			lines.append((x1, y1, x2, min(ny1, ny2)))
			lines.append((x1, max(ny1, ny2), x2, y2))
		del lines[index]

	printcase(lines, random.randint(0, 1))

def rungen():
	zero(False)
	zero(True)
	largestAns()
	for _ in range(10):
		strong()

print("--- compile std ---")
os.system("g++ -o std ../psj/std.cpp -O2 -std=c++14")

print("--- start data generation ---")
rungen()
