#include <vector>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <cassert>

using namespace std;


char a[3][3][2][2];
bool can[3][3];

queue<string> q;

string get(char ch[][3]) {
	string s = "";
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) s+=ch[i][j];
	return s;
}

char mat[6][6];
bool vst[6][6];
bool ill(int x, int y) {
	return x>=0 && x<6 && y>=0 && y<6;
}
void dfs(int x, int y);

inline void _dfs(int px, int py, int x, int y) {
	if(!ill(x, y) || vst[x][y] || mat[px][py]!=mat[x][y]) return;
	dfs(x, y);
}

void dfs(int x, int y) {
	vst[x][y] = true;
	int tx = x%2, ty = y%2;
	if(tx==0 && ty==0) {
		_dfs(x, y, x+1, y);
		_dfs(x, y, x+1, y+1);
		_dfs(x, y, x-2, y+1);
	} else if(tx==0 && ty==1) {
		_dfs(x, y, x+1, y);
		_dfs(x, y, x+1, y-1);
		_dfs(x, y, x+2, y-1);
	} else if(tx==1 && ty==0) {
		_dfs(x, y, x-1, y);
		_dfs(x, y, x-1, y+1);
		_dfs(x, y, x, y-1);
	} else {
		_dfs(x, y, x-1, y-1);
		_dfs(x, y, x-1, y);
		_dfs(x, y, x, y+1);
	}
}

bool out;
bool check(char ch[][3]) {
	memset(vst, false, sizeof(vst));
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			int x = i*2;
			int y = j*2;
			int ss = ch[i][j]-'0';
			int ti = ss/3, tj = ss%3;
			for(int p=0;p<2;p++) for(int q=0;q<2;q++) {
				mat[x+p][y+q] = a[ti][tj][p][q];
			}
		}
	}

	set<char> st;
	for(int i=0;i<6;i++) for(int j=0;j<6;j++) {
		if(vst[i][j]) continue;
		if(st.find(mat[i][j]) == st.end()) {
			dfs(i, j);
			st.insert(mat[i][j]);
		}else{
			return false;
		}
	}
	return true;
}

int mp[550000];
int main() {
	int T; scanf("%d", &T);
	int Te=1;
	while(T--) {
		map<string, int> mp;
		for(int i=0;i<3;i++) {
			for(int j=0;j<3;j++) {
				string s; cin>>s;
				a[i][j][0][0] = s[0];
				a[i][j][0][1] = s[1];
				a[i][j][1][0] = s[2];
				a[i][j][1][1] = s[3];
				can[i][j] = (s[4]=='0');
			}
		}
		while(!q.empty()) q.pop();
		//clr(mp, 0x3f);
		q.push("012345678");
		mp["012345678"] = 0;
		int ans;

		while(!q.empty()) {
			char ch[3][3];
			string s= q.front(); q.pop();
			//out =false;

			//printf("s = %s\n", s.c_str());
			for(int i=0, c=0;i<3;i++) {
				for(int j=0;j<3;j++) {
					ch[i][j] = s[c++];
				}
			}
			int last_ans = mp[s];
			//printf("last_ans = %d\n", last_ans);
			if(q.size()==0 && check(ch)) {
				ans = last_ans;
				break;
			}

			char tmp[3][3], tc;
			int hs;
			for(int r=0;r<3;r++) {
				if(!can[r*3] || !can[r*3+1] || !can[r*3+2]) 
					continue;
				memcpy(tmp, ch, sizeof(ch));
				tc = tmp[r][0];
				tmp[r][0] = tmp[r][1];
				tmp[r][1] = tmp[r][2];
				tmp[r][2] = tc;
				s = get(tmp);
				if(mp.find(s) == mp.end()) {
					mp[s] = last_ans + 1;
					q.push(s);
					if(check(tmp)) {
						ans = last_ans + 1;
						goto KKK;
					}
				}

				memcpy(tmp, ch, sizeof(ch));
				tc = tmp[r][2];
				tmp[r][2] = tmp[r][1];
				tmp[r][1] = tmp[r][0];
				tmp[r][0] = tc;
				s = get(tmp);
				if(mp.find(s) == mp.end()) {
					mp[s] = last_ans + 1;
					q.push(s);
					if(check(tmp)) {
						ans = last_ans + 1;
						goto KKK;
					}
				}

			}
			for(int c=0;c<3;c++) {
				if(!can[c] || !can[3+c] || !can[6+c]) 
					continue;
				memcpy(tmp, ch, sizeof(ch));
				tc = tmp[0][c];
				tmp[0][c] = tmp[1][c];
				tmp[1][c] = tmp[2][c];
				tmp[2][c] = tc;
				s = get(tmp);
				if(mp.find(s) == mp.end()) {
					mp[s] = last_ans + 1;
					q.push(s);
					if(check(tmp)) {
						ans = last_ans + 1;
						goto KKK;
					}
				}

				memcpy(tmp, ch, sizeof(ch));
				tc = tmp[2][c];
				tmp[2][c] = tmp[1][c];
				tmp[1][c] = tmp[0][c];
				tmp[0][c] = tc;
				s = get(tmp);
				if(mp.find(s) == mp.end()) {
					mp[s] = last_ans + 1;
					q.push(s);
					if(check(tmp)) {
						ans = last_ans + 1;
						goto KKK;
					}
				}
			}
		}
		//if(ans>=1000) while(1) cout<<"fda"<<endl;
		KKK:;
		printf("Case #%d: %d\n", Te++, ans);
	}
}
