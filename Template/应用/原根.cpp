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
//��1~P���ж��ٶ�����x<=y,��x^x+y^y=0 (mod P), P������

/*
ԭ��Primitive Root����
������m����������a����������aģm�Ľ׵��ڦ�(m)�����aΪģm��һ��ԭ���������Ц�(m)��ʾm��ŷ��������
��������һ����g����P��˵��ԭ������ôg^i mod P�Ľ��������ͬ,���� 1<g<P, 0<i<P,��ôg���Գ�Ϊ��P��һ��ԭ��,������׾���g^(P-1) = 1 (mod P)���ҵ�ָ��ΪP-1��ʱ�����.(����P������).
��������˵��g^i mod p �� g^j mod p ��pΪ������
��������i��j��i, j���1��(p-1)֮��
������gΪp��ԭ����
������ԭ��Ŀǰ������ֻ���Ǵ�2��ʼö�٣�Ȼ�����ж�g^(P-1) = 1 (mod P)�Ƿ��ҵ�ָ��ΪP-1��ʱ�����
����������ԭ��һ�㶼�������Կ��Ա����õ�.
*/

#define maxn 1000006
int val[maxn];
int rm[maxn];
int ge[maxn];
int P;


int getPrimitiveRoot(int P) {//����������������ԭ��
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
����P��������������Inv(i) -> j, ����j�� [1.. P-1]�ڵ�һ������
����Inv()���������һһӳ��ģ�
����һ��j, ����ֻ����һ��i,ʹ��Inv(i) = j ( mod P)
����һ��i, Inv(i) = j (mod P), ֻ��Ӧһ��j
(֤����ԭ����ŷ������)
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