//�����
//The Manacher Algorithm ��һ���ַ�������ĳ��λ��Ϊ���ĵ����뾶
//���õ�Ҫ���� *m*****I*****c* m��c�ĶԳƵ�,��ô��c�İ뾶��ʱ��,(*m*) �� (*c*)�ǶԳƵ�  
#define maxn 200100
int rado[maxn]; //rado[i],����������   max k{[i-k,...,i-1,  i  ,i+1,...,i+k] }
int rade[maxn]; //rade[i],����Ϊż���� max k{[i-k-1,...,i-1,i,   i+1,i+2,...,i+k] }
void Manacher(char *str, int len) { //index base 0
    int I = 0, R = 0, r = 0;
    for (int i = 0; i < len;) {
        while (i - (r + 1) >= 0 && i + (r + 1) < len && str[i - (r + 1)] == str[i + (r + 1)]) r++;
        rado[i] = r;
        if (i + r > I + R) I = i, R = r;
        i++;
        if (I + R < i) {
            r = 0;
            continue;
        } else {
            int mir = I - (i - I); //mir ����ԳƵ�
            r = min(rado[mir], I + R - i);
        }
    }
    I = 0, R = 0, r = 0;
    for (int i = 0; i < len;) {
        while (i - r >= 0 && i + 1 + r < len && str[i - r] == str[i + 1 + r]) r++;
        rade[i] = r;
        if (i + r > I + R) I = i, R = r;
        i++;
        if (I + R <= i) {
            r = 0;
            continue;
        } else {
            int mir = I - (i - I);
            r = min(rade[mir], I + R - i);
        }
    }
}//**************ģ�����************************