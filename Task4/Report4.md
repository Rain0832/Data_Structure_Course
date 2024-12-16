

# 第七章 图上机实验

> **姓名：黄昌斌**
>
> **学号：2023140902005**
>
>  **Github仓库： https://github.com/Rain0832/Data_Structure_Course.git**

> **上机时间：第 15 周星期六（12 月 14 日）**
>
> **上机地点：基础实验大楼506**

### 实验目的

1.  进一步掌握图的结构及非线性特点，递归特点和动态性。
2.  进一步巩固图的三种存储结构和二种遍历方法、最小生成树的两种求解算法。

### 实验题目

1. 以邻接链表为存储结构，实现图的深度优先和广度优先遍历算法。 
2.  设计合适的存储结构，用普里姆算法和克鲁斯卡尔算法求网的最小生成树。

### 实验性质

- 设计型实验

# 1. 深度优先遍历算法

### 1.1 题目描述

- 图结构的初始化，建立，邻接表结构。
- DFS递归函数。

### 1.2 程序结果

测试样例：

- 对于如下的一个无向网图：

![graph (1)](D:\Downloads\graph (1).png)

- 一种深度优先搜索方案为：

![FTjntJeRRPUAHHCz](D:\Downloads\FTjntJeRRPUAHHCz.png)

- 运行程序，验证结果正确:

![image-20241216150024006](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241216150024006.png)



### 1.3 源程序

```cpp
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

```

### 1.4 实验结论与结果分析

实验实现了深度优先遍历DFS。

算法分析:  

- 假设图中有$n$ 个顶点，$e$ 条边。遍历过程实质上是对每个顶点查找邻接点的过程。  
- 如果用邻接表表示图，沿 $firsarc$ 链可以找到某个顶点v的所有邻接顶点w。由于总共有 $2e$ 个边结点，所以扫描边的时间为$O(e)$ 。所以遍历图的时间复杂性为$O(n+e)$ 。 
- 如果用邻接矩阵表示图，则查找每一个顶点的所有的边， 需时间为 $O(n)$ ，则遍历图中所有的顶点所需的时间为$O(n^2 )$。

# 2. 广度优先遍历算法

### 2.1 题目描述

- 图结构的初始化，建立，邻接表结构。队列的建立和基本操作。
- BFS递归函数。

### 2.2 程序结果

测试样例：

- 对于如下的一个无向网图：

![rgLIPquZRWpcoAGz](D:\Downloads\rgLIPquZRWpcoAGz.png)

- 一种广度优先搜索方案为：

![OaUAtyxwxCsCboph](D:\Downloads\OaUAtyxwxCsCboph.png)

- 运行程序，验证结果正确：

![screenshot-20241216-153653](D:\Downloads\screenshot-20241216-153653.png)

### 2.3 源程序

```cpp
// 以邻接链表为存储结构，实现图的广度优先遍历算法

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

// 队列结构
typedef struct
{
    int data[MAX];
    int front, rear;
} Queue;

// 初始化队列
void InitQueue(Queue *Q)
{
    Q->front = Q->rear = 0;
}

// 判断队列是否为空
int QueueEmpty(Queue Q)
{
    return Q.front == Q.rear;
}

// 入队
void EnQueue(Queue *Q, int x)
{
    if ((Q->rear + 1) % MAX == Q->front)
    {
        printf("Queue overflow\n");
        exit(1);
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAX;
}

// 出队
void DeQueue(Queue *Q, int *x)
{
    if (QueueEmpty(*Q))
    {
        printf("Queue underflow\n");
        exit(1);
    }
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAX;
}

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

// 获取顶点 v 的第一个邻接点
int FirstAdjVex(Graph G, int v)
{
    ArcNode *p = G.vertices[v].firstarc;
    return (p != NULL) ? p->adjvex : -1;
}

// 获取顶点 v 的相对于 w 的下一个邻接点
int NextAdjVex(Graph G, int v, int w)
{
    ArcNode *p = G.vertices[v].firstarc;
    while (p != NULL && p->adjvex != w)
    {
        p = p->nextarc;
    }
    if (p != NULL && p->nextarc != NULL)
    {
        return p->nextarc->adjvex;
    }
    return -1;
}

// 广度优先遍历
void BFSTraverse(Graph G)
{
    Queue Q;
    InitQueue(&Q);

    for (int v = 0; v < G.vexnum; v++)
    {
        visited[v] = 0; // 初始化访问标志
    }

    for (int v = 0; v < G.vexnum; v++)
    {
        if (!visited[v])
        {
            visited[v] = 1;
            printf("Visited vertex: %d\n", v);
            EnQueue(&Q, v);
            while (!QueueEmpty(Q))
            {
                int u;
                DeQueue(&Q, &u);
                for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
                {
                    if (!visited[w])
                    {
                        visited[w] = 1;
                        printf("Visited vertex: %d\n", w);
                        EnQueue(&Q, w);
                    }
                }
            }
        }
    }
    printf("\n");
}

// 测试函数
int main()
{
    Graph G;
    int vexnum = 9, arcnum = 9; // 示例：5个顶点，6条边
    InitGraph(&G, vexnum, arcnum);

    // 添加边（无向图）
    AddEdge(&G, 0, 1, 0);
    AddEdge(&G, 1, 0, 0);

    AddEdge(&G, 0, 2, 0);
    AddEdge(&G, 2, 0, 0);

    AddEdge(&G, 0, 3, 0);
    AddEdge(&G, 3, 0, 0);

    AddEdge(&G, 1, 2, 0);
    AddEdge(&G, 2, 1, 0);

    AddEdge(&G, 3, 5, 0);
    AddEdge(&G, 5, 3, 0);

    AddEdge(&G, 5, 7, 0);
    AddEdge(&G, 7, 5, 0);

    AddEdge(&G, 5, 2, 0);
    AddEdge(&G, 2, 5, 0);

    AddEdge(&G, 8, 7, 0);
    AddEdge(&G, 7, 8, 0);

    AddEdge(&G, 1, 4, 0);
    AddEdge(&G, 4, 1, 0);

    AddEdge(&G, 4, 6, 0);
    AddEdge(&G, 6, 4, 0);

    printf("BFS Traversal:\n");
    BFSTraverse(G);

    return 0;
}

```

