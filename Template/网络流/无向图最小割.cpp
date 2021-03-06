/*
求无向图的最小割
最小割集◎Stoer-Wagner算法
一个无向连通网络，去掉一个边集可以使其变成两个连通分量则这个边集就是割集；最小割集当然就权和最小的割集。

一、可以用最小切割最大流定理：
1.min=MAXINT,确定一个源点
2.枚举汇点
3.计算最大流，并确定当前源汇的最小割集，若比min小更新min
4.转到2直到枚举完毕
5.min即为所求输出min
不难看出复杂度很高：枚举汇点要O(n)，最短增广路最大流算法求最大流是O((n^2)m)复杂度，在复杂网络中O(m)=O(n^2)，算法总复杂度 就是O(n^5)；哪怕采用最高标号预进流算法求最大流O((n^2)(m^0.5))，算法总复杂度也要O(n^4)
所以用网络流算法求解最小割集复杂度不会低于O(n^4)。
－－－－－－－－－
二、prim算法不仅仅可以求最小生成树，也可以求“最大生成树”。最小割集Stoer-Wagner算法就是典型的应用实例。
求解最小割集普遍采用Stoer-Wagner算法，不提供此算法证明和代码，只提供算法思路：
1.min=MAXINT，固定一个顶点P（一般是顶点1）
2.从点P用类似prim的s算法扩展出“最大生成树”，记录最后扩展的顶点（设为 Vt）和最后扩展的边(设为Et)
3.计算最后扩展到的顶点的切割值（即与此顶点相连的所有边权和），若比min小更新min
4.合并最后扩展的那条边的两个端点为一个顶点（当然他们的边也要合并  缩点 缩边
5.转到2，合并N-1次后结束
6.min即为所求，输出min
prim本身复杂度是O(n^2)，合并n-1次，算法复杂度即为O(n^3)
如果在prim中加堆优化，复杂度会降为O((n^2)logn) 　　
算法在做”最大生成树”时更新的不是普通意义上的最大边, 而是与之相连的边的权值和, 当所有边都是单位权值时就是累计度.
*/
//pku 2914
#include <iostream>

using namespace std;
int mat[600][600];

int Mincut(int n) { //无向图最小割  base 0
    int res = 1 << 29, node[600], dist[600];
    bool visit[600];
    int i, prev, maxj, j, k;
    for (i = 0; i < n; i++)    //保存顶点 ，固定顶点为0
        node[i] = i;
    while (n > 1) {
        maxj = 1;
        for (i = 1; i < n; i++) {
            dist[node[i]] = mat[node[0]][node[i]];     //初始化距离数组dist[]
            if (dist[node[i]] > dist[node[maxj]])    //寻找最大距离——求最大生成树
                maxj = i;
        }
        prev = 0;
        memset(visit, false, sizeof(visit));
        visit[node[0]] = true;
        //求最大生成树，并进行最小割操作。
        for (i = 1; i < n; i++) {
            if (i == n - 1) { //只剩最后一个没加入集合的点，更新最小割
                res = __min(res, dist[node[maxj]]);
                for (k = 0; k < n; k++) //合并最后一个点以及推出它的集合中的点
                    mat[node[k]][node[prev]] = (mat[node[prev]][node[k]] += mat[node[k]][node[maxj]]);
                node[maxj] = node[--n]; //缩点后的图
            }
            visit[node[maxj]] = true;    //标记已经访问
            prev = maxj;
            maxj = -1;
            for (j = 1; j < n; j++) {
                if (!visit[node[j]]) { //将上次求的maxj加入集合，合并与它相邻的边到割集
                    dist[node[j]] += mat[node[prev]][node[j]];   //dist[]保存的是一个积累量。
                    if (maxj == -1 || dist[node[maxj]] < dist[node[j]])
                        maxj = j;    //保存更新值
                }
            }
        }
    }
    return res;
}

int main() {
    int n, m, a, b, v;
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(mat, 0, sizeof(mat));
        while (m--) {
            scanf("%d%d%d", &a, &b, &v);
            mat[a][b] += v;
            mat[b][a] += v;
        }
        printf("%d\n", Mincut(n));
    }
    return 0;
}