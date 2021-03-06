//vector做平衡树用
vector<int>::iterator it;
void insert(vector<int> &v,int val){ //插入
	it=lower_bound(v.begin(),v.end(),val);
	v.insert(it,val);
}
void remove(vector<int> &v,int val){ //删除
	it=lower_bound(v.begin(),v.end(),val);
	if( it!=v.end() && *it == val ) v.erase(it);
}//-----------------------------------------------------









/*
Test: 在已有10w个有序元素的序列中再插入10w个数, 这些数都在中间, 也就是每次都要挪动5w个数才能插入一个
测试结果:
	类似插入排序的暴力插入用时27秒.
	vector的插入用时4秒.
代码如下:

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

//----------------------zjut_DD for Topcoder-------------------------------
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
#define PB push_back
#define MP make_pair
#define ff first
#define ss second
#define two(w) (1<<(w))
#define test(x,w) (x&two(w))
#define sz(v) (int)v.size()
#define all(c) c.begin(),c.end() 
#define clr(buf,val) memset(buf,val,sizeof(buf))
#define rep(i,l,r) for(int i=(l);i<(r);i++)
#define repv(i,v)  for(int i=0;i<(int)v.size();i++)
#define repi(it,c) for(typeof(c.begin()) it=c.begin();it!=c.end();++it)
//------------------------------------------------------------------------

vector<int>::iterator it;
void insert(vector<int> &v,int val){ //插入
	it=lower_bound(v.begin(),v.end(),val);
	v.insert(it,val);
}
void remove(vector<int> &v,int val){ //删除
	it=lower_bound(v.begin(),v.end(),val);
	if( it!=v.end() && *it == val ) v.erase(it);
}


int data[550000], cnt;

void insert(int val){
	for(int i=cnt-1;;i--){
		if( i==-1 ){
			data[0]=val; break;
		}
		if( data[i]>val ) data[i+1]=data[i];
		else {
			data[i+1]=val;
			break;
		}
	}
	cnt++;
}

int main(){
	VI v;
	cnt=0;
	rep(i, 0, 50000) {
		v.PB(i);
		data[cnt++]=i;
	}
	rep(i, 150000, 200000) {
		v.PB(i);
		data[cnt++]=i;
	}
	int t=clock();
	rep(i, 50000, 150000) insert(v, i);
	printf("%d ms\n", clock()-t);
	t=clock();
	rep(i, 50000, 150000) insert(i);
	printf("%d ms\n", clock()-t);
	//rep(i, 50000, 150000) remove(v, i);
}


*/



