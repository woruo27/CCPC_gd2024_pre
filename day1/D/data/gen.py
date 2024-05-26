import random
import os
import copy
import datetime
import numpy as np
import tqdm

TASK_NUM = 1

N_LIMIT = 100000
Q_LIMIT = 100000
LEN_LIMIT = 3000000
ALPHABET = "0123456789"

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write("[{}] {}\n".format(datetime.datetime.now(), string))

class Tree:
	def __init__(self):
		self.fa = [0]
		self.depth = [0]

	def addNodeUnder(self, fa):
		self.fa.append(fa)
		self.depth.append(self.depth[fa] + 1)
		return
	
	def finalize(self, genPhone, **extra_param):
		self.n = len(self.fa) - 1
		self.isLeaf = [1] * (self.n + 1)
		for i in range(1, self.n + 1):
			self.isLeaf[self.fa[i]] = 0
		numbers = genPhone(self, **extra_param)
		self.nodes = list(zip(self.fa, self.isLeaf, numbers))
		self.expfa = np.zeros((18, self.n + 1), dtype = np.int32)
		self.expfa[0, :] = self.fa
		for i in range(1, 18):
			for j in range(1, self.n + 1):
				self.expfa[i, j] = self.expfa[i - 1, self.expfa[i - 1, j]]
		self.bfa = [0]
		self.cfa = [0]
		for i in range(1, self.n + 1):
			if self.isLeaf[i]:
				assert isinstance(numbers[i], str)
			else:
				assert isinstance(numbers[i], tuple) and len(numbers[i]) == 3
				assert isinstance(numbers[i][0], str) and isinstance(numbers[i][1], str) and isinstance(numbers[i][2], str)
			self.bfa.append(self.fa[i] if numbers[self.fa[i]][0] else self.bfa[self.fa[i]])
			self.cfa.append(self.fa[i] if numbers[self.fa[i]][1] else self.cfa[self.fa[i]])
		return

	def LCA(self, u, v):
		if self.depth[u] > self.depth[v]:
			u, v = v, u
		if self.depth[u] < self.depth[v]:
			i = 0
			diff = self.depth[v] - self.depth[u]
			while diff:
				if diff & (2 ** i):
					v = self.expfa[i, v]
					diff ^= 2 ** i
				i += 1
		if u == v:
			return u
		for i in range(17, -1, -1):
			if self.expfa[i, u] != self.expfa[i, v]:
				u = self.expfa[i, u]
				v = self.expfa[i, v]
		return self.fa[u]
	
	def query(self, u, v):
		x = self.LCA(u, v)
		left = ""
		right = self.nodes[v][2]
		u = self.bfa[u]
		while self.depth[u] > self.depth[x]:
			left = left + self.nodes[u][2][0]
			u = self.bfa[u]
		v = self.cfa[v]
		while self.depth[v] > self.depth[x]:
			right = self.nodes[v][2][1] + right
			v = self.cfa[v]
		return left + self.nodes[x][2][2] + right

def genRandNumbers(tree: Tree, total_length = LEN_LIMIT, alphabet = ALPHABET, p = None, nonempty_inner = False, p_multi = None, **extra_param):
	rng = np.random.default_rng()

	if nonempty_inner:
		lengths = np.ones(tree.n + 1, dtype = np.int32)
		lengths[0] = 0
	else:
		lengths = np.array(tree.isLeaf)
	if p_multi is None:
		p_multi = np.ones(tree.n + 1) / (tree.n)
		p_multi[0] = 0
	elif callable(p_multi):
		p_multi = p_multi(tree)
	lengths += rng.multinomial(total_length - lengths.sum(), p_multi)
	
	numbers = []
	for i, l in enumerate(lengths):
		if tree.isLeaf[i]:
			numbers.append("".join(rng.choice(list(alphabet), l, p = p)))
		else:
			cat = "".join(rng.choice(list(alphabet), l, p = p))
			x, y = rng.integers(l, size = 2, endpoint = True)
			if x > y:
				x, y = y, x
			numbers.append((cat[:x], cat[x : y], cat[y:]))
	
	return numbers