### 2.4 实验结论与结果分析

实验实现了广度优先遍历BFS。

算法分析 ：

- 图中每个顶点至多入队一次，因此外循环次数为 $n$。

- 当图 $G$ 采用邻接表方式存储，则当结点v出队后，内循环次 数等于结点 $v$ 的度。由于访问所有顶点的邻接点的总的时间复 杂度为 $O(d_0+d_1+d_2+…+d_{n-1})=O(e)$ ， 因此图采用邻接表方式存储，广度优先搜索算法的时间复杂度为 $O(n+e)$ ；

- 当图G采用邻接矩阵方式存储，由于找每个顶点的邻接点时， 内循环次数等于 $n$，因此广度优先搜索算法的时间复杂度为  $O(n^2)$。

# 3. 普里姆算法求最小生成树

### 3.1 题目描述

- 设计合适的存储结构，用普里姆算法求网的最小生成树

> 从一个平凡图开始，普利姆算法逐步增加U中的顶点，可 称为“加点法”。

### 3.2 程序结果

测试用例：

- 对于如下的一个无向网图:

![gqTzCwyLtjAEEMNj](D:\Downloads\gqTzCwyLtjAEEMNj.png)

- 一种利用Prim算法求得的最小生成树如下：

	![bJXomHLyCGvWspvJ](D:\Downloads\bJXomHLyCGvWspvJ.png)

- 运行程序，验证结果正确：

![screenshot-20241216-154124](D:\Downloads\screenshot-20241216-154124.png)



### 3.3 源程序

```cpp
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

```

### 3.4 实验结论与结果分析

实验实现了利用Prim算法求最小生成树。

> 计算机内怎样实现Prim（普里姆）算法？
>
> Prime算法特点: 将顶点归并，与边数无关，适于稠密网。 
>
> 故采用邻接矩阵作为图的存储表示。 
>
> 设计思路： 
>
> 增设一辅助数组$Closedge[n]$，以记录从$U$ 到 $V-U$ 具有最小代价的边， 每个数组分量都有两个域
>
> 算法复杂度：$O(n^2)$

# 4. 克鲁斯卡尔算法求最小生成树

### 4.1 题目描述

- 设计合适的存储结构，用克鲁斯卡尔算法求网的最小生成树

	> 从一个零图开始，克鲁斯卡尔算法 逐步增加生成树的边，与普里姆算 法相比，可称为“加边法”

### 4.2 程序结果

测试用例：

- 对于如下的一个无向网图:

![gqTzCwyLtjAEEMNj](D:\Downloads\gqTzCwyLtjAEEMNj.png)

- 一种利用Kruskal算法求得的最小生成树如下：

	![bJXomHLyCGvWspvJ](D:\Downloads\bJXomHLyCGvWspvJ.png)

- 运行程序，验证结果正确：

![image-20241216155514343](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241216155514343.png)

### 4.3 源程序

```cpp
// 设计合适的存储结构，用克鲁斯卡尔算法求网的最小生成树。
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

```

### 4.4 实验结论与结果分析

实验实现了利用Kruskal算法求最小生成树。

> 适用于稀疏网的最小生成树， 算法复杂度为: $O(n\log{n})$
