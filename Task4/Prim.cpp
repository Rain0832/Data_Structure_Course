// // 设计合适的存储结构，用普里姆算法求网的最小生成树。

#include <stdio.h>
#include <limits.h> // 提供 INT_MAX

#define MAX_VERTEX_NUM 100
#define VRType int
#define VertexType int

// 定义 CloseEdge 类型
typedef struct
{
    VertexType adjvex; // 当前最小生成树的顶点
    VRType lowcost;    // 顶点与最小生成树之间的最小边权
} CloseEdge;

// 全局变量
CloseEdge closedge[MAX_VERTEX_NUM];

// 图的定义（邻接矩阵）
typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];             // 顶点数组
    VRType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵
    int vexnum, arcnum;                          // 顶点数和边数
} Graph;

// 定位顶点在数组中的位置
int LocateVex(Graph G, VertexType u)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vexs[i] == u)
        {
            return i;
        }
    }
    return -1; // 顶点不存在
}

// 找到当前最小权值边对应的顶点位置
int minimum(CloseEdge closedge[], int vexnum)
{
    int min = INT_MAX;
    int k = -1;
    for (int i = 0; i < vexnum; i++)
    {
        if (closedge[i].lowcost != 0 && closedge[i].lowcost < min)
        {
            min = closedge[i].lowcost;
            k = i;
        }
    }
    return k;
}

// 普里姆算法求最小生成树
void MiniSpanTree_PRIM(Graph G, VertexType u)
{
    int k = LocateVex(G, u);
    if (k == -1)
    {
        printf("The starting vertex does not exist.\n");
        return;
    }

    // 初始化 closedge 数组
    for (int j = 0; j < G.vexnum; j++)
    {
        if (j != k)
        {
            closedge[j].adjvex = u;
            closedge[j].lowcost = G.arcs[k][j];
        }
        else
        {
            closedge[j].lowcost = 0; // 起始点本身
        }
    }

    // 主循环，生成最小生成树的边
    for (int i = 1; i < G.vexnum; ++i)
    {
        k = minimum(closedge, G.vexnum);
        if (k == -1)
        {
            printf("Graph is disconnected.\n");
            return;
        }

        // 输出当前选择的边
        printf("Edge: (%d, %d), Weight: %d\n", closedge[k].adjvex, G.vexs[k], closedge[k].lowcost);
        closedge[k].lowcost = 0; // 标记顶点 k 已加入最小生成树

        // 更新 closedge 数组
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[k][j] < closedge[j].lowcost && closedge[j].lowcost != 0)
            {
                closedge[j].adjvex = G.vexs[k];
                closedge[j].lowcost = G.arcs[k][j];
            }
        }
    }
}

// 主函数
int main(void)
{

    // 测试代码
    Graph G;
    G.vexnum = 6;
    G.arcnum = 10;

    // 顶点集合
    G.vexs[0] = 0;
    G.vexs[1] = 1;
    G.vexs[2] = 2;
    G.vexs[3] = 3;
    G.vexs[4] = 4;
    G.vexs[5] = 5;

    // 初始化邻接矩阵
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = INT_MAX; // 无边为无穷大
        }
    }

    // 添加边及权值
    G.arcs[0][1] = 6;
    G.arcs[1][0] = 6;
    G.arcs[0][2] = 1;
    G.arcs[2][0] = 1;
    G.arcs[0][3] = 5;
    G.arcs[3][0] = 5;
    G.arcs[1][2] = 5;
    G.arcs[2][1] = 5;
    G.arcs[2][3] = 5;
    G.arcs[3][2] = 5;
    G.arcs[1][4] = 3;
    G.arcs[4][1] = 3;
    G.arcs[2][4] = 6;
    G.arcs[4][2] = 6;
    G.arcs[2][5] = 4;
    G.arcs[5][2] = 4;
    G.arcs[3][5] = 2;
    G.arcs[5][3] = 2;
    G.arcs[5][4] = 6;
    G.arcs[4][5] = 6;

    // 调用普里姆算法
    printf("Minimum Spanning Tree:\n");
    MiniSpanTree_PRIM(G, 0);

    return 0;
}
