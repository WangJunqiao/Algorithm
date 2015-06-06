//最长回文
//The Manacher Algorithm 求一个字符串中以某个位置为中心的最大半径
//利用的要点是 *m*****I*****c* m是c的对称点,那么算c的半径的时候,(*m*) 和 (*c*)是对称的  
#define maxn 200100
int rado[maxn]; //rado[i],长度奇数的   max k{[i-k,...,i-1,  i  ,i+1,...,i+k] }
int rade[maxn]; //rade[i],长度为偶数的 max k{[i-k-1,...,i-1,i,   i+1,i+2,...,i+k] }
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
            int mir = I - (i - I); //mir 镜像对称点
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
}//**************模板结束************************