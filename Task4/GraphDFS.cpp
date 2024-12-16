// // 以邻接链表为存储结构，实现图的深度优先遍历算法

#include <stdio.h>
#include <stdlib.h>

#define MAX 100            // 最大顶点数
#define InfoType int       // 弧的相关信息：权重
#define MAX_VERTEX_NUM 100 // 顶点最大数目
#define Vertex int         // 顶点类型

int visited[MAX]; // 访问标志数组：记录每个顶点是否被访问过

// 表结点
typedef struct ArcNode
{
    int adjvex;              // 邻接顶点索引
    struct ArcNode *nextarc; // 下一条弧
    InfoType info;           // 边的信息（权重）
} ArcNode;

// 头结点
typedef struct Vnode
{
    Vertex data;       // 顶点信息
    ArcNode *firstarc; // 第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];

// 图的邻接表表示
typedef struct
{
    AdjList vertices;   // 顶点数组
    int vexnum, arcnum; // 顶点数和边数
    int kind;           // 图的类型
} Graph;

// 初始化图
void InitGraph(Graph *G, int vexnum, int arcnum)
{
    G->vexnum = vexnum;
    G->arcnum = arcnum;
    for (int i = 0; i < vexnum; i++)
    {
        G->vertices[i].data = i; // 顶点编号
        G->vertices[i].firstarc = NULL;
    }
}

// 添加边到图中
void AddEdge(Graph *G, int from, int to, InfoType info)
{
    ArcNode *newNode = (ArcNode *)malloc(sizeof(ArcNode));
    newNode->adjvex = to;
    newNode->info = info;
    newNode->nextarc = G->vertices[from].firstarc;
    G->vertices[from].firstarc = newNode;
}

// 图的深度优先遍历
void DFS(Graph G, int v)
{
    visited[v] = 1; // 标记访问过
    printf("Visited vertex: %d\n", v);

    ArcNode *p = G.vertices[v].firstarc;
    while (p)
    {
        int w = p->adjvex;
        if (!visited[w])
        {
            DFS(G, w);
        }
        p = p->nextarc;
    }
}

// 遍历主函数
void DFSTraverse(Graph G)
{
    for (int v = 0; v < G.vexnum; v++)
    {
        visited[v] = 0; // 初始化访问标志
    }
    for (int v = 0; v < G.vexnum; v++)
    {
        if (!visited[v])
        {
            DFS(G, v);
        }
    }
}

int main(void)
{

    // 测试 DFS 函数
    Graph G;
    int vexnum = 8, arcnum = 9; // 示例：8个顶点，18条有向边（9条无向边）
    InitGraph(&G, vexnum, arcnum);

    // 添加边（无向图）
    AddEdge(&G, 0, 1, 0); // 0 -> 1
    AddEdge(&G, 1, 0, 0); // 1 -> 0

    AddEdge(&G, 1, 3, 0); // 1 -> 3
    AddEdge(&G, 3, 1, 0); // 3 -> 1

    AddEdge(&G, 3, 7, 0); // 3 -> 7
    AddEdge(&G, 7, 3, 0); // 7 -> 3

    AddEdge(&G, 7, 4, 0); // 7 -> 4
    AddEdge(&G, 4, 7, 0); // 4 -> 7

    AddEdge(&G, 4, 1, 0); // 4 -> 1
    AddEdge(&G, 1, 4, 0); // 1 -> 4

    AddEdge(&G, 0, 2, 0); // 0 -> 2
    AddEdge(&G, 2, 0, 0); // 2 -> 0

    AddEdge(&G, 2, 5, 0); // 2 -> 5
    AddEdge(&G, 5, 2, 0); // 5 -> 2

    AddEdge(&G, 5, 6, 0); // 5 -> 6
    AddEdge(&G, 6, 5, 0); // 6 -> 5

    AddEdge(&G, 5, 2, 0); // 5 -> 2
    AddEdge(&G, 2, 5, 0); // 2 -> 5

    printf("DFS Traversal:\n");
    DFSTraverse(G);

    return 0;
}
