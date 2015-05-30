/*
int __builtin_clz (unsigned int x)
Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.
���������һ����1��֮ǰ0�ĸ�����

int __builtin_ctz (unsigned int x)
Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.
���������һ����1��֮���0�ĸ�����

int __builtin_popcount (unsigned int x)
Returns the number of 1-bits in x.
���ء�1���ĸ�����
 * */

#include <iostream>

using namespace std;

int main() {
    cout << __builtin_clz(1) << endl; //ͳ�ƶ��������0�ĸ���
    cout << __builtin_clz(0) << endl;

    cout << __builtin_ctz(4) << endl; //ͳ�ƶ������ұ�0�ĸ���
    cout << __builtin_ctz(0) << endl;

    cout << __builtin_popcount(0) << endl; //ͳ��1�ĸ���
    cout << __builtin_popcount(7) << endl;
    cout << __builtin_popcount(-1) << endl;
}
/*
output:
31
32
2
32
0
3
32
 * */