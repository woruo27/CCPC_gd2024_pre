#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
const int mod=998244353;
typedef long long ll;
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second

void add(int &x,int y){x=(x+y>=mod)?(x+y-mod):x+y;}
int qpow(int x,int y){int ret=1;while(y){if(y&1)ret=1ll*ret*x%mod;x=1ll*x*x%mod;y>>=1;}return ret;}
int n[9]={0,3,5,10,20,200,2000,20000,200000};
mt19937_64 rnd(time(0));
char cmd[80];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
    rep(task,1,40){
        sprintf(cmd,"std < ../data/%d.in > ../data/%d.ans",task,task);
        system(cmd);
    }
    return 0;
    rep(ns,1,8)rep(prop,1,5){
        int tasknum=(ns-1)*5+prop;
        int n=::n[ns];
        int m=min(200000,(int)(n*(0.04*prop))+1);
        if(prop==5&&ns==8)m=200000;
        sprintf(cmd,"%d.in",tasknum);
        freopen(cmd,"w",stdout);
        printf("%d %d\n",n,m);
        int cnt=1;
        rep(i,1,m){
            int x,y,z;
            x=rnd()%n+1;y=rnd()%n+1;z=rnd()%n+1;
            if(rnd()%m<=min(m/2,28)){
                x=cnt;y=++cnt;z=(rnd()%2?cnt:cnt+1);
                x=min(n,x);y=min(n,y);z=min(n,z);
            }
            printf("%d %d %d\n",x,y,z);
        }
        fclose(stdout);
        sprintf(cmd,"std < %d.in > %d.out",tasknum,tasknum);
        system(cmd);
        cerr<<"cnt= "<<cnt<<endl;
    }
	return 0;
}
