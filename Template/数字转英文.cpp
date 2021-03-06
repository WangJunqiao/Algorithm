#include <iostream>
#include<vector>
#include<map>
#include<stack>
#include<string>
#include<algorithm>
using namespace std;
//����תӢ��
map<int,string> mp,mpt;

void init(){
	mp[1]= "one"; mpt[1]="first";
	mp[2]= "two"; mpt[2]="second";
	mp[3]= "three"; mpt[3]="third";
	mp[4]= "four"; mpt[4]="fourth";
	mp[5]= "five"; mpt[5]="fifth";
	mp[6]= "six"; mpt[6]="sixth";
	mp[7]= "seven"; mpt[7]="seventh";
	mp[8]= "eight"; mpt[8]="eighth";
	mp[9]= "nine"; mpt[9]="ninth";
	mp[10]= "ten"; mpt[10]="tenth";
	mp[11]= "eleven"; mpt[11]="eleventh";
	mp[12]= "twelve"; mpt[12]="twelfth";
	mp[13]= "thirteen"; mpt[13]="thirteenth";
	mp[14]= "fourteen"; mpt[14]="fourteenth";
	mp[15]= "fifteen"; mpt[15]="fifteenth";
	mp[16]= "sixteen"; mpt[16]="sixteenth";
	mp[17]= "seventeen"; mpt[17]="seventeenth";
	mp[18]= "eighteen"; mpt[18]="eighteenth";
	mp[19]= "nineteen"; mpt[19]="nineteenth";
	mp[20]= "twenty"; mpt[20]="twentieth";
	mp[30]= "thirty"; mpt[30]="thirtieth";
	mp[40]= "forty"; mpt[40]="fortieth";
	mp[50]= "fifty"; mpt[50]="fiftieth";
	mp[60]= "sixty"; mpt[60]="sixtieth";
	mp[70]= "seventy"; mpt[70]="seventieth";
	mp[80]= "eighty"; mpt[80]="eightieth";
	mp[90]= "ninety"; mpt[90]="ninetieth";
	mp[100]= "hundred"; mpt[100]="hundredth";
	mp[1000]= "thousand"; mpt[1000]="thousandth";
}

char buf[2000000]=" tisthe";
int tail=7;

void print(string s){
	for(int i=0;i<s.length();i++){
		buf[tail++]=s[i];
	}	
}

void dfs(int t){
	if( t==0 ) return;
	
	if( mp.find(t)!=mp.end()){
		if( t==100 || t==1000 ) print("one"); // ****
		print(mp[t]);
	}else{
		if( t>=1000 ){
			dfs(t/1000);
			print("thousand");
			dfs(t%1000);
		}else if( t>=100 ){
			dfs(t/100);
			print("hundred");
			dfs(t%100);
		}else if( t>10 ){
			dfs(t/10*10);
			dfs(t%10);
		}
	}
}
void dfst(int t){
	if( t==0 ) return;
	if( mpt.find(t) !=mpt.end()){
		if( t==100 || t==1000 ) print("one"); // ****
		print(mpt[t]);
	}else{
		if( t>=1000 ){
			dfs(t/1000);
			print("thousand");
			if( t%1000==0 ) { print("th"); return; }
			dfst(t%1000);
		}else if( t>=100 ){
			dfs(t/100);
			print("hundred");
			if( t%100==0 ) { print("th"); return; }
			dfst(t%100);
		}else if( t>10 ){
			dfs(t/10*10);
			dfst(t%10);
		}
	}
}

int ans[100005];

void test(){
	int ind=1;
	for(int i=1;;i++){
		if( ind>100000 ) break;
		if( buf[i]=='t' ){
			ans[ind++]=i;
			dfst(i);
		}
	}
}

void tt(){
	int t;
	while(cin>>t){
		memset(buf,0,sizeof(buf));
		tail=0;
		dfst(t);
		puts(buf);
	}
}

int main(){
	init();
	tt();
	test();
	int n;
	while( scanf("%d",&n) && n) printf("%d\n",ans[n]);
}