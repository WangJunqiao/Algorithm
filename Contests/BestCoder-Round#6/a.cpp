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

typedef long long LL;

int a[11000];

int main(){
	int n;
	while (scanf("%d", &n) != EOF) {
		int sum = 0;
		for (int i = 1; i <= n; i ++) {
			int x; 
			scanf("%d", &x);
			a[i] = x;
			sum += x;
		}
		sort(a + 1, a + n + 1);
		int median = a[(n + 1) / 2];
		if (sum >= n * median) {
			puts("NO");
		} else {
			puts("YES");
		}
	}
}

