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


int checks, MAX = 20;

bool can(int left_num, int cur, int sum, int n, int spe) {
	if (checks > MAX) return false;
	if (left_num == 1) {
		int last = n - sum;
		if (last < cur || last == spe) {
			checks ++;
			return false;
		} else {
			return true;
		}
	}
	if (cur == spe) cur ++;
	while(true) {
		if (checks > MAX) return false;
		if(can(left_num - 1, cur + 1, sum + cur, n , spe))
		  return true;
		cur ++;
	}
	return false;
}

int main() {
	int n, k;
	while (scanf("%d %d", &n, &k) != EOF) {
		bool found = false;
		for (int sq = 500; sq >= 1; sq --) {
			if (sq * sq >= n) continue;
			checks = 0;
			if (can(k - 1, 1, n - sq * sq, n, n - sq * sq)) {
				found = true;
			}
		}
		if (found) puts("YES");
		else puts("NO");
	}
}