def genUnbalancedNumbers(tree: Tree, total_length = LEN_LIMIT, alphabet = ALPHABET, p = None, nonempty_inner = False, p_multi = None, frac_inner = 0.5, **extra_param):
	rng = np.random.default_rng()

	if nonempty_inner:
		lengths = np.ones(tree.n + 1, dtype = np.int32)
		lengths[0] = 0
	else:
		lengths = np.array(tree.isLeaf)
	if p_multi is None:
		p_multi = np.ones(tree.n + 1) / (tree.n)
		p_multi[0] = 0
	elif callable(p_multi):
		p_multi = p_multi(tree)
	p_leaf = np.where(tree.isLeaf, p_multi, 0)
	p_leaf /= p_leaf.sum()
	p_inner = np.where(tree.isLeaf, 0, p_multi)
	p_inner[0] = 0
	p_inner /= p_inner.sum()
	total_inner = int(total_length * frac_inner)
	nleaves = sum(tree.isLeaf)
	lengths += rng.multinomial(total_inner - (tree.n - nleaves if nonempty_inner else 0), p_multi)
	lengths += rng.multinomial(total_length - total_inner - nleaves, p_leaf)
	
	numbers = []
	for i, l in enumerate(lengths):
		if tree.isLeaf[i]:
			numbers.append("".join(rng.choice(list(alphabet), l, p = p)))
		else:
			cat = "".join(rng.choice(list(alphabet), l, p = p))
			x, y = rng.integers(l, size = 2, endpoint = True)
			if x > y:
				x, y = y, x
			numbers.append((cat[:x], cat[x : y], cat[y:]))
	
	return numbers

def getRandInnerNumber(length, alphabet = ALPHABET, p = None):
	rng = np.random.default_rng()
	cat = "".join(rng.choice(list(alphabet), length, p = p))
	x, y = rng.integers(length, size = 2, endpoint = True)
	if x > y:
		x, y = y, x
	return (cat[:x], cat[x : y], cat[y:])

def genNumberByDepth(tree: Tree, total_length = LEN_LIMIT, alphabet = ALPHABET, p = None, frac_inner = 0.7, n_alter = 2, prob_mutant = 0.01, **extra_param):
	rng = np.random.default_rng()

	max_depth = max(tree.depth)
	depth_cnt = [0] * (max_depth + 1)
	for i in range(1, tree.n + 1):
		if not tree.isLeaf[i]:
			depth_cnt[tree.depth[i]] += 1
	
	reserved = 0
	lengths = [0] * (max_depth + 1)
	try_cnt = 0
	while reserved <= int(total_length * frac_inner) and try_cnt < 5:
		d = rng.integers(1, max_depth, endpoint = True)
		if reserved + depth_cnt[d] <= int(total_length * frac_inner):
			lengths[d] += 1
			reserved += depth_cnt[d]
		else:
			try_cnt += 1
	
	alternatives = [[getRandInnerNumber(lengths[d], alphabet, p) for _ in range(n_alter)] for d in range(max_depth + 1)]

	numbers = [("", "", "")]
	p_leaf = np.array(tree.isLeaf)
	nleaves = p_leaf.sum()
	p_leaf = p_leaf / nleaves
	leaf_length = rng.multinomial(total_length - reserved - nleaves, p_leaf) + 1
	for i in range(1, tree.n + 1):
		if tree.isLeaf[i]:
			numbers.append("".join(rng.choice(list(alphabet), leaf_length[i], p = p)))
		else:
			if rng.random() < prob_mutant:
				num = list(alternatives[tree.depth[i]][rng.integers(n_alter)])
				x = rng.integers(lengths[tree.depth[i]])
				if x < len(num[0]):
					num[0] = num[0][:x] + rng.choice(alphabet, p = p) + num[0][x + 1:]
				elif x < len(num[0]) + len(num[1]):
					x -= len(num[0])
					num[1] = num[1][:x] + rng.choice(alphabet, p = p) + num[1][x + 1:]
				else:
					x -= len(num[0]) + len(num[1])
					num[2] = num[2][:x] + rng.choice(alphabet, p = p) + num[2][x + 1:]
				numbers.append(tuple(num))
			else:
				numbers.append(alternatives[tree.depth[i]][rng.integers(n_alter)])
	
	return numbers

def genLeafyNumbers(tree: Tree, total_length = LEN_LIMIT, alphabet = ALPHABET, p = None, p_multi = None, **extra_param):
	rng = np.random.default_rng()

	lengths = np.array(tree.isLeaf)
	if p_multi is None:
		p_multi = np.ones(tree.n + 1) / (tree.n)
		p_multi[0] = 0
	elif callable(p_multi):
		p_multi = p_multi(tree)
	p_leaf = np.where(tree.isLeaf, p_multi, 0)
	lengths += rng.multinomial(total_length - lengths.sum(), p_leaf)
	
	numbers = []
	for i, l in enumerate(lengths):
		if tree.isLeaf[i]:
			numbers.append("".join(rng.choice(list(alphabet), l, p = p)))
		else:
			cat = "".join(rng.choice(list(alphabet), l, p = p))
			x, y = rng.integers(l, size = 2, endpoint = True)
			if x > y:
				x, y = y, x
			numbers.append((cat[:x], cat[x : y], cat[y:]))
	
	return numbers

