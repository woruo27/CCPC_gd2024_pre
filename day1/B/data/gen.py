import random
import os
import copy
import datetime
import numpy as np
import tqdm

TASK_NUM = 1

L_LIMIT = 3000000
CP_LIMIT = 2 ** 30 - 1
S_LIMIT = 3000000
ALPHABET = "abcdefghijklmnopqrstuvwxyz"

SAME_CORE = 0
RAND_CORE = 1
SLICE_CORE = 2

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write("[{}] {}\l".format(datetime.datetime.now(), string))

def getCP(**extra_param):
	rng = np.random.default_rng()
	while True:
		c, p = np.sort(rng.integers(2, CP_LIMIT, 2, endpoint = True))
		if c < p:
			break
	return c, p

def genSameChar(l, ch = "a", **extra_param):
	return [ch * (S_LIMIT // l)] * l

def genSameString(l, alphabet = ALPHABET, p = None, **extra_param):
	rng = np.random.default_rng()
	return ["".join(rng.choice(list(alphabet), (S_LIMIT // l), p = p))] * l

def genTriangle(l, mainc = "a", alterc = "b", **extra_param):
	s = []
	for i in range(1, l + 1):
		s.append(mainc * ((i - 1) // 2) + alterc + mainc * (i // 2))
	return s

def getRandPizza(num, length, alphabet = ALPHABET, p = None, **extra_param):
	rng = np.random.default_rng()
	return ["".join(rng.choice(list(alphabet), length, p = p)) for _ in range(num)]

def getRepeatingPizza(num, length, alphabet = ALPHABET, p = None, corelen = 5, coretype = SAME_CORE, max_repetition = 5, **extra_param):
	rng = np.random.default_rng()

	if coretype == SAME_CORE:
		cores = ["".join(rng.choice(list(alphabet), corelen, p = p))] * num
	elif coretype == RAND_CORE:
		cores = ["".join(rng.choice(list(alphabet), corelen, p = p)) for _ in range(num)]
	elif coretype == SLICE_CORE:
		cores = ["".join(rng.choice(list(alphabet), corelen, p = p))]
	else:
		raise ValueError(f"Unidentified {coretype = }")
	
	s = []
	for i in range(num):
		si = cores[i]
		while len(si) < length:
			si = str(rng.choice(list(alphabet), p = p)).join([si] * rng.integers(2, min(max_repetition, length // len(si) + 1), endpoint = True))
		if len(si) > length:
			start = rng.integers(len(si) - length, endpoint = True)
			s.append(si[start : start + length])
		else:
			s.append(si)
		if coretype == SLICE_CORE:
			j = rng.integers(i, endpoint = True)
			start = rng.integers(length - corelen, endpoint = True)
			cores.append(cores[j][start : start + corelen])
	return s

def genSlices(l, nmain = 10, mainlen = S_LIMIT // 20, alphabet = ALPHABET, p = None, getPizza = None, **extra_param):
	rng = np.random.default_rng()
	s = getPizza(nmain, mainlen, alphabet = alphabet, p = p, **extra_param)
	
	nminor = l - nmain
	minorlen = rng.multinomial(S_LIMIT - mainlen * nmain - nminor, np.ones(nminor) / (nminor)) + 1
	for x in minorlen:
		while True:
			leftlen = rng.integers(x, endpoint = True)
			u, v = rng.integers(len(s), size = 2)
			if len(s[u]) >= leftlen and len(s[v]) >= x - leftlen:
				break
		s.append(s[u][-leftlen:] + s[v][:x - leftlen] if leftlen else s[v][:x])

	return s

def genSlicedPizza(l, nmain = 10, mainlen = S_LIMIT // 20, alphabet = ALPHABET, p = None, p_new_slice = 0.5, minlen = 3, **extra_param):
	rng = np.random.default_rng()
	mainpizza = getRepeatingPizza(1, 2 * S_LIMIT, alphabet = alphabet, p = p, **extra_param)[0]
	s = []
	for i in range(nmain):
		start = rng.integers(len(mainpizza) - mainlen, endpoint = True)
		s.append(mainpizza[start : start + mainlen])
	
	nminor = l - nmain
	if nminor:
		minorlen = rng.multinomial(S_LIMIT - mainlen * nmain - minlen * nminor, np.ones(nminor) / (nminor)) + minlen
		for x in minorlen:
			if rng.random() < p_new_slice:
				start = rng.integers(len(mainpizza) - x, endpoint = True)
				s.append(mainpizza[start : start + x])
			else:
				while True:
					leftlen = rng.integers(x, endpoint = True)
					u, v = rng.integers(len(s), size = 2)
					if len(s[u]) >= leftlen and len(s[v]) >= x - leftlen:
						break
				s.append(s[u][-leftlen:] + s[v][:x - leftlen] if leftlen else s[v][:x])
	
	return s

def genTestcase(filename, gen, l, **extra_param):
	log(f"Generating input for case {filename}, params: {l = }, {gen.__name__}, {extra_param = }")
	# assert ..., "Parameters invalid!"
	assert 1 <= l <= L_LIMIT
	c, p = getCP()
	assert 2 <= c < p <= CP_LIMIT
	s = gen(l, **extra_param)
	assert sum(len(si) for si in s) <= S_LIMIT, f"{sum(len(si) for si in s)}"
	
	with open(f"{filename}.in", "w") as f:
		print(l, c, p, file = f)
		for si in s:
			print(si, file = f)
	
	log(f"Generating output for case {filename}")
	# os.system('(time ../ShinyRacers/std < {}.in > {}.ans) 2>> gen.log'.format(filename, filename))
	os.system(f'(time {os.path.join("..", "peacepiecepizza", "std")} < {filename}.in > {filename}.ans) 2>> gen.log')		# Linux
	# os.system(f'({os.path.join("..", "peacepiecepizza", "std")} < {filename}.in > {filename}.ans) 2>> gen.log')				# Windows

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, gen, l, **extra_param):
		self.cnt += 1
		genTestcase(f"{self.prefix}{self.cnt}", gen, l, **extra_param)
	
	def skip(self, cnt = 1):
		self.cnt += cnt

# os.system("rm gen.log")
testcase = Cases()
# precase = Cases("../pre/")
# sample = Cases("../down/")

for i in range(1, TASK_NUM + 1):
	log("Generating subtask {}".format(i))
	pre = testcase.cnt
	# pre_pre = precase.cnt
	# add testcases below
	rng = np.random.default_rng()

	'''
	testcase.gen(genTriangle, 2448)
	for l in (10, int(S_LIMIT ** 0.5), S_LIMIT // 20, S_LIMIT):
		testcase.gen(genSameChar, l, ch = ALPHABET[rng.integers(26)])
	for l in (10, int(S_LIMIT ** 0.5), S_LIMIT // 20, S_LIMIT):
		testcase.gen(genSameString, l)
	for l in (10, int(S_LIMIT ** 0.5), S_LIMIT // 20, S_LIMIT):
		testcase.gen(genSameString, l, alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.9, 0.1])

	for l in (100, S_LIMIT // 50, S_LIMIT // 20):
		testcase.gen(genSlices, l, getPizza = getRandPizza)
		testcase.gen(genSlices, l, getPizza = getRandPizza, alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.9, 0.1])
	
	for l in (100, S_LIMIT // 50, S_LIMIT // 20):
		for coretype in (SAME_CORE, RAND_CORE, SLICE_CORE):
			for max_repetition in (5, 250):
				testcase.gen(genSlices, l, getPizza = getRepeatingPizza, coretype = coretype, max_repetition = max_repetition)
				testcase.gen(genSlices, l, getPizza = getRepeatingPizza, coretype = coretype, max_repetition = max_repetition, alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2])

	'''
	testcase.skip(55)

	testcase.gen(genSlicedPizza, 40, nmain = 40, mainlen = S_LIMIT // 40, max_repetition = 30)
	testcase.gen(genSlicedPizza, 40, nmain = 40, mainlen = S_LIMIT // 40, alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2], max_repetition = 10)

	testcase.gen(genSlicedPizza, S_LIMIT // 30, max_repetition = 50)
	testcase.gen(genSlicedPizza, S_LIMIT // 30, alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2], p_new_slice = 0.8, max_repetition = 10)
	testcase.gen(genSlicedPizza, S_LIMIT // 30, alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2], p_new_slice = 0.2, max_repetition = 10)

				
	# add testcases above		
	log("Subtask {} done. ({} - {})".format(i, pre + 1, testcase.cnt))
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")
