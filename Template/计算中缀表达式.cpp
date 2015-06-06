//zjut ---DD
//通过校OJ1034测试
//PS: vc6 里string头文件中getline函数的定义有bug..........
#include<iostream>
#include<string.h>
#include<string>
#include<stack>
#include<map>

using namespace std;

map<char, int> mp;

void preprocess()//出现新的操作符可以在这里添加，值的大小为优先级的高低
{
    mp['|'] = 0;//位或运算
    mp['&'] = 0;//位与运算
    mp['+'] = 1;
    mp['-'] = 1;
    mp['*'] = 2;
    mp['/'] = 2;
    mp['%'] = 2;//取余运算
    mp['^'] = 3;//乘方运算
    mp['('] = 10000;//')'特殊考虑的
}

void cal(stack<int> &val_stack, stack<char> &ope_stack) {
    int val1, val2, ans;
    char ch;

    val1 = val_stack.top();
    val_stack.pop();
    val2 = val_stack.top();
    val_stack.pop();
    ch = ope_stack.top();
    ope_stack.pop();

    switch (ch) {
        case '&':
            ans = val2 & val1;
            break;
        case '|':
            ans = val2 | val1;
            break;
        case '+':
            ans = val2 + val1;
            break;
        case '-':
            ans = val2 - val1;
            break;
        case '*':
            ans = val2 * val1;
            break;
        case '/':
            ans = val2 / val1;
            break;
        case '%':
            ans = val2 % val1;
            break;
        case '^':
            ans = 1;
            while (val1)//整数幂的二分加速，(⊙o⊙)…貌似这里数据太小，米用~~~
            {
                if (val1 & 1)
                    ans *= val2;
                val2 *= val2;
                val1 >>= 1;
            }
            break;
    }
    val_stack.push(ans);
    return;
}

int calculate(string &temp) {

    int len = temp.length(), ind = 0, i;
    for (i = 0; i < len; i++) //过滤空格
        if (temp[i] != ' ')
            temp[ind++] = temp[i];
    len = ind;


    if (temp[0] == '-') {
        temp = '0' + temp;
        len++;
    }

    stack<int> val_stack;
    stack<char> ope_stack;
    for (i = 0; i < len; i++) {
        if (temp[i] == '(') {
            ope_stack.push(temp[i]);
            continue;
        }
        else if (temp[i] == ')') {
            while (ope_stack.top() != '(')
                cal(val_stack, ope_stack);
            ope_stack.pop();//弹出'('
        }
        else if (isdigit(temp[i])) {
            int val = 0;
            while (i < len && isdigit(temp[i])) {
                val = 10 * val + (temp[i] - '0');
                i++;
            }
            i--;//返回一个
            val_stack.push(val);
        }
        else {
            char ope = temp[i];
            while (!ope_stack.empty() && ope_stack.top() != '(' && mp[ope_stack.top()] >= mp[ope])
                cal(val_stack, ope_stack);
            ope_stack.push(ope);
        }
    }
    while (!ope_stack.empty())
        cal(val_stack, ope_stack);
    return val_stack.top();
}

int main() {
    preprocess();//这里面定义运算的优先级

    string temp;
    cout << "请输入中缀表达式:\n";
    while (getline(cin, temp)) {
        int ans = calculate(temp);

        cout << "the result is " << ans << endl;
    }
}