#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
mt19937_64 rnd(1145141);
int ID,N=1e12;
inline 
void Gen1(int z){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%lld\n",z);
	for(re int i=1;i<=z;++i){
		int L=rnd()%N+1,R=rnd()%N+1;
		while(L>=R)L=rnd()%N+1,R=rnd()%N+1;
		printf("%lld %lld\n",L,R);
	}
}
void Gen2(int z,int k){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%lld\n",z);
	for(re int i=1;i<=z;++i){
		int L=rnd()%(N/2)+1,R;
		R=L+rnd()%max(1ll,(L/k))+1;
		printf("%lld %lld\n",L,R);
	}
}
void Gen3(re int z){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	re int k=N/z;
	printf("%d\n",10);
	for(re int i=1;i<=10;++i){
		int x=rnd()%(k-1)+1;
		printf("%lld %lld\n",max(1ll,x*z-((long long)rnd()%100000000ll)),min(N,(x+1)*z+(long long)((rnd()%10))));
	}
}
inline void Gen4(re int L,re int R){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%d\n",10);
	for(re int i=1;i<=10;++i){
		printf("%lld %lld\n",L,R);
	}
}
signed main(){
	ID=1;
	Gen1(6),Gen1(7),Gen1(8),Gen1(9),Gen1(10);
	for(re int i=1;i<=1024;i<<=1)Gen2(10,i);
	Gen3(237482749529ll);Gen3(114514114529ll),Gen3(83742648617ll),Gen3(24362849411ll),Gen3(77723949217ll);
	Gen3(100003ll*100019ll),Gen3(100043ll*100049ll),Gen3(100049ll*800083ll);
	Gen4(1,1000000000000ll),Gen4(1000000000000ll-1,1000000000000ll),Gen4(1000000000000ll-1000000,1000000000000ll);
	for(re int i=1;i<=ID;++i){
		string tmp="std.exe < "+to_string(i)+".in > "+to_string(i)+".ans";
		cerr<<tmp<<endl;
		system(tmp.c_str());
	}
}



