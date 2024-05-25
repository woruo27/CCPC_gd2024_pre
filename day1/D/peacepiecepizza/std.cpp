#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define BASE 3054109
#define MOD 20211007
#define ESAB 15070229
#define CASE 3356263
#define NOD 435443857
#define ESAC 179335228
const int w[] = {
	0x45, 0x71, 0x43, 0x1a, 0x7a, 0xc0, 0xea, 0x57, 0xc1, 0x18, 0x8d, 0x79, 0x2d, 0xce, 0x29, 0xf4
}, m[10] = {
	0xa6, 0x8f, 0x44, 0xd1, 0x55, 0x7c, 0x30, 0x13, 0xb0, 0x21
};
struct HashVal {
	int x1, x2;
	inline bool operator == (const HashVal &other) const {
		return x1 == other.x1 && x2 == other.x2;
	}
	void pr() const { fprintf(stderr, "(%d, %d)\n", x1, x2); }
} a[200007], r[200007];
struct HashFun {
	int a1, b1, a2, b2;
	inline HashFun operator * (const HashFun &f) const {
		return (HashFun) {
			1ll * a1 * f.a1 % MOD,
			(b1 + 1ll * a1 * f.b1) % MOD,
			1ll * a2 * f.a2 % NOD,
			(b2 + 1ll * a2 * f.b2) % NOD
		};
	}
	inline HashVal operator () (const HashVal &val) const {
		return (HashVal) {
			(1ll * a1 * val.x1 + b1) % MOD,
			(1ll * a2 * val.x2 + b2) % NOD
		};
	}
	void pr() const { fprintf(stderr, "f(x) = (%d x + %d, %d x + %d)\n", a1, b1, a2, b2); }
} digit[18], tigid[18], d[200007], dinv[200007];
const HashFun I = (HashFun){1, 0, 1, 0};
struct Edge {
	HashFun f, inv;
	int to, next;
} e[400005];
struct HashNode {
	int val, cnt, aid, next;
} hn[200007];
struct Query {
	HashVal val;
	int qid, ent, hnid;
} curq[200007];
struct Modify {
	HashVal val;
	int aid;
};
vector<int> dial[200007], vq, modified;
vector<Modify> modify;
int htab[MOD], head[200007], isLeaf[200007], del[200007], vis[200007], vis2[200007], siz[200007], f[200007];
int ans[200007], aid[200007], en = 1, entid, vcnt, hntot, qtot, foundLeaf;
void insert(const Modify &m) {
	for (int i = htab[m.val.x1]; i; i = hn[i].next) {
		if (hn[i].val == m.val.x2) {
			++hn[i].cnt;
			hn[i].aid = m.aid;
			return ;
		}
	}
	hn[++hntot] = (HashNode){m.val.x2, 1, m.aid, htab[m.val.x1]};
	if (htab[m.val.x1] == 0) modified.push_back(m.val.x1);
	htab[m.val.x1] = hntot;
	return ;
}
int locate(const HashVal &v) {
	int i;
	for (i = htab[v.x1]; i; i = hn[i].next) {
		if (hn[i].val == v.x2) {
			break;
		}
	}
	return i;
}
inline int findByIndex(int id) {
	if (curq[id].hnid) return curq[id].hnid;
	return curq[id].hnid = locate(curq[id].val);
}
inline void updateAns(int id) {
	int hnid = findByIndex(id);
	if (hnid) {
		if ((ans[curq[id].qid] += hn[hnid].cnt) == 1 && vis2[hn[hnid].aid] != curq[id].ent) {
			aid[curq[id].qid] = hn[hnid].aid;
		}
	}
	return ;
}
inline void downdateAns(int id) {
	ans[curq[id].qid] -= hn[findByIndex(id)].cnt;		// Assume hn[0].cnt == 0
	return ;
}
void dp(int o) {
	int i, to;
	vis[o] = siz[o] = 1;
	f[o] = vis2[o] = 0;
	vq.push_back(o);
	if (isLeaf[o]) foundLeaf = 1;
	for (i = head[o]; i; i = e[i].next) {
		if (del[to = e[i].to] == 0 && vis[to] == 0) {
			dp(to);
			siz[o] += siz[to];
			cmax(f[o], siz[to]);
		}
	}
	return ;
}
int getG(int x) {
	int g, mins = 999999999, tmp;
	dp(x);
	for (int v : vq) {
		tmp = dmax(f[v], vq.size() - siz[v]);
		if (tmp < mins) {
			g = v;
			mins = tmp;
		}
	}
	return g;
}
void dfs(int o, HashFun f, HashFun inv) {
	vis[o] = 0;
	vis2[o] = entid;
	if (isLeaf[o]) {
		modify.push_back((Modify){f(a[o]), o});
		for (int qid : dial[o]) {
			curq[++qtot] = (Query){inv(r[qid]), qid, entid, 0};
		}
		return ;
	}
	int i, to;
	for (i = head[o]; i; i = e[i].next) {
		if (del[to = e[i].to] == 0 && vis2[to] == 0) {
			dfs(to, f * e[i].f, inv * e[i ^ 1].inv);
		}
	}
	return ;
}
void dc(int x) {
	int i, j, g = getG(x), to, qnow = 0;
	if (foundLeaf == 0 || vq.size() <= 2) {
		vq.clear();
		return ;
	}
	vector<int> entries;
	del[g] = 1;
	for (i = head[g]; i; i = e[i].next) {
		if (del[to = e[i].to] == 0) {
			entries.push_back(entid = to);
			modify.clear();
			dfs(to, e[i].f, e[i ^ 1].inv);
			for (j = qnow + 1; j <= qtot; ++j) updateAns(j);
			for (Modify m : modify) insert(m);
			for (j = qnow + 1; j <= qtot; ++j) downdateAns(j);
			qnow = qtot;
		}
	}
	
	for (j = 1; j <= qtot; ++j) updateAns(j);

	// Clear
	foundLeaf = hntot = qtot = 0;
	for (int x : modified) htab[x] = 0;
	modified.clear();
	vq.clear();

	// Subproblems
	for (int ent : entries) {
		dc(ent);
	}

	return ;
}
void compose(char * begin, const char *end, HashFun &f, HashFun &inv) {
	int tmp;
	f = I;
	inv = I;
	while (begin != end) {
		f = f * digit[tmp = *begin - '0'];
		inv = tigid[tmp] * inv;
		++begin;
	}
	return ;
}
int fastin() {
	int i; char ch;
	while (ch = getchar(), ch < '0' || ch > '9');
	i = ch - '0';
	while (ch = getchar(), ch >= '0' && ch <= '9') i = i * 10 + (ch - '0');
	return i;
}
char buf[10000008];
int main() {
	int n, q, i, j, v, fa, len;
	char *s, *t;
	HashFun b, bi, c, ci;
	for (i = 0; i <= 9; ++i) {
		digit[i] = (HashFun) {BASE, w[i], CASE, m[i]};
		tigid[i] = (HashFun) {ESAB, 1ll * (MOD - ESAB) * w[i] % MOD, ESAC, 1ll * (NOD - ESAC) * m[i] % NOD};
	}
	n = fastin(); q = fastin();
	for (i = 1; i <= n; ++i) {
		fa = fastin(); isLeaf[i] = fastin();
		scanf("%s", buf);
		if (isLeaf[i]) {
			for (j = strlen(buf) - 1; j >= 0; --j) {
				a[i] = digit[buf[j] - '0'](a[i]);
			}
			e[++en] = (Edge){I, I, fa, head[i]};
			head[i] = en;
			e[++en] = (Edge){d[fa], dinv[fa], i, head[fa]};
			head[fa] = en;
		}
		else {
			t = strchr(buf, '/');
			compose(buf, t, b, bi);
			s = t + 1;
			t = strchr(s, '/');
			compose(s, t, c, ci);
			compose(t + 1, t + strlen(t), d[i], dinv[i]);
			if (fa) {
				e[++en] = (Edge){b, bi, fa, head[i]};
				head[i] = en;
				e[++en] = (Edge){d[fa] * c * dinv[i], d[i] * ci * dinv[fa], i, head[fa]};
				head[fa] = en;
			}
		}
	}
	for (i = 1; i <= q; ++i) {
		v = fastin();
		scanf("%s", buf);
		dial[v].push_back(i);
		for (j = strlen(buf) - 1; j >= 0; --j) {
			r[i] = digit[buf[j] - '0'](r[i]);
		}
	}
	dc(1);

	for (i = 1; i <= q; ++i) {
		if (ans[i] == 1) printf("1 %d\n", aid[i]);
		else printf("0 %d\n", ans[i]);
	}

	return 0;
}