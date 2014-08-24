#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int phi(int n){
	int ret=1,i;

	for (i=2;i*i<=n;i++){

		if (n%i==0){

			n/=i,ret*=(i-1);

			while (n%i==0) n/=i,ret*=i;

		}

	}

	if (n>1)  ret*=n-1;  return ret;

}
typedef long long LL;

int mod = 1000000007;

int main() {

	int n, k;
	while (scanf("%d %d", &n, &k) != EOF) {
		if (k > 2) {
			puts("0");
			continue;
		}
		if (k == 2) {
			puts("1");
			continue;
		}
		int ans = 0;
		for (int d1 = 1; d1 * d1 <= n; d1 ++) {
			if (n % d1) continue;
			int t1 = phi(n / d1);
			int t2 = phi(d1);
			ans = (ans + t1 * (LL) t2) % mod;
			if (d1 * d1 != n) {
				ans = (ans + t1 * (LL)t2) % mod;
			}
		}
		printf("%d\n", ans);
	}
}


