#include <iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

char str[1000005];
char str2[2000005];

//格点计数,比较恶心的-_-
int main() {
    while (scanf(" %s", str) != EOF) {
        int len = strlen(str);
        int len2 = 0;
        for (int i = 0; i < len; i++) {
            if ((str[i] - '0') % 2 == 0) {
                str2[len2++] = str[i];
            } else {
                if (str[i] == '1') {
                    str2[len2++] = '2';
                    str2[len2++] = '0';
                } else if (str[i] == '3') {
                    str2[len2++] = '4';
                    str2[len2++] = '2';
                } else if (str[i] == '5') {
                    str2[len2++] = '6';
                    str2[len2++] = '4';
                } else {
                    str2[len2++] = '0';
                    str2[len2++] = '6';
                }
            }
        }
        __int64 sum = 0;
        int x = 0, y = 0, last = str2[len2 - 1] - '0';
        for (int i = 0; i < len2; i++) { //下面这段的处理值得注意下!!
            if (str2[i] == '0') {
                if (last == 4) sum++;
                else if (last == 6 || last == 0)sum -= (y - 1);
                x++;
            } else if (str2[i] == '2') {
                if (last == 0)sum -= (y - 1);
                else if (last == 6) sum -= (y - 1);
                y++;
            } else if (str2[i] == '4') {
                if (last == 0) sum++;
                else if (last == 2 || last == 4) sum += y;
                x--;
            } else {
                if (last == 2 || last == 4) sum += y;
                y--;
            }
            last = str2[i] - '0';
        }
        if (sum < 0) sum = -sum;
        cout << sum << endl;
    }
}