/*
��catalan����n� 
1,	C(n)=(2n)!/ (n! * (n+1)! )
2,	C(n)=(4*n-2)/(n+1) * C(n-1)  �� C(0)=1;
O(n)���㷨

���⣺
��ǰn���ģm
�Ƚ�m�ֽ���������Ȼ��(4 * i - 2) �� (i + 1) �� c[i - 1]���ֳ����ݣ�һ������m���ʵģ�����һ��������m���������������ɵġ�Ȼ��ֱ�ά�������ݡ�ǰ��ֻҪ�á�������ά���ͺã�����ǰ�ߣ����ں�m�����ˣ�������������Ԫ��Ȼ����(4*i - 2)��c[i - 1]�ĵ�һ�ݱ߳˱�ģ�����ں��ߣ�������m������������ά�������c[i]���ǰ����������е����˵���һ����߳˱�ģm��ע����ܳ�int�ĵط���
*/
#define MAXN 200005  // 2*n
typedef long long int64;
int isp[MAXN], num[MAXN], tmp[MAXN];

void init_isp() {
    memset(isp, 0, sizeof(isp));
    for (int i = 2; i * i < MAXN; i++) {
        if (isp[i]) continue;
        for (int j = i * i; j < MAXN; j += i)
            isp[j] = i;
    }
    //printf("init\n");
}

void resolve(int *num, int n) { //resolve n! to num array
    for (int i = 0; i <= n; i++) num[i] = 1;
    for (int i = n; i >= 4; i--) {
        if (isp[i] == 0) continue;
        num[isp[i]] += num[i];
        num[i / isp[i]] += num[i];
        num[i] = 0;
    }
}

int cal_catalan(int n, int mod) {//����catalan����n����ģmod
    static bool init = false;
    if (!init) init_isp(), init = true;
    resolve(num, 2 * n);
    resolve(tmp, n);
    for (int i = 2; i <= n; i++) num[i] -= tmp[i];
    resolve(tmp, n + 1);
    for (int i = 2; i <= n + 1; i++) num[i] -= tmp[i];
    int ret = 1;
    for (int i = 2; i <= 2 * n; i++) {
        for (int j = 1; j <= num[i]; j++)
            ret = (int64) ret * i % mod;
    }
    return ret;
}