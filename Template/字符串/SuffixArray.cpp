#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

//δ��֤

#define maxn 11000
//�÷�: 1,��ֵdata(base1). 2,��ֵn(����). 3,make_SA(). 4,make_H().
int data[maxn], n; //n�ַ�������
#define getR(a) ((a)>n?0:rnk[a])
inline bool cmp(int a, int b){ return data[a] < data[b]; }
void Double(int L, int *SA, int *rnk){//ÿ�μ�����Ǹ���SA��rnk
	static int _SA[maxn], _rnk[maxn], c[maxn], a[maxn]; 

	fill(c, c + n + 1, 0);
	for (int i = 1; i <= n; ++ i) c[getR(i + L)] ++;
	a[0] = 1; //a[i]rank��i�ĺ�׺����ʼindex
	for (int i = 1; i <= n; ++ i) a[i] = a[i - 1] + c[i - 1];
	for (int i = 1; i <= n; ++ i) _SA[a[getR(i + L)] ++] = i;

	//���ü���������ȶ��ԣ���Դ�Ҫ�ؼ��ֺ���Ҫ�ؼ��ֱַ�����
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

//SA�Ǻ�׺����,SA[i]��ʾ�ŵ�iλ�ĺ�׺��˭
//rnk����������,rnk[i]��ʾ��׺i�ŵڼ�
//H�Ǹ߶�����,H[i]ΪSA[i]��SA[i-1]��LCP,�ʴ�2��ʼ
int SA[maxn], rnk[maxn], H[maxn]; 
void make_SA() { //���ַ���ֵ��С�޹ص�!!
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
	//���ʣ�
	//data: ...xi....yj..., 
	//SA:   ....yx...j..i...
	//�����SA��xǰ����y,��ô��׺i����֮ǰ�ĺ�׺��lcp������_h[x]-1
	static int _h[maxn];//_h��ʾ��׺i�ͺ�׺j��LCP����׺j�������Ⱥ�׺iС1
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
}//*************ģ�����***************

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
