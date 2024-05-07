#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MX=30;
string str[MX]={
    "gen1 -n 2 -m 20 > 1.in",
    "gen1 -n 5 -m 20 > 2.in",
    "gen1 -n 10 -m 20 > 3.in",
    "gen1 -n 50 -m 50 > 4.in",
    "gen1 -n 50 -m 1000 > 5.in",
    "gen1 -n 100 -m 10000 > 6.in",
    "gen1 -n 1000 -m 1999 > 7.in",
    "gen2 -n 100 -m 100 > 8.in",
    "gen2 -n 200 -m 399 > 9.in",
    "gen2 -n 10 -m 91 > 10.in",
    "gen2 -n 5 -m 101 > 11.in",
    "gen2 -n 100000 -m 200000 > 12.in",
    "gen2 -n 100000 -m 100000 > 13.in",
    "gen2 -n 10000 -m 10000 > 14.in",
    "gen3 -n 100 -m 100 > 15.in",
    "gen3 -n 200 -m 399 > 16.in",
    "gen3 -n 10 -m 91 > 17.in",
    "gen3 -n 5 -m 101 > 18.in",
    "gen3 -n 100000 -m 200000 > 19.in",
    "gen3 -n 100000 -m 100000 > 20.in",
    "gen3 -n 10000 -m 10000 > 21.in",
    "gen3 -n 1000 -m 9991 > 22.in",
    "gen4 -n 50 -m 1000 > 23.in",
    "gen4 -n 100 -m 10000 > 24.in",
    "gen4 -n 1000 -m 1999 > 25.in",
    "gen1 -n 100 -m 200000 > 26.in",
    "gen2 -n 11 -m 199991 > 27.in",
    "gen3 -n 11 -m 199991 > 28.in",
    "gen3 -n 101 -m 199901 > 29.in",
    "gen4 -n 200 -m 200000 > 30.in"
};
char s[100005];
void syst(const char* x){
    printf("%s\n",x);fflush(stdout);
    system(x);
}
int main(){
    syst("g++ -O2 -std=c++14 -Wall -Wl,--stack=268435456 std.cpp -o std.exe");
    syst("g++ -O2 -std=c++14 -Wall -Wl,--stack=268435456 chk.cpp -o chk.exe");
    syst("g++ -O2 -std=c++14 -Wall -Wl,--stack=268435456 validator.cpp -o validator.exe");
    syst("g++ -O2 -std=c++14 -Wall -Wl,--stack=268435456 gen1.cpp -o gen1.exe");
    syst("g++ -O2 -std=c++14 -Wall -Wl,--stack=268435456 gen2.cpp -o gen2.exe");
    syst("g++ -O2 -std=c++14 -Wall -Wl,--stack=268435456 gen3.cpp -o gen3.exe");
    syst("g++ -O2 -std=c++14 -Wall -Wl,--stack=268435456 gen4.cpp -o gen4.exe");
    for(int i=0;i<MX;++i)syst(str[i].c_str());
    for(int i=1;i<=MX;++i){
        sprintf(s,"validator < %d.in",i);
        syst(s);
    }
    for(int i=1;i<=MX;++i){
        sprintf(s,"std < %d.in > %d.ans",i,i);
        syst(s);
    }
    for(int i=1;i<=MX;++i){
        sprintf(s,"chk %d.in %d.ans %d.ans",i,i,i);
        syst(s);
    }
    // syst("pause");
    return 0;
}