/**
 * 判断图中是否存在环
    Description
    有一个包含 N 个顶点，M 条边的有向图，以及提供该图是无向图还是有向图，如果I == 0则是有向图，I == 1则是无向图。


    Input
    // N 表示顶点的个数，M表示边的个数。I 表示是否为无向图，如果I == 1则是无向图，如果I == 0则是有向图。（0 < N <= 100, 0 < M <= 4000)。接下来 M 行代表边输入两个正整数 A、B（0 < A, B <= N）。代表有一条从 A 指向 B 的边。


    Output
    如果该图存在环，则输出字符串 `Yes`，否则输出 `No`
    
    这道题目是 2018 年应届生在面试阿里巴巴手机淘宝 iOS 客户端一职时所遇到的。当时的场景是口术思路，并没有要求代码实现。

    题解: 
    https://blog.csdn.net/u010040029/article/details/52861473
 * 
*/

#include <iostream>
#include <stdio.h>
#include <string> 

using namespace std;

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

#define maxVertex 100 //定义邻接举证的最大定点数
int visited[maxVertex];//通过visited数组来标记这个顶点是否被访问过，0表示未被访问，1表示被访问 2 
int DFS_Count;//连通部件个数，用于测试无向图是否连通，DFS_Count=1表示只有一个连通部件，所以整个无向图是连通的
int idCircled; // 有向图是否有环标记

//图的邻接矩阵表示结构
typedef struct
{
	char v[maxVertex];//图的顶点信息
	int e[maxVertex][maxVertex];//图的顶点信息
	int vNum;//顶点个数
	int eNum;//边的个数
    int undirected; // 是否是无向图
}graph;

class Solution {
public:
    bool circleInGraph(graph *g) {
        if (g -> undirected){
            return circleInUndirectedGraph(g);
        }
        return circleInDirectedGraph(g);
    }

    // 1 - 2 - 3;
    /*
    * n 顶点个数
    * m 边的个数
    */
    bool circleInUndirectedGraph(graph *g) {
        //边的数量不小于顶点的数量, 则可以直接判定有环
        if(g -> eNum >= g -> vNum){
            return true;
        }
        //
        DFS_Count = 0;
        for (int i = 1; i <= g->vNum; i++) {
            visited[i] = 0;
        }
        for (int i = 1; i <= g->vNum; i++)
        {
            if (visited[i] == 0)
            {
                DFS_Count++;
                dfsUndirected(g,i);
            }
        }

        // 判定
        bool circle = DFS_Count + g->eNum > g->vNum;
        return circle;
    }

     void dfsUndirected(graph *g,int vertex) {
        // 更新未访问
        
        visited[vertex] = 1;
        for (int j = 1; j <= g -> vNum; j++) {
            if(g->e[vertex][j] != 0 && visited[j] == 0){
                dfsUndirected(g,j);
            }
        }
    }

    bool circleInDirectedGraph(graph *g) {
        idCircled = false;
        for (int i = 1; i <= g->vNum; i++) {
            visited[i] = 0;
        }
        for (int i = 1; i <= g->vNum; i++)
        {
            if (idCircled == false && visited[i] == 0)
            {
                dfsDirected(g,i);
            }
        }
        return idCircled;
    }

    void dfsDirected(graph *g,int vertex) {
        // 更新未访问
        visited[vertex] = -1;
        for (int j = 1; j <= g -> vNum; j++) {
            if(g->e[vertex][j] != 0){
                if (visited[j] == -1) {
                    idCircled = true;
                    break;
                } else {
                    dfsDirected(g,j);
                }
            }
        }
        visited[vertex] = 1;
    }

   
};

/**
 * n 顶点数
 * m 边的数量
 * 
*/
graph* createGraph(int n, int m,bool undirected){
    graph * g = (graph *)malloc(sizeof(graph));
    g -> vNum = n;
    g -> eNum = m;
    g -> undirected = undirected;
    // 初始化默认数据, 从1开始是因为 顶点的数据是连续的正整数
    for (int i = 1; i <= n; i++) {
        // 默认顶点数据
        g -> v[i] = 0;
        for (int j = 1; j <= m; j++){
            // 默认边的数据
            g -> e[i][j] = 0;
        }
    }
    // 填充边的数据
    int i, j;
    for (int k = 1; k <= m; k ++) {
        scanf("%d%d",&i,&j);
        g ->e[i][j] = 1;
        // 无向图的处理
        if (undirected){ g ->e[j][i] = 1; }
    }

    return g;
}

int main () {
    int n , m ;// 顶点的个数 n ; 边的个数 m
    int i;
	// cin io 耗时较多, 可以用 scanf
    while (~scanf("%d%d%d",&n,&m,&i)) {
        graph *g = createGraph(n,m,i);
        cout << "图的顶点数: " << n << " ,边数: " << m << endl;
        string ret = Solution().circleInGraph(g) ? "Yes" : "No";
        cout << ret  << endl;
    }
}
