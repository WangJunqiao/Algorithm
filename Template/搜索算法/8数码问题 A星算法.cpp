/*
problem : 8��������
Algorithm: A*�㷨
Author: �����0801 ������  2010.11.27
IDE: Visual Studio 2010
*/
#include<iostream>
#include<vector>
#include<queue>
#include<string>

using namespace std;

struct PII {
    int r, c;

    PII(int _r = 0, int _c = 0) : r(_r), c(_c) { };
};               //���ڴ�������

struct EIGHT {    //�����״̬��
    int _d[3][3];
    PII _z;    //0������
    int g, h;
    vector<int> path; //�ѵ����״̬��·��

    int getRev() const { //������
        int a[8], ind = 0, i, j, Rev = 0;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (_d[i][j] != 0)
                    a[ind++] = _d[i][j];
            }
        }
        for (i = 1; i < 8; i++) {
            for (j = 0; j < i; j++)
                if (a[j] > a[i])
                    Rev++;
        }
        return Rev;
    }

    bool getNext(int dir, EIGHT &ns) {//�ƶ��������ƶ��Ƿ�ɹ�(��һ��״̬�������д���)
        memcpy(ns._d, _d, sizeof(_d));
        ns.path = path;
        ns._z = _z;
        int r = _z.r, c = _z.c, nr, nc;
        if (dir == 0) {                       // down
            if (_z.r == 2) return false;
            nr = r + 1, nc = c;
        } else if (dir == 1) {                // left
            if (_z.c == 0) return false;
            nr = r, nc = c - 1;
        } else if (dir == 2) {               // right
            if (_z.c == 2) return false;
            nr = r, nc = c + 1;
        } else {                             // up
            if (_z.r == 0) return false;
            nr = r - 1, nc = c;
        }
        swap(ns._d[r][c], ns._d[nr][nc]);
        ns._z = PII(nr, nc);
        ns.path.push_back(dir);
        return true;
    }

    int getH(EIGHT &des) { //���ۺ���2
        PII b[8];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (_d[i][j])
                    b[_d[i][j] - 1] = PII(i, j);
            }
        }
        int ret = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (des._d[i][j]) {
                    int v = des._d[i][j];
                    ret += abs(i - b[v - 1].r) + abs(j - b[v - 1].c);
                }
            }
        }
        return ret;
    }

    /*int getH(EIGHT &des){ //���ۺ���1
        int ret=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if( _d[i][j]==0 ) continue;
                if( _d[i][j] != des._d[i][j] ){ //����λ��
                    ret++;
                }
            }
        }
        return ret;
    }*/

    void init(int *d) { //�������ʼ��
        for (int i = 0; i < 9; i++) {
            _d[i / 3][i % 3] = d[i];
            if (d[i] == 0) {
                _z.r = i / 3, _z.c = i % 3;
            }
        }
        this->path.clear();
    }

    int getHash() {     //ȫ���е�������ϣ,���Ӷ�O(n^2),�����õ�
        int a[9];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) a[3 * i + j] = _d[i][j];
        }
        int ret = 0, mul = 1;
        for (int i = 1; i < 9; i++) {
            int rev = 0;
            for (int j = 0; j < i; j++) if (a[j] > a[i]) rev++;
            ret += mul * rev;
            mul *= (i + 1);
        }
        return ret;
    }

    void print(int step) { //��ӡ8����
        printf("step %d:\n%d %d %d\n%d %d %d\n%d %d %d\n", step,
               _d[0][0], _d[0][1], _d[0][2], _d[1][0], _d[1][1],
               _d[1][2], _d[2][0], _d[2][1], _d[2][2]);
    }

    bool operator<(const EIGHT &b) const { //���ȶ����еıȽ�
        return g + h > b.g + b.h;
    }

    bool operator==(const EIGHT &b) const { //�����,����ֻҪ3*3��board��Ⱦ�ok��
        return memcmp(_d, b._d, 9 * sizeof(int)) == 0;
    }

} src, des;

priority_queue<EIGHT> open;

//queue< EIGHT > close;
void trace(vector<int> path) {
    EIGHT s = src, t;
    int step = 0;
    s.print(step++);
    for (int i = 0; i < (int) path.size(); i++) {
        cout << "--->" << endl;
        s.getNext(path[i], t);
        t.print(step++);
        s = t;
    }
}

bool hash[500000];

void Astar() {
    if (src.getRev() % 2 != des.getRev() % 2) {//�н�
        puts("unSolvable");
        return;
    }
    vector<int> path;
    fill(hash, hash + 500000, false);
    while (!open.empty()) open.pop();
    //while( !close.empty()) close.pop();
    src.g = 0, src.h = src.getH(des);
    open.push(src);

    int searched = 0, visited = 0;
    while (true) {
        EIGHT cur = open.top(), nxt;
        open.pop();
        if (cur == des) {
            puts("I find it!");
            path = cur.path;

            break;
        }
        for (int i = 0; i < 4; i++) { //0��4�������ƶ�
            if (cur.getNext(i, nxt)) {
                nxt.g = 0;
                nxt.g = cur.g + 1;
                nxt.h = nxt.getH(des);//�ĳ�nxt.g=0������ͨ�Ĺ�����
                //nxt.h=0;
                int hh = nxt.getHash();
                if (hash[hh]) continue;
                hash[hh] = true;
                open.push(nxt);
                visited++;   //���ʹ��Ľڵ����+1
            }
        }
        searched++; //�������Ľڵ����+1
        //cout<<searched<<endl;
    }
    trace(path);         //��ӡ������·��
    printf("���·��%d,������%d��״̬,������%d��״̬\n", path.size(), visited, searched);
}

int main() {
    int d[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    des.init(d);
    while (cin >> d[0]) {
        for (int i = 1; i < 9; i++) cin >> d[i];
        src.init(d);
        Astar();
    }
}
/*
2 1 0
3 4 5
6 7 8
I find it!
step 0:
2 1 0
3 4 5
6 7 8
--->
step 1:
2 0 1
3 4 5
6 7 8
--->
step 2:
2 4 1
3 0 5
6 7 8
--->
step 3:
2 4 1
3 7 5
6 0 8
--->
step 4:
2 4 1
3 7 5
6 8 0
--->
step 5:
2 4 1
3 7 0
6 8 5
--->
step 6:
2 4 0
3 7 1
6 8 5
--->
step 7:
2 0 4
3 7 1
6 8 5
--->
step 8:
2 7 4
3 0 1
6 8 5
--->
step 9:
2 7 4
0 3 1
6 8 5
--->
step 10:
0 7 4
2 3 1
6 8 5
--->
step 11:
7 0 4
2 3 1
6 8 5
--->
step 12:
7 3 4
2 0 1
6 8 5
--->
step 13:
7 3 4
2 1 0
6 8 5
--->
step 14:
7 3 0
2 1 4
6 8 5
--->
step 15:
7 0 3
2 1 4
6 8 5
--->
step 16:
7 1 3
2 0 4
6 8 5
--->
step 17:
7 1 3
0 2 4
6 8 5
--->
step 18:
0 1 3
7 2 4
6 8 5
--->
step 19:
1 0 3
7 2 4
6 8 5
--->
step 20:
1 2 3
7 0 4
6 8 5
--->
step 21:
1 2 3
7 8 4
6 0 5
--->
step 22:
1 2 3
7 8 4
0 6 5
--->
step 23:
1 2 3
0 8 4
7 6 5
--->
step 24:
1 2 3
8 0 4
7 6 5
���·��24,������2368��״̬,������1472��״̬

*/

