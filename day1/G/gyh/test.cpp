#include<cstdio>
long long L,R,ans;
int t;
inline void chk(long long x){
	if(x<ans)return;
	if(R/x-(L-1)/x>1)ans=x;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&L,&R),ans=1;
		for(int i=0;i<=1000000000&&ans==1&&i<=R-L+1;++i)chk(R-L+1-i);
		printf("%lld\n",ans);
	}
}



