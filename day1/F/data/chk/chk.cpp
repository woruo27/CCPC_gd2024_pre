//This is a chk avoiding spaces at each end of a line and \n at end of the file
//You can include .h file like testlib.h here
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>

FILE *inFile;
FILE *outFile;
FILE *ansFile;
FILE *scoreFile;
FILE *infoFile;
double score;
bool swap_flag;
std::ostringstream info;

const char esc[][5] = {
	"\\0", "\\x01", "\\x02", "\\x03", "\\x04", "\\x05", "\\x06", "\\a",
	"\\b", "\t", "\\n", "\v", "\\f", "\\r", "\\x0e", "\\x0f",
	"\\x10", "\\x11", "\\x12", "\\x13", "\\x14", "\\x15", "\\x16", "\\x17",
	"\\x18", "\\x19", "\\x1a", "\\x1b", "\\x1c", "\\x1d", "\\x1e", "\\x1f"
};
const int CONTEXT_LEN = 10;

bool blank(char c){
	return c == ' ' || c == '\t' || c == '\r';
}

void ret(double result, bool add_context = true);

struct Reader{
	int ptr, len, line, col;
	bool eof, first;
	FILE *file;
	char buff[CONTEXT_LEN * 3 + 11];
	void fresh(){
		if(!eof && len - ptr < CONTEXT_LEN + 1){
			int lef = std::max(ptr - CONTEXT_LEN, 0);
			int rig = std::min(len, ptr + CONTEXT_LEN * 2 + 1);
			for(int i = lef, j = 0; i <= rig; i++, j++)
				buff[j] = buff[i];
			ptr -= lef;
			len = rig - lef;
			for(int end = ptr + CONTEXT_LEN * 2 + 2; len < end;){
				char c = fgetc(file);
				if(c == EOF){
					eof = true;
					break;
				}
				buff[len++] = c;
			}
			buff[len] = 0;
			first = false;
		}
		if(!line){
			line = 1;
			first = true;
			col++;
		}
	}
	char cur(){
		fresh();
		return buff[ptr];
	}
	char next(){
		if(buff[ptr] == '\n'){
			line++;
			col = 0;
		}
		if(buff[ptr]){
			ptr++;
			col++;
		}
		fresh();
		return buff[ptr];
	}
	bool rest_empty(){
		for(; blank(cur()) || cur() == '\n'; next());
		return !cur();
	}
	int readInt(int l,int r,char*s=NULL){
		char c=next();int f=1,re=0;
		for(;c<'0'||c>'9';c=next()){
			if(c<=0)ret(0);
			if(c=='-')f=-1;
		}
		for(;c>='0'&&c<='9';c=next())re=re*10+(c-'0');
		re=re*f;
		if(re<l||re>r){
			info<<"Input out of bound ("<<l<<","<<r<<").";
			ret(0);
		}
		return re;
	}
}ouf, ans, inf;

std::ostream& operator<<(std::ostream& ost, const Reader& r){
	int lef = std::max(r.ptr - CONTEXT_LEN, 0);
	int rig = std::min(r.ptr + CONTEXT_LEN + 1, r.len);
	if(!r.first || lef != 0)
		ost << "...";
	for(int i = lef; i < rig; i++){
		//Arbiter cannot print {} in info
		if(i == r.ptr)
			ost << (swap_flag ? '[' : '{');
		if(r.buff[i] >= 0 && r.buff[i] < 32)
			ost << esc[r.buff[i]];
		else if(swap_flag && r.buff[i] == '{')
			ost << "\\[";
		else if(swap_flag && r.buff[i] == '}')
			ost << "\\]";
		else
			ost << r.buff[i];
		if(i == r.ptr)
			ost << (swap_flag ? ']' : '}');;
	}
	if(!r.eof || rig != r.len)
		ost << "...";
	return ost;
}

void ret(double result, bool add_context){
	if(add_context)
		if(swap_flag){
			//info in arbiter must shorter than about 100
			info.str("Wrong answer.");
			info << "out:[" << ouf << "]@r" << ouf.line << "c" << ouf.col <<",";
			info << "ans:[" << ans << "]@r" << ans.line << "c" << ans.col <<".";
		}else{
			info << "out: [" << ouf << "] at line " << ouf.line << ", column " << ouf.col <<".\n";
			info << "ans: [" << ans << "] at line " << ans.line << ", column " << ans.col <<".\n";
		}
	if(swap_flag){
		//Arbiter only allow to read EXACTLY one line info, no less and no more, and must BEFORE score
		std::string st = info.str();
		const char* p = st.data();
		//info in arbiter must shorter than about 100
		for(int i = 0; *p && i < 100; p++, i++)
			if(*p < 0 || *p >= 32)
				fputc(*p, infoFile);
			else
				fprintf(infoFile, esc[*p]);
		fputc('\n', infoFile);
	}
	fprintf(scoreFile, "%.6f\n", result * score);
	if(!swap_flag)
		fprintf(infoFile, "%s\n", info.str().data());
	exit(0);
}

void ensuref(int t,std::string o=""){
	if(!t){
		info<<o;
		ret(0);
	}
	return;
}

#include<map>
using std::map;
using std::pair;
using std::make_pair;
using std::swap;
const int maxT=10'000,
    maxN=100'000,sumN=100'000,
    maxM=200'000,sumM=200'000;
map<pair<int,int>,int> mp,vis;
int s[maxM+5];
int chk(int u,int v){
    if(u>v)swap(u,v);
    pair<int,int>tmp=make_pair(u,v);
    return (++vis[tmp])<=mp[tmp];
}

int main(int argc, char **argv){
	//You'd better not change this swith block
	switch(argc){
		case 0: case 1:		//LOJ and debug
			inFile = fopen("input", "r");
			outFile = fopen("user_out", "r");
			ansFile = fopen("answer", "r");
			scoreFile = stdout;
			infoFile = stderr;
			score = 100;
			break;
		case 4:		//Arbiter
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			scoreFile = infoFile = fopen("/tmp/_eval.score", "w");
			score = 10;
			swap_flag = true;
			break;
		case 5:
			if(strcmp(argv[4], "THUOJ") == 0){	//Tsinghua OJ(OJ for DSA course)
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[3], "r");
				ansFile = fopen(argv[2], "r");
				scoreFile = stdout;
				infoFile = stdout;
				score = 100;
			}else{								//Tsinsen OJ
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[2], "r");
				ansFile = fopen(argv[3], "r");
				scoreFile = fopen(argv[4], "w");
				infoFile = fopen("tmp", "w");		//Tsinsen doesn't use this file
				score = 1;
			}
			break;
		case 7:		//Lemon and TUOJ
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			FILE *fs = fopen(argv[4], "r");
			if(fs)
				fscanf(fs, "%lf", &score);		//Current TUOJ
			else
				sscanf(argv[4], "%lf", &score);	//Lemon and future TUOJ
			scoreFile = fopen(argv[5], "w");
			infoFile = fopen(argv[6], "w");
			break;
	}
	ouf.file = outFile;
	ans.file = ansFile;
	inf.file = inFile;

    int T=inf.readInt(1,maxT,"T");
    int sn=0,sm=0;
    for(int i=1;i<=T;++i){
        int n=inf.readInt(2,maxN,"n"),m=inf.readInt(1,maxM,"m");
        sn+=n;sm+=m;
        ensuref(sn<=maxN,"sum of n should not exceed 100000.");
        ensuref(sm<=maxM,"sum of m should not exceed 200000.");
        for(int i=1;i<=m;++i){
            int u=inf.readInt(1,n,"u"),v=inf.readInt(1,n,"v");
            ensuref(u!=v,"No self-loop.");
            if(u>v)swap(u,v);
            ++mp[make_pair(u,v)];
        }
        int k=(m+n-2)/(n-1);
        int anss=ans.readInt(1,n),anst=ans.readInt(1,n);
        ensuref(anss!=anst,"s should not be equal to t.");
        for(int j=1;j<=k;++j){
            int cn=ans.readInt(1,m+1);
            for(int k=1;k<=cn;++k)
                s[k]=ans.readInt(1,n);
            ensuref(s[1]==anss,"Begin in s.");
            ensuref(s[cn]==anst,"End in t.");
            for(int k=1;k<cn;++k){
                int u=s[k],v=s[k+1];
                ensuref(chk(u,v),"No edge cross.");
            }
        }
        vis.clear();
        int oufs=ouf.readInt(1,n),ouft=ouf.readInt(1,n);
        ensuref(oufs!=ouft,"s should not be equal to t.");
        for(int j=1;j<=k;++j){
            int cn=ouf.readInt(1,m+1);
            for(int k=1;k<=cn;++k)
                s[k]=ouf.readInt(1,n);
            ensuref(s[1]==oufs,"Begin in s.");
            ensuref(s[cn]==ouft,"End in t.");
            for(int k=1;k<cn;++k){
                int u=s[k],v=s[k+1];
                ensuref(chk(u,v),"No edge cross.");
            }
        }
        vis.clear();
        mp.clear();
    }
    ret(1,false);
	return 0;
}
