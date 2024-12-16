// // // 设计合适的存储结构，用克鲁斯卡尔算法求网的最小生成树。
// # include <stdio.h>
// # define MAXVEX 100
// # define MAXEDGE 1000


// void MiniSpanTree_Kruskal(Graph G)
// {
//     int i, n, m;
//     Edge edge[MAXEDGE];
//     int parent[MAXVEX];
// //将邻接矩阵 G 转换成边集数组
//     for(i=0;i<G.numVertexes;i++)
//     {
//         parent[i] = 0;
//         for(i = 0;i<G.numEdges;i++)
//         {
//             n = Find(parent, edges[i].begin);
//             m = Find(parent, edges[i].end);
//             if(n!= m)
//             {
//                 parent[n] = m;
//                 printf("(%d, %d), %d", edges[i].begin, edges[i].end, edges[i].weight);
//             }
//         }
//     }
// }

// int Find(int *parent, int f)
// {
//     while(parent[f]>0)
//     {
//         f = parent[f];
//     }
//     return f;
// }



#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 100   // 最大顶点数
#define MAXEDGE 1000 // 最大边数

typedef struct {
    int begin, end; // 边的两个顶点
    int weight;     // 边的权重
} Edge;

typedef struct {
    int numVertexes;    // 顶点数
    int numEdges;       // 边数
    int arc[MAXVEX][MAXVEX]; // 邻接矩阵
} Graph;

// 查找集合根节点
int Find(int *parent, int f) {
    while (parent[f] > 0) {
        f = parent[f];
    }
    return f;
}

// Kruskal 最小生成树算法
void MiniSpanTree_Kruskal(Graph G) {
    int parent[MAXVEX] = {0}; // 初始化父节点数组
    Edge edges[MAXEDGE];      // 边集数组
    int edgeCount = 0;

    // 将邻接矩阵转换为边集数组
    for (int i = 0; i < G.numVertexes; i++) {
        for (int j = i + 1; j < G.numVertexes; j++) {
            if (G.arc[i][j] != 0 && G.arc[i][j] != INT_MAX) { // 有边且非无穷大
                edges[edgeCount].begin = i;
                edges[edgeCount].end = j;
                edges[edgeCount].weight = G.arc[i][j];
                edgeCount++;
            }
        }
    }

    // 按边的权值升序排序
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Kruskal 算法核心
    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 0; i < edgeCount; i++) {
        int n = Find(parent, edges[i].begin);
        int m = Find(parent, edges[i].end);

        if (n != m) { // 如果不在同一集合中，加入最小生成树
            parent[n] = m;
            printf("(%d, %d) -> %d\n", edges[i].begin, edges[i].end, edges[i].weight);
        }
    }
}
// 主函数
int main() {

    // 测试代码
    Graph G;
    G.numVertexes = 6; // 顶点数
    G.numEdges = 10;   // 边数

    // 初始化邻接矩阵
    for (int i = 0; i < MAXVEX; i++) {
        for (int j = 0; j < MAXVEX; j++) {
            G.arc[i][j] = (i == j) ? 0 : INT_MAX; // 自己到自己权重为0，其余为无穷大
        }
    }

    // 添加边及权值
    G.arc[0][1] = 6;
    G.arc[1][0] = 6;
    G.arc[0][2] = 1;
    G.arc[2][0] = 1;
    G.arc[0][3] = 5;
    G.arc[3][0] = 5;
    G.arc[1][2] = 5;
    G.arc[2][1] = 5;
    G.arc[2][3] = 5;
    G.arc[3][2] = 5;
    G.arc[1][4] = 3;
    G.arc[4][1] = 3;
    G.arc[2][4] = 6;
    G.arc[4][2] = 6;
    G.arc[2][5] = 4;
    G.arc[5][2] = 4;
    G.arc[3][5] = 2;
    G.arc[5][3] = 2;
    G.arc[5][4] = 6;
    G.arc[4][5] = 6;
    
    // 无向图对称处理
    for (int i = 0; i < G.numVertexes; i++) {
        for (int j = 0; j < G.numVertexes; j++) {
            if (G.arc[i][j] != INT_MAX) {
                G.arc[j][i] = G.arc[i][j];
            }
        }
    }

    MiniSpanTree_Kruskal(G);
    return 0;
}
