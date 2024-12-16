// // 以邻接链表为存储结构，实现图的广度优先遍历算法

// #include <stdio.h>
// #include <stdlib.h>

// #define MAX 100              // 最大顶点数
// #define InfoType int         // 弧的相关信息：权重
// #define MAX_VERTEX_NUM 100   // 顶点最大数目
// #define Vertex int           // 顶点类型

// int visited[MAX];   // 访问标志数组：记录每个顶点是否被访问过

// // 表结点
// typedef struct ArcNode {
//     int adjvex;                // 邻接顶点索引
//     struct ArcNode *nextarc;   // 下一条弧
//     InfoType info;             // 边的信息（权重）
// } ArcNode;

// // 头结点
// typedef struct Vnode {
//     Vertex data;               // 顶点信息
//     ArcNode *firstarc;         // 第一条弧
// } VNode, AdjList[MAX_VERTEX_NUM];

// // 图的邻接表表示
// typedef struct {
//     AdjList vertices;          // 顶点数组
//     int vexnum, arcnum;        // 顶点数和边数
//     int kind;                  // 图的类型
// } Graph;

// // 初始化图
// void InitGraph(Graph *G, int vexnum, int arcnum) {
//     G->vexnum = vexnum;
//     G->arcnum = arcnum;
//     for (int i = 0; i < vexnum; i++) {
//         G->vertices[i].data = i;     // 顶点编号
//         G->vertices[i].firstarc = NULL;
//     }
// }

// // 添加边到图中
// void AddEdge(Graph *G, int from, int to, InfoType info) {
//     ArcNode *newNode = (ArcNode *)malloc(sizeof(ArcNode));
//     newNode->adjvex = to;
//     newNode->info = info;
//     newNode->nextarc = G->vertices[from].firstarc;
//     G->vertices[from].firstarc = newNode;
// }

// // 广度优先遍历:
// // 1. 首先访问指定顶点v0，将v0作为当前顶点
// // 2. 访问当前顶点的所有为访问过的邻接点
// // 3. 并依次将访问的这些邻接点作为当前顶点
// // 4. 重复步骤2，直到所有顶点都被访问过为止

// void BFSTraverse(Graph G)
// {
//     for(int v = 0; v < G.vexnum; v++)
//     {
//         visited [v] = 0;
//     }
//     InitQueue(Q);
//     for(int v = 0; v < G.vexnum; v++)
//     {
//         if(!visited[v])
//         {
//             visited[v] = 1;
//             printf("%d ", v);
//             EnQueue(Q, v);
//             while(!QueueEmpty(Q))
//             {
//                 Dequeue(Q, u);
//                 for(w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
//                 {
//                     if(!visited[w])
//                     {
//                         visited[w] = 1;
//                         VisitFun(w);
//                         EnQueue(Q, w);
//                     }
//                 }
//             }
//         }
//     }
// }

// int main()
// {
//     return 0;
// }

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
