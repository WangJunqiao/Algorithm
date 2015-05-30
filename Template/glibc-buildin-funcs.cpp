/*
int __builtin_clz (unsigned int x)
Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.
返回左起第一个‘1’之前0的个数。

int __builtin_ctz (unsigned int x)
Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.
返回右起第一个‘1’之后的0的个数。

int __builtin_popcount (unsigned int x)
Returns the number of 1-bits in x.
返回‘1’的个数。
 * */

#include <iostream>

using namespace std;

int main() {
    cout << __builtin_clz(1) << endl; //统计二进制左边0的个数
    cout << __builtin_clz(0) << endl;

    cout << __builtin_ctz(4) << endl; //统计二进制右边0的个数
    cout << __builtin_ctz(0) << endl;

    cout << __builtin_popcount(0) << endl; //统计1的个数
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