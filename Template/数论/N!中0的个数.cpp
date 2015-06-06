#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int Factor=1005;
int zeros[Factor],a[2577]={1};
void process(){
	double bitNum=1.0;
	for(int n=2,beg=0,e=0;n<=Factor;++n){
		e=bitNum+=log10(n*1.0);
		while(a[beg]==0)
			beg++;
		for(int j=beg,and=0;j<e;j++,and/=10)
			a[j]=(and+=n*a[j])%10;
		zeros[n]=count(a+beg,a+e,0)+beg;
	}
}
int main(){
	process();
	int n;
	while(scanf("%d",&n)!=EOF)
		printf("%d\n",zeros[n]);
}