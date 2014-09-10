#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

//未验证

#define maxn 11000
//用法: 1,赋值data(base1). 2,赋值n(串长). 3,make_SA(). 4,make_H().
int data[maxn], n; //n字符串长度
#define getR(a) ((a)>n?0:rnk[a])
inline bool cmp(int a, int b){ return data[a] < data[b]; }
void Double(int L, int *SA, int *rnk){//每次计算就是更新SA和rnk
	static int _SA[maxn], _rnk[maxn], c[maxn], a[maxn]; 

	fill(c, c + n + 1, 0);
	for (int i = 1; i <= n; ++ i) c[getR(i + L)] ++;
	a[0] = 1; //a[i]rank是i的后缀的起始index
	for (int i = 1; i <= n; ++ i) a[i] = a[i - 1] + c[i - 1];
	for (int i = 1; i <= n; ++ i) _SA[a[getR(i + L)] ++] = i;

	//利用计数排序的稳定性，针对次要关键字和主要关键字分别排序
	fill(c, c + n + 1, 0);
	for (int i = 1; i <= n; ++ i) c[getR(_SA[i])]++;
	a[0] = 1;
	for (int i = 1; i <= n; ++ i) a[i] = a[i - 1] + c[i - 1];
	for (int i = 1; i <= n; ++ i) SA[a[getR(_SA[i])] ++] = _SA[i];
	
	_rnk[SA[1]] = 1;
	for (int i=2;i<=n;i++)
		if (getR(SA[i]) == getR(SA[i - 1]) && getR(SA[i] + L) == getR(SA[i - 1] + L)) 
			_rnk[SA[i]] = _rnk[SA[i - 1]];
		else
			_rnk[SA[i]] = _rnk[SA[i - 1]] + 1;
	memcpy(rnk, _rnk, sizeof(int) * (n + 1));
}

//SA是后缀数组,SA[i]表示排第i位的后缀是谁
//rnk是排名数组,rnk[i]表示后缀i排第几
//H是高度数组,H[i]为SA[i]和SA[i-1]的LCP,故从2开始
int SA[maxn], rnk[maxn], H[maxn]; 
void make_SA() { //跟字符串值大小无关的!!
	//intialize SA and rnk
	for (int i = 1; i <= n; ++ i) SA[i] = i;
	sort(SA + 1, SA + n + 1, cmp);
	rnk[SA[1]] = 1;
	for (int i = 2; i <= n; ++ i)
		rnk[SA[i]] = rnk[SA[i - 1]] + (data[SA[i]] != data[SA[i - 1]]);
	//run Count Sort iteratively
	for (int L = 1; L < n; L <<= 1) {
		Double(L, SA, rnk);
	}
}

void make_H(){
	//性质：
	//data: ...xi....yj..., 
	//SA:   ....yx...j..i...
	//如果在SA中x前面是y,那么后缀i和它之前的后缀的lcp至少是_h[x]-1
	static int _h[maxn];//_h表示后缀i和后缀j的LCP，后缀j的排名比后缀i小1
	fill(_h, _h + n + 1, 0);
	for (int i = 1; i <= n; ++ i) {
		if (rnk[i] == 1) _h[i] = 0;
		else if (i == 1 || _h[i - 1] <= 1) 
			while (data[i + _h[i]] == data[SA[rnk[i] - 1] + _h[i]]) _h[i]++;
		else{
			_h[i] = _h[i - 1] - 1;
			while (data[i + _h[i]] == data[SA[rnk[i] - 1] + _h[i]]) _h[i]++;
		}
	}
	for (int i = 1; i <= n; ++ i) H[rnk[i]] = _h[i];
}//*************模板结束***************

int main() {
	n = 0;
	data[++n] = 1;
	data[++n] = 2;
	data[++n] = 2;
	data[++n] = 1;
	make_SA();
	make_H();
	for (int i = 1; i <= n; ++ i) {
		printf("SA[%d] = %d, rnk[%d] = %d, H[%d] = %d\n", i, SA[i], i, rnk[i], i, H[i]);
	}
}
