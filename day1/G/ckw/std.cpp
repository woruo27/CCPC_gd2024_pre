#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
inline lint inn() { lint x;scanf("%lld",&x);return x; }
int main()
{
	lint T=inn(); assert(T<=10);
	while(T--)
	{
		lint l=inn(),r=inn(),ans=0; assert(1<=l&&l<r&&r<=1000000000000ll);
		for(lint s=1,t;s<=r;s=t+1)
		{
			t=r/(r/s);
			if(s<l) t=min(t,(l-1)/((l-1)/s));
			if(r/s-(l-1)/s>1) ans=max(ans,t);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
