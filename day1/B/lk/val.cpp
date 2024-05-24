#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;
signed main(){
	registerValidation();
	int L,C;
	L=inf.readInt(1,3000000,"L");inf.readSpace();C=inf.readInt(2,(1<<30)-2,"C");inf.readSpace();inf.readInt(C+1,(1<<30)-1,"P");inf.readEoln();
	int sl=0;
	for(int i=1;i<=L;++i){
		string s=inf.readToken("[a-z]{1,3000000}");
		inf.readEoln();
		sl+=s.length();
		ensuref(sl<=3000000, "sum(|si|) > 3000000");
	}
	inf.readEof();
	return 0;
}
