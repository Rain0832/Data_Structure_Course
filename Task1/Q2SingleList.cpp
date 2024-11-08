// 单链表的初始化，建立，插入，查找，删除操作

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10
#define Element int

// 定义单链表结构
struct SingleList
{
    int data;         // 数据域
    SingleList *next; // 指针域
};

// 初始化单链表
void ListInit(SingleList *L)
{
    L->next = NULL;
}

// 建立单链表
// 通过输入数据元素建立一个线性表，使用ctrl-z表示输入完毕
void ListEstablish(SingleList *L)
{
    char input[20]; // 输入的数字缓存区
    int cnt = 0;
    printf("Input Elements('Enter' to separate, 'Ctrl-Z' to end):\n");

    // 读取输入
    // fgets()读取到文件末尾“Ctrl-Z”时返回NULL
    while (fgets(input, 20, stdin) != NULL)
    {
        if (cnt >= MAX_SIZE)
        {
            printf("List full!\n");
            return;
        }

        // 去掉输入的换行符
        // strcspn()返回寻找到的字符 “\n” 的位置
        input[strcspn(input, "\n")] = '\0';

        // 检查输入是否为空
        if (strlen(input) == 0)
            continue;

        // 将字符串转换为整数
        int value = atoi(input);

        // 建立临时节点 p
        SingleList *p = (SingleList *)malloc(sizeof(SingleList));
        p->data = value;
        p->next = NULL;

        // 插入到链表尾部
        // 若链表为空
        if (L->next == NULL)
        {
            L->next = p;
        }
        else
        {
            // 临时结点 q 指向链表尾部
            SingleList *q = L->next;
            while (q->next != NULL)
                q = q->next;
            // 将 p 插入到 q（链表尾部） 的后面
            q->next = p;
        }
        cnt++;
    }
    printf("Establish Successfully!\n");
}

// 打印单链表操作
void ListPrint(SingleList *L)
{
    SingleList *p = L->next;
    int cnt = 1;
    while (p != NULL)
    {
        printf("Element %d: %d\n", cnt, p->data);
        p = p->next;
        cnt++;
    }
    printf("SingleList length: %d\n", cnt - 1);
}

// 插入操作
// 参数：链表名 L、插入位置 i、插入元素 e
void ListInsert(SingleList &L, int i, Element e)
{
    // 考虑空间满的情况
    if (i < 1 || i > MAX_SIZE)
    {
        printf("Position Illegal!\n");
        return;
    }

    // 建立新节点
    SingleList *p = (SingleList *)malloc(sizeof(SingleList));
    p->data = e;
    p->next = NULL;

    // 若插入位置在链表头
    if (i == 1)
    {
        p->next = L.next;
        L.next = p;
    }
    else
    {
        // 临时结点 q
        SingleList *q = L.next;
        int cnt = 1;
        // q 指向链表第 i-1 个节点
        while (cnt < i - 1 && q->next != NULL)
        {
            q = q->next;
            cnt++;
        }
        // 第一步：将 p 的 next 指向 q 的 next（原第i个节点）
        p->next = q->next;
        // 第二步：将 q 的 next 指向 p
        q->next = p;

        printf("Element %d Insert Successfully!\n", e);
        return;
    }
}

// 删除操作
void ListDelete(SingleList &L, int i)
{
    int data;
    // 边界检查
    if (i < 1 || i > MAX_SIZE)
    {
        printf("Position Illegal!\n");
        return;
    }

    // 建立临时结点 q
    SingleList *q = L.next;
    int cnt = 1;

    // 让 q 指向链表第 i-1 个节点
    while (cnt < i - 1 && q->next != NULL)
    {
        q = q->next;
        cnt++;
    }

    // 若删除位置在链表头
    if (i == 1)
    {
        L.next = q->next;
        free(q);
    }
    else
    {
        // 临时结点 p 指向待删除的节点（i）
        SingleList *p = q->next;
        data = p->data;
        // 第一步：将 q 的 next 指向 p 的 next（原第i+1个节点）
        q->next = p->next;
        // 第二步：释放 p 内存
        free(p);
    }
    printf("Element %d: %d Delete Successfully!\n", i, data);
}

// 查找操作
bool ListFind(SingleList *L, Element e)
{
    int judge = 0;
    int cnt = 1;
    SingleList *p = L->next;
    while (p != NULL)
    {
        if (p->data == e)
        {
            printf("Element %d Find, Position: %d\n", e, cnt);
            judge = 1;
        }
        p = p->next;
        cnt++;
    }
    if (judge == 0)
    {
        printf("Element %d Not Found!\n", e);
        return false;
    }
    return true;
}

int main(void)
{
    // 定义单链表
    SingleList L;

    // 初始化单链表
    ListInit(&L);

    // 建立单链表
    ListEstablish(&L);
    printf("\n");

    // 打印单链表
    ListPrint(&L);
    printf("\n");

    // 插入操作
    // 参数：链表名、插入位置、插入元素
    ListInsert(L, 3, 19);
    ListInsert(L, 5, 12);
    ListInsert(L, 6, 19);
    printf("\n");

    // 打印单链表
    ListPrint(&L);
    printf("\n");

    // 查找操作
    // 参数：链表名、查找元素
    ListFind(&L, 19);
    printf("\n");

    // 删除操作
    ListDelete(L, 3);
    printf("\n");

    // 打印单链表
    ListPrint(&L);
    printf("\n");
}