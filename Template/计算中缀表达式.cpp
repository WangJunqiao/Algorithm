//zjut ---DD
//ͨ��УOJ1034����
//PS: vc6 ��stringͷ�ļ���getline�����Ķ�����bug..........
#include<iostream>
#include<string.h>
#include<string>
#include<stack>
#include<map>

using namespace std;

map<char, int> mp;

void preprocess()//�����µĲ�����������������ӣ�ֵ�Ĵ�СΪ���ȼ��ĸߵ�
{
    mp['|'] = 0;//λ������
    mp['&'] = 0;//λ������
    mp['+'] = 1;
    mp['-'] = 1;
    mp['*'] = 2;
    mp['/'] = 2;
    mp['%'] = 2;//ȡ������
    mp['^'] = 3;//�˷�����
    mp['('] = 10000;//')'���⿼�ǵ�
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
            while (val1)//�����ݵĶ��ּ��٣�(��o��)��ò����������̫С������~~~
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
    for (i = 0; i < len; i++) //���˿ո�
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
            ope_stack.pop();//����'('
        }
        else if (isdigit(temp[i])) {
            int val = 0;
            while (i < len && isdigit(temp[i])) {
                val = 10 * val + (temp[i] - '0');
                i++;
            }
            i--;//����һ��
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
    preprocess();//�����涨����������ȼ�

    string temp;
    cout << "��������׺���ʽ:\n";
    while (getline(cin, temp)) {
        int ans = calculate(temp);

        cout << "the result is " << ans << endl;
    }
}