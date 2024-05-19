#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define li long long
using namespace std;
inline li read(li l = 0,li r = 1e9){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9'){
		assert(y != '-' && (c == ' ' || c == '\n' || c == '\r' || c == '-'));
		y = c;c = gc;
	} 
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	assert(c == -1 || c == ' ' || c == '\n' || c == '\r');
	if(y == '-') x *= -1;
	//cerr<<l<<" "<<x<<" "<<r<<endl;
	assert(x >= l && x <= r);
	return x;
}
void end_chk(){
	char c;
	do{
		c = gc;
		assert(c == -1 || c == ' ' || c == '\n' || c == '\r');			
	}while(c != -1);
}
int n,m;
int main(){
	int tot = 1;
	for(int tsd = 1;tsd <= tot;++tsd){
		cerr<<tsd<<":"<<endl;
		char ch[50];
		sprintf(ch,"%d.in",tsd);
		freopen(ch,"r",stdin);
		int t = read(1,300000);
		while(t--){
			li n = read(2,1e18l);
			li m = read(1,n - 1);
		} 
		end_chk();
		fclose(stdin); 
		freopen("con","r",stdin);
		sprintf(ch,"std.exe <%d.in >%d.ans",tsd,tsd);
		system(ch);
		sprintf(ch,"zyb.exe <%d.in >zyb.out",tsd);
		system(ch);
		sprintf(ch,"fc %d.ans zyb.out",tsd);
		system(ch);
	} 
	return 0;
}
