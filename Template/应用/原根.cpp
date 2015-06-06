//fzu 2031
#include <vector>
//#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

//fzu2031
//求1~P内有多少对整数x<=y,有x^x+y^y=0 (mod P), P是素数

/*
原根Primitive Root。　
　　设m是正整数，a是整数，若a模m的阶等于φ(m)，则称a为模m的一个原根。（其中φ(m)表示m的欧拉函数）
　　假设一个数g对于P来说是原根，那么g^i mod P的结果两两不同,且有 1<g<P, 0<i<P,那么g可以称为是P的一个原根,归根到底就是g^(P-1) = 1 (mod P)当且当指数为P-1的时候成立.(这里P是素数).
　　简单来说，g^i mod p ≠ g^j mod p （p为素数）
　　其中i≠j且i, j介於1至(p-1)之间
　　则g为p的原根。
　　求原根目前的做法只能是从2开始枚举，然后暴力判断g^(P-1) = 1 (mod P)是否当且当指数为P-1的时候成立
　　而由于原根一般都不大，所以可以暴力得到.
*/

#define maxn 1000006
int val[maxn];
int rm[maxn];
int ge[maxn];
int P;


int getPrimitiveRoot(int P) {//必须是奇素数才有原根
    for (int i = 2; ; i++) {
        int rem = 1;
        bool suc = true;
        for (int j = 1; j < P - 1; j++) {
            rem = (long long) rem * i % P;
            if (rem == 1) {
                suc = false;
                break;
            }
        }
        if (suc) return i;
    }
}

/*
由于P是奇素数，所以Inv(i) -> j, 其中j是 [1.. P-1]内的一个数字
并且Inv()这个函数是一一映射的：
对于一个j, 有且只存在一个i,使得Inv(i) = j ( mod P)
对于一个i, Inv(i) = j (mod P), 只对应一个j
(证明用原根和欧拉定理)
*/


int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d", &P);
        if (P == 2) {
            cout << 1 << endl;
            continue;
        }
        int r = getPrimitiveRoot(P), rem = 1;
        for (int i = 1; i <= P; i++) ge[i] = 0;
        //continue;
        for (int i = 1; i < P; i++) {
            rem = (long long) rem * r % P;
            val[i] = rem;
            rm[rem] = i;
            //cout<<rem<<' '<<i<<endl;
            //mi[rem]=i;
            int t = (long long) i * rem % (P - 1);
            //cout<<"t: "<<t<<endl;
            if (t == 0)t = P - 1;
            ge[t]++;
        }
        int ans = 0;
        for (int i = 1; i < P; i++) {
            ///if( i>P/2 ) break;
            //if( ge[i] && ge[P-i])
            ans += ge[i] * ge[rm[P - val[i]]];
        }
        printf("%d\n", ans / 2);
    }
}