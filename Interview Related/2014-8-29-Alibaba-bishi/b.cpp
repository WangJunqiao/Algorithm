#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define maxn 1100000
char data[maxn];
int SA[maxn],rnk[maxn],H[maxn],n; 
#define getR(a)((a)>n?0:rnk[a])
inline bool cmp(int a,int b){ return data[a] < data[b]; }
int c[maxn],a[maxn],_SA[maxn],_rnk[maxn],_h[maxn],L;
void Double(){
	memset(c,0,sizeof(int) * (n + 1));int i;
	for (i=1;i<=n;i++) c[getR(i + L)]++;
	a[0] = 1;for (i=1;i<=n;i++) a[i] = a[i - 1] + c[i - 1];
	for (i=1;i<=n;i++) _SA[a[getR(i + L)]++] = i;
	memset(c,0,sizeof(int) * (n + 1));
	for (i=1;i<=n;i++) c[getR(i)]++;
	a[0] = 1;for (i=1;i<=n;i++) a[i] = a[i - 1] + c[i - 1];
	for (i=1;i<=n;i++) SA[a[getR(_SA[i])]++] = _SA[i];
	_rnk[SA[1]] = 1;
	for (i=2;i<=n;i++) 
		if (getR(SA[i]) == getR(SA[i - 1]) && getR(SA[i] + L) == getR(SA[i - 1] + L)) 
			_rnk[SA[i]] = _rnk[SA[i - 1]];
		else
			_rnk[SA[i]] = _rnk[SA[i - 1]] + 1;
	memcpy(rnk,_rnk,sizeof(int) * (n + 1));
	L <<= 1;
}

void make_SA(){ 
	int i;
	for (i=1;i<=n;i++) SA[i] = i;
	sort(SA + 1,SA + n + 1,cmp);rnk[SA[1]] = 1;
	for (i=2;i<=n;i++) 
		if (data[SA[i]] == data[SA[i - 1]]) rnk[SA[i]] = rnk[SA[i - 1]]; 
		else rnk[SA[i]] = rnk[SA[i - 1]] + 1;
	L = 1; while (L < n) Double();
}

void make_H(){
	int i;
	memset(_h,0,sizeof(int) * (n + 1));
	for (i=1;i<=n;i++) if (rnk[i] == 1) _h[i] = 0;
	else if (i == 1 || _h[i - 1] <= 1) 
		while (data[i + _h[i]] == data[SA[rnk[i] - 1] + _h[i]]) _h[i]++;
	else{
		_h[i] = _h[i - 1] - 1;
		while (data[i + _h[i]] == data[SA[rnk[i] - 1] + _h[i]]) _h[i]++;
	}
	for (i=1;i<=n;i++) H[rnk[i]] = _h[i];

}
//采用后缀数组的解法。复杂度为n*log(n), 其中n = query.length + text.length
//首先把两个字符串串起来，中间用一个#隔开。
//然后计算后缀数组SA和高度数组H。
//H是高度数组,H[i]为SA[i]和SA[i-1]的最长公共前缀。
int find(const char *query, const char *text) {
	int len1 = strlen(query);
	int len2 = strlen(text);
	n = 0;
	for (int i = 1; i <= len1; i ++) {
		data[++ n] = query[i - 1];
	}
	data[++ n] = '#'; //all other character is lower case letter!!
	for (int i = 1; i <= len2; i ++) {
		data[++ n] = text[i - 1];
	}

	make_SA();
	make_H();
	int ans = 0;
	for (int i = 2; i <= n; i ++) {
		//当前后两个分别在query和text中就更新答案
		if ((SA[i] <= len1 && SA[i - 1] > len1 +1) 
			|| (SA[i] > len1 + 1 && SA[i - 1] <= len1)) {
			ans = max(ans, H[i]);
		}
	}
	return ans;
}


int main() {
	cout << find("acbac", "acaccbabb") << endl;	
}
