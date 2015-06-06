//�����͸�˹��Ԫ,�����Ƿ���ȷ����
double a[MAXN][MAXN], x[MAXN], b[MAXN];

bool gauss() {
    for (int i = 0; i < n; i++) { //�°��ȫ����0
        double m = abs(a[i][i]);   //ע��m�ĳ�ֵ
        index = i;
        for (int j = i + 1; j < n; j++) { //�ҵ�����ֵ����һ��
            if (abs(a[j][i]) > m) {
                m = abs(a[j][i]);
                index = j;
            }
        }
        if (m < eps)return false;  //�����ȫ��0ʱ�������޽�
        if (index != i) {
            swap(b[i], b[index]); //���������������н�����
            for (int k = 0; k < n; k++)
                swap(a[i][k], a[index][k]);
        }
        for (int k = i + 1; k < n; k++) { //�����ǵ�i��ȥ����k�У���k�е�0~i-1�Ѿ�ȫ��0����
            double d = a[k][i] / a[i][i]; //�������
            b[k] -= b[i] * d;
            for (int p = i; p < n; p++)
                a[k][p] -= a[i][p] * d;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++)
            b[i] -= x[j] * a[i][j];
        x[i] = b[i] / a[i][i];
    }
    return true;
}