def genRandTree(n, genPhone = genRandNumbers, **extra_param):
	rng = np.random.default_rng()
	
	tree = Tree()
	tree.addNodeUnder(0)
	for i in range(2, n + 1):
		tree.addNodeUnder(rng.integers(1, i))
	
	tree.finalize(genPhone, **extra_param)

	return tree

def genChain(n, genPhone = genRandNumbers, **extra_param):
	tree = Tree()
	for i in range(n):
		tree.addNodeUnder(i)
	
	tree.finalize(genPhone, **extra_param)

	return tree

def genDoubleChain(n, genPhone = genRandNumbers, **extra_param):
	rng = np.random.default_rng()

	tree = Tree()
	tree.addNodeUnder(0)
	tree.addNodeUnder(1)
	tree.addNodeUnder(1)
	leaves = [2, 3]
	for i in range(4, n + 1):
		j = rng.integers(2)
		tree.addNodeUnder(leaves[j])
		leaves[j] = i
	
	tree.finalize(genPhone, **extra_param)
	return tree

def genShortTree(n, genPhone = genRandNumbers, maxdepth = 5, nviolate = 0, **extra_param):
	rng = np.random.default_rng()

	tree = Tree()
	tree.addNodeUnder(0)
	depth = [0, 0]
	violcnt = 0
	available = [1]
	for i in range(2, n + 1):
		fa = available[rng.integers(len(available))]
		tree.addNodeUnder(fa)
		d = depth[fa] + 1
		depth.append(d)
		if d == maxdepth:
			if violcnt < nviolate:
				violcnt += 1
				available.append(fa)
		else:
			available.append(fa)

	tree.finalize(genPhone, **extra_param)
	return tree

def genTallTree(n, genPhone = genRandNumbers, maxdist = 10, **extra_param):
	rng = np.random.default_rng()
	
	tree = Tree()
	tree.addNodeUnder(0)
	for i in range(2, n + 1):
		tree.addNodeUnder(rng.integers(max(1, i - maxdist), i))

	tree.finalize(genPhone, **extra_param)
	return tree

def genRandValidQuery(tree: Tree, **extra_param):
	rng = np.random.default_rng()
	queries = []
	total = 0
	leaves = [i for i in range(1, tree.n + 1) if tree.isLeaf[i]]
	while total < LEN_LIMIT and len(queries) < Q_LIMIT:
		u, v = rng.choice(leaves, 2)
		s = tree.query(u, v)
		if total + len(s) > LEN_LIMIT:
			queries.append((u, "".join(rng.choice(list(ALPHABET), LEN_LIMIT - total))))
			break
		queries.append((u, s))
		total += len(s)

	return queries

def genRandUniformQuery(tree: Tree, q = Q_LIMIT, alphabet = ALPHABET, p = None, **extra_param):
	rng = np.random.default_rng()
	queries = []
	leaves = [i for i in range(1, tree.n + 1) if tree.isLeaf[i]]
	lengths = rng.multinomial(LEN_LIMIT, np.ones(q) / q)
	for l in lengths:
		queries.append((rng.choice(leaves), "".join(rng.choice(list(alphabet), l, p = p))))

	return queries

def genRandMixedQuery(tree: Tree, q = Q_LIMIT, alphabet = ALPHABET, p = None, frac_valid = 0.8, **extra_param):
	rng = np.random.default_rng()
	valid = genRandValidQuery(tree)
	queries = [""] * q
	total_length = 0
	cnt = 0
	oldid = rng.permutation(len(valid))
	newid = rng.permutation(q)
	for i in oldid:
		if len(valid[i][1]) + total_length <= int(LEN_LIMIT * frac_valid):
			queries[newid[cnt]] = valid[i]
			total_length += len(valid[i][1])
			cnt += 1
	
	p_multi = np.array([0 if isinstance(query, tuple) else 1 for query in queries])
	print(p_multi.sum())
	leaves = [i for i in range(1, tree.n + 1) if tree.isLeaf[i]]
	# lengths = (rng.multinomial(LEN_LIMIT - total_length - p_multi.sum(), p_multi / p_multi.sum()) + 1) + p_multi
	lengths = p_multi
	lengths[rng.choice([i for i, query in enumerate(queries) if not isinstance(query, tuple)], LEN_LIMIT - total_length - p_multi.sum())] += 1
	buf = "".join(rng.choice(list(alphabet), LEN_LIMIT - total_length - p_multi.sum(), p = p))
	rand_leaves = rng.choice(leaves, q)
	sliced = 0
	for i, l in enumerate(lengths):
		if l:
			if i % 100 == 0:
				print(i, flush = True)
			queries[i] = (rand_leaves[i], buf[sliced : sliced + l])
			sliced += l

	return queries

def genTestcase(filename, n, genTree = genRandTree, genQuery = genRandValidQuery, **extra_param):
	log(f"Generating input for case {filename}, params: {n = }, {genTree.__name__}, {genQuery.__name__}, {extra_param = }")
	# assert ..., "Parameters invalid!"
	assert 1 <= n <= N_LIMIT
	tree = genTree(n, **extra_param)
	queries = genQuery(tree, **extra_param)
	assert 1 <= len(queries) <= Q_LIMIT
	
	with open(f"{filename}.in", "w") as f:
		print(n, len(queries), file = f)
		for i in range(1, n + 1):
			fa, isLeaf, s = tree.nodes[i]
			if isLeaf:
				print(fa, isLeaf, s, file = f)
			else:
				print(fa, isLeaf, "/".join(s), file = f)
		for q in queries:
			print(*q, file = f)
	
	log(f"Generating output for case {filename}")
	# os.system('(time ../ShinyRacers/std < {}.in > {}.ans) 2>> gen.log'.format(filename, filename))
	os.system(f'(time {os.path.join("..", "peacepiecepizza", "std")} < {filename}.in > {filename}.ans) 2>> gen.log')		# Linux
	# os.system(f'({os.path.join("..", "peacepiecepizza", "std")} < {filename}.in > {filename}.ans) 2>> gen.log')				# Windows

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, n, **extra_param):
		self.cnt += 1
		if self.cnt <= 57 or "genQuery" not in extra_param or extra_param["genQuery"] != genRandMixedQuery:
			log(f"[Warning] Skip teatcase {self.cnt}")
			return
		genTestcase(f"{self.prefix}{self.cnt}", n, **extra_param)
	
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

	testcase.gen(N_LIMIT, genTree = genChain)
	for genQuery in (genRandValidQuery, genRandUniformQuery, genRandMixedQuery):
		testcase.gen(N_LIMIT - rng.integers(10), genTree = genDoubleChain, genQuery = genQuery)
	
	for genQuery in (genRandValidQuery, genRandUniformQuery, genRandMixedQuery):
		for genTree in (genRandTree, genTallTree):
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genTree, genQuery = genQuery)
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genTree, genQuery = genQuery, alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2])
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genTree, genPhone = genUnbalancedNumbers, genQuery = genQuery,
				alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2])
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genTree, genPhone = genNumberByDepth, genQuery = genQuery,
				alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2])
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genTree, genPhone = genLeafyNumbers, genQuery = genQuery,
				alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2])

	for genQuery in (genRandValidQuery, genRandUniformQuery, genRandMixedQuery):
		for nviolate in (0, 2):
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genShortTree, genQuery = genQuery, alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2], nviolate = nviolate)
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genShortTree, genPhone = genUnbalancedNumbers, genQuery = genQuery,
				alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2], nviolate = nviolate)
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genShortTree, genPhone = genNumberByDepth, genQuery = genQuery, nviolate = nviolate)
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genShortTree, genPhone = genNumberByDepth, genQuery = genQuery,
				alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2], nviolate = nviolate)
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genShortTree, genPhone = genLeafyNumbers, genQuery = genQuery,
				alphabet = rng.choice(list(ALPHABET), 2, replace = False), p = [0.8, 0.2], nviolate = nviolate)
	
	for genQuery in (genRandValidQuery, genRandUniformQuery, genRandMixedQuery):
		for genTree in (genRandTree, genTallTree):
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genTree, genPhone = genUnbalancedNumbers, genQuery = genQuery,
				alphabet = rng.choice(list(ALPHABET), 1), frac_inner = 0.1)
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genTree, genPhone = genLeafyNumbers, genQuery = genQuery,
				alphabet = rng.choice(list(ALPHABET), 1))
		for nviolate in (0, 2):
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genShortTree, genPhone = genUnbalancedNumbers, genQuery = genQuery,
				alphabet = rng.choice(list(ALPHABET), 1), nviolate = nviolate, frac_inner = 0.1)
			testcase.gen(N_LIMIT - rng.integers(10), genTree = genShortTree, genPhone = genLeafyNumbers, genQuery = genQuery,
				alphabet = rng.choice(list(ALPHABET), 1), nviolate = nviolate)
	# add testcases above		
	log("Subtask {} done. ({} - {})".format(i, pre + 1, testcase.cnt))
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")
