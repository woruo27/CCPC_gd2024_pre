#include <cstdio>
#include <cstring>
using namespace std;
#define BASE 3054109
#define MOD 20211007
#define CASE 3356263
#define MAXLEN 1000008
const int w[] = {
	0xd5, 0x3f, 0xb8, 0xf5, 0xf8, 0xf9, 0xc8, 0x9a, 0x6e, 0xde, 0x24, 0x87, 0xab, 0x75, 0x31, 0xf7,
	0xc0, 0x17, 0x54, 0xb2, 0x6d, 0x79, 0x23, 0x3e, 0xc2, 0xc4, 0x46, 0xaf, 0x70, 0x19, 0x8c, 0x5b
};
const unsigned int m[26] = {
	0xfa, 0xea, 0x64, 0x97, 0x94, 0x3a, 0xd2, 0x33, 0x86, 0xdb, 0xcb, 0x48, 0x59, 0x92, 0xf1, 0x5e,
	0xa6, 0x8f, 0x44, 0xd1, 0x55, 0x7c, 0x30, 0x13, 0xb0, 0x21
};
struct Substr {
	unsigned long long h;
	char *start, *end;
	Substr *next;
	int val, cnt;
} sub[MAXLEN], *head[MOD];
char buf[MAXLEN << 1], *s[MAXLEN], *bptr = buf;
int cp[MAXLEN], len[MAXLEN], fail[MAXLEN], g[MAXLEN], stot;
void insert(char *op, char *ed, int key, unsigned long long h, int val) {
	fprintf(stderr, "%d %d %d %llu %d\n", op - buf, ed - buf, key, h, val); fflush(stderr);
	char *s1, *s2;
	for (Substr *p = head[key]; p != nullptr; p = p -> next) {
		if (h == p -> h && val == p -> val && p -> end - p -> start == ed - op) {
			for (s1 = op, s2 = p -> start; s1 != ed; ++s1, ++s2) {
				if (*s1 != *s2) break;
			}
			if (s1 == ed) {
				++(p -> cnt);
				return ;
			}
		}
	}
	sub[++stot] = (Substr){h, op, ed, head[key], val, 1};
	head[key] = sub + stot;
	return ;
}
int getVal(char *op, char *ed, int key, unsigned long long h) {
	char *s1, *s2;
	// fprintf(stderr, "%d %d %d %llu\n", op - buf, ed - buf, key, h); fflush(stderr);
	for (Substr *p = head[key]; p != nullptr; p = p -> next) {
		// fprintf(stderr, "%d %llu", p - sub, p -> h);
		if (h == p -> h && p -> end - p -> start == ed - op) {
			for (s1 = op, s2 = p -> start; s1 != ed; ++s1, ++s2) {
				if (*s1 != *s2) break;
			}
			if (s1 == ed) return p -> val;
		}
		// fprintf(stderr, "DO NOT MATCH\n");
	}
	return 0;
}
int main() {
	int l, c, p, i, j, k, maxlen = 0, ans = 0, powb;
	char ch;
	unsigned long long hash, powc;
	scanf("%d %d %d", &l, &c, &p);
	ans = 1ll * l * l % p;
	cp[0] = 1;
	for (i = 1; i <= l; ++i) {
		s[i] = bptr;
		scanf("%s", s[i] + 1);
		bptr += (len[i] = strlen(s[i] + 1)) + 1;
		if (len[i] > maxlen) {
			for (j = maxlen + 1; j <= len[i]; ++j) {
				cp[j] = 1ll * cp[j - 1] * c % p;
			}
			maxlen = len[i];
		}

		k = fail[1] = 0;
		for (j = 2; j <= len[i]; ++j) {
			while (k > 0 && s[i][j] != s[i][k + 1]) k = fail[k];
			fail[j] = (s[i][j] == s[i][k + 1] ? ++k : 0);
		}

		hash = k = 0;
		for (j = 1; j <= len[i]; ++j) {
			k = (1ll * k * BASE + w[ch = s[i][j] - 'a']) % MOD;
			hash = hash * CASE + m[ch];
			insert(s[i] + 1, s[i] + j + 1, k, hash, (p + cp[j] - cp[fail[j]]) % p);
		}
	}

	for (i = 1; i <= stot; ++i) sub[i].val = (1ll * sub[i].val * sub[i].cnt) % p;

	for (i = 1; i <= l; ++i) {
		hash = k = 0;
		powb = powc = 1;
		for (j = len[i]; j; --j, powb = 1ll * powb * BASE % MOD, powc *= CASE) {
			k = (1ll * powb * w[ch = s[i][j] - 'a'] + k) % MOD;
			hash += powc * m[ch];
			(ans += getVal(s[i] + j, s[i] + len[i] + 1, k, hash)) %= p;
			// fprintf(stderr, "%d %d %d\n", i, j, ans); fflush(stderr);
		}
	}

	printf("%d\n", ans);

	return 0;
}