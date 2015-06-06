//����С��ansʹ�ô���k����:  z1/m1 <= k/ans <z2/m2 ............
//�༴���ڸ���������double,����С��һ������ans,ʹ��ans*low��ans*high֮�����һ������
//����ŷ����õ��㷨.......(��ͣ�ط�ת,ȡ������)

#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#include<map>
#include<iostream>
#include<queue>
#include<vector>
#include<string>

using namespace std;

//flag��ʾ=���ı�,false��>=,true��<=
void dfs(long long z1, long long m1, long long z2, long long m2, long long &k, long long &ans, bool flag) {
    if (z1 < m1 && m2 < z2) { //�����ٷ�ת��(ȡ����������)
        if (z1 == 0 && flag == false) k = 0;
        else k = 1;
        ans = 1;
        return;
    }
    if (z1 < m1) {
        dfs(m2, z2, m1, z1, ans, k, !flag);
        return;
    }
    long long p = z1 / m1;
    long long _k, _ans;
    dfs(z1 - m1 * p, m1, z2 - m2 * p, m2, _k, _ans, flag);
    ans = _ans;
    k = p * ans + _k;
    return;
}

long long mul[111];

int main() {
    int Te = 1;
    mul[0] = 1;
    for (int i = 1; i <= 12; i++) mul[i] = mul[i - 1] * 10;
    long long A;
    char *B;
    string s;
    while (cin >> s) {
        if (s[0] == '-') break;

        A = s[0] - '0';
        B = (char *) s.substr(1).c_str();

        int lenB = strlen(B + 1);

        long long t = mul[lenB]; //cout<<" t "<<t<<endl;
        long long BB = 0;
        for (int i = 1; i <= lenB; i++) BB = 10 * BB + B[i] - '0';
        t *= 10;
        long long k, ans = 0;
        long long z1 = A * t + 10 * BB - 5;
        long long z2 = A * t + 10 * BB + 5;
        dfs(z1, t, z2, t, k, ans, false);

        printf("Case %d: %lld\n", Te++, ans);
    }
}