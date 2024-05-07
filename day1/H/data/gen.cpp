#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
mt19937 rnd(1145141);
int ID,n,m,b[502];
inline int Rand(re int L,re int R){
	return rnd()%(R-L+1)+L;
}
inline vector<int> Randperm(re int k){
	vector<int>A;
	for(re int i=1;i<=k;++i)A.push_back(i);
	shuffle(A.begin(),A.end(),rnd);
	return A;
}
void Gen1(re int L,re int R,re int k,int opt=0){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	int t=500/R;
	printf("%d\n",t);
	while(t--){
		n=Rand(L,R),m=Rand(L,R);
		printf("%d %d\n",n,m);
		for(re int i=1;i<=m;++i)b[i]=0;
		for(re int i=1;i<=n;++i)++b[rnd()%m+1];
		if(opt==1)for(re int i=1;i<=m;++i)b[i]=1;
		if(opt==2)for(re int i=m/2+1;i<=m;++i)b[i]=500;
		for(re int i=1;i<m;++i)printf("%d ",b[i]);printf("%d\n",b[m]);
		for(re int i=1;i<=n;++i){
			re int x=Rand(0,min(k,opt==2?m/2:m));
			if(k==500)x=min(k,m)-rnd()%5;
			if(x==0){
				puts("0");
				continue;
			}
			printf("%d ",x);
			vector<int>A=Randperm(opt==2?m/2:m);
			for(re int j=0;j<x-1;++j)printf("%d ",A[j]);printf("%d\n",A[x-1]);
		}
	} 
}
void Gen2(re int L,re int R,re int k,int opt=0){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	int t=500/R;
	printf("%d\n",t);
	while(t--){
		n=Rand(L,R),m=Rand(L,R);
		printf("%d %d\n",n,m);
		for(re int i=1;i<=m;++i)b[i]=0;
		for(re int i=1;i<=n;++i)++b[(int)(sqrt(rnd()%(m*m)))+1];
		if(opt)for(re int i=1;i<=m;++i)b[i]=1;
		for(re int i=1;i<m;++i)printf("%d ",b[i]);printf("%d\n",b[m]);
		for(re int i=1;i<=n;++i){
			re int x=Rand(0,min(k,m));
			if(x==0){
				puts("0");
				continue;
			}
			printf("%d ",x);
			vector<int>A=Randperm(m);
			for(re int ii=0;ii<10;++ii)
				for(re int jj=0;jj+1<A.size();++jj)
					if(rnd()%2==0&&A[jj]>A[jj+1])swap(A[jj],A[jj+1]);
			for(re int j=0;j<x-1;++j)printf("%d ",A[j]);printf("%d\n",A[x-1]);
		}
	} 
}
inline void Gen3(re int L,re int R,re int k){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	int t=500/R;
	printf("%d\n",t);
	while(t--){
		n=Rand(L,R),m=Rand(L,R);
		printf("%d %d\n",n,m);
		for(re int i=1;i<=m;++i)b[i]=0;
		for(re int i=1;i<=m;++i)b[i]=1;
		for(re int i=1;i<m;++i)printf("%d ",b[i]);printf("%d\n",b[m]);
		for(re int i=1;i<=n;++i){
			vector<int>A;
			for(re int j=0;j<k;++j)if(rnd()%2==0)A.push_back(i+j);
			re int x=A.size();
			if(x==0){
				puts("0");
				continue;
			}
			shuffle(A.begin(),A.end(),rnd);
			printf("%d ",x);
			for(re int j=0;j<x-1;++j)printf("%d ",(A[j]-1)%m+1);printf("%d\n",(A[x-1]-1)%m+1);
		}
	} 
}
signed main(){
	ID=1;
	Gen1(1,2,2),Gen1(3,3,2),Gen1(4,4,3),Gen1(5,5,3),Gen1(45,50,10),Gen1(495,500,50),Gen1(495,500,500);
	Gen1(95,100,2),Gen1(95,100,5),Gen1(95,100,10),Gen1(95,100,50);
	Gen1(95,100,2,1),Gen1(495,500,2,1),Gen1(49,50,2,1),Gen1(49,50,3,1),Gen1(495,500,3,1);
	Gen2(1,2,2),Gen2(3,3,2),Gen2(4,4,3),Gen2(5,5,3),Gen2(45,50,10),Gen2(495,500,50),Gen2(495,500,500);
	Gen2(95,100,2),Gen2(95,100,5),Gen2(95,100,10),Gen2(95,100,50),Gen2(495,500,3);
	Gen1(495,500,50,2),Gen1(495,500,500,2);
	Gen3(45,50,2),Gen3(95,100,2),Gen3(495,500,2);
	Gen3(45,50,3),Gen3(95,100,3),Gen3(495,500,3);
	Gen3(45,50,5),Gen3(95,100,5),Gen3(495,500,5);
	Gen3(45,50,10),Gen3(95,100,10),Gen3(495,500,10);
	for(re int i=1;i<=ID;++i){
		string tmp="std.exe < "+to_string(i)+".in > "+to_string(i)+".ans";
		cerr<<tmp<<endl;
		system(tmp.c_str());
	}
}



