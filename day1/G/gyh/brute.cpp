#include<cstdio>
long long L,R,ans;
int t;
inline long long gcd(long long x,long long y){return y?gcd(y,x%y):x;}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&L,&R),ans=0;
		for(long long i=R-1000;i<=R;++i)for(long long j=L;j<=L+1000&&j<i;++j){long long x=gcd(i,j);if(x>ans)ans=x;}
		printf("%lld\n",ans);
	}
}



