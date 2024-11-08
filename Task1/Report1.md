

# 第二章 线性表上机实验

> **姓名：****
>
> **学号：****
>
> **Github仓库：https://github.com/Rain0832/Data_Structure_Course.git**

> **上机时间：第 8 周星期三（10 月 23 日）**
>
> **上机地点：基础实验大楼506**

# 1. 顺序表的实现

### 1.1 题目描述

- 顺序表的初始化，建立，插入，查找，删除。

### 1.2 程序结果

#### 建立顺序表操作页面

- 逐行输入顺序表元素
- `'Ctrl-Z' `实现完成输入

![image-20241108120647928](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241108120647928.png)

#### 打印顺序表元素

![image-20241108120914676](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241108120914676.png)

#### 顺序表插入元素

- 插入函数：` bool ListInsert(SeqList &L, int i, Element e)`
- 首先检查 `List ` 是否已满，满则输出Full，否则进行插入操作
- 打印顺序表检验插入后的顺序表

![image-20241108120945453](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241108120945453.png)

#### 顺序表的删除

- 删除函数 ` bool ListDelete(SeqList &L, int i, Element &e)` 

- 删除首先检验是否为空表，空则返回False，否则进行元素查询（按元素位置删除）

#### 顺序表的元素查询

- 根据值查询线性表中所有符合元素的位置，返回元素位置$index$ 

![image-20241108121421996](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241108121421996.png)

### 1.3 源程序

```cpp
// 顺序表的初始化，建立，插入，查找，删除。

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_SIZE 10
# define IncreSize 10
# define Element int

// 定义顺序表结构
struct SeqList
{
    Element data[MAX_SIZE]; // 数组模拟顺序表
    int length; // 存储顺序表长度
    int MaxSize; // 最大容量
};


// 初始化顺序表
void ListInit(SeqList &L)
{
    L.length = 0;
}

// 建立顺序表
// 通过输入数据元素建立一个线性表，使用ctrl-z表示输入完毕
void ListEstablish(SeqList &L)
{
    char input[20]; //输入的数字缓存区
    int cnt = 0;
    printf("Input Elements('Enter' to separate, 'Ctrl-Z' to end):\n");

    // 读取输入
    // fgets()读取到文件末尾“Ctrl-Z”时返回NULL
    while(fgets(input, 20, stdin) != NULL)
    {
        if(cnt >= MAX_SIZE)
        {
            printf("List Full!\n");
            return;
        }

        // 去掉输入的换行符
        // strcspn()返回寻找到的字符 “\n” 的位置
        input[strcspn(input, "\n")] = '\0';

        // 检查输入是否为空
        if(strlen(input) == 0) continue;

        // 将字符串转换为整数
        int value = atoi(input);

        L.data[cnt] = value;
        cnt++;

    }
    L.length = cnt;
    printf("Establish Successfully!\n");
}

// 打印顺序表操作
void ListPrint(SeqList &L)
{
    printf("SequenList\n");
    printf("Length: %d\n", L.length);
    for(int i = 0; i < L.length; i++)
    {
        printf("Elem %d: %d\n", i+1, L.data[i]);
    }
}

// 顺序表插入操作
// 参数：顺序表 L，插入位置 i，插入元素 e
// 索引 i 从 1 开始
bool ListInsert(SeqList &L, int i, Element e)
{
    // 考虑空间满的情况
    if(L.length >= MAX_SIZE)
    {
        printf("List Full!\n");
        return false; 
    }

    // 考虑插入位置越界的情况
    if(i < 1 || i > L.length + 1)
    {
        printf("Position Illegal!\n");
        return false;
    }

    // 元素后移
    for(int j = L.length; j >= i; j--)
    {
        L.data[j] = L.data[j-1];
    }

    // 插入元素
    L.data[i-1] = e;
    L.length++;

    printf("Elem %d Insert Successfully!\n", e);
    return true;
}

// 删除操作
bool ListDelete(SeqList &L, int i, Element &e)
{
    // 考虑是否是空表
    if(L.length == 0)
    {
        printf("List Null!\n");
        return false;
    }

    // 考虑删除元素越界
    if(i < 1 || i > L.length + 1)
    {
        printf("Position Illegal!\n");
        return false;
    }

    // 删除元素
    e = L.data[i-1];

    // 元素前移
    for(int j = i; j < L.length; j++)
    {
        L.data[j-1] = L.data[j];
    }

    L.length--;
    printf("Elem %d Delete Successfully!\n", e);
    return true;
}

// 查找操作
bool ListFind(SeqList &L, Element e)
{
    int judge = 0;
    for(int i = 0; i < L.length; i++)
    {
        if(L.data[i] == e)
        {
            judge = 1;
            printf("Element %d Find, Position: %d!\n", e, i+1);
        }
    }
    if(judge == 0)
    {
        printf("Elem %d Not Found!\n", e);
        return false;
    }
    return true;
}

int main(void)
{
    // 建立表
    SeqList L;
    printf("\n");

    // 表初始化
    ListInit(L);
    printf("\n");

    // 打印表
    ListPrint(L);
    printf("\n");

    // 建立表
    ListEstablish(L);
    printf("\n");

    // 打印表
    ListPrint(L);
    printf("\n");

    // 插入元素
    ListInsert(L, 2, 15);
    ListInsert(L, 4, 25);
    ListInsert(L, 6, 35);
    ListInsert(L, 8, 45);
    ListInsert(L, 9, 50);
    ListInsert(L, 10, 55);
    printf("\n");

    // 此时表已满：再插入则 返回 List full
    ListInsert(L, 10, 100);
    printf("\n");

    // 打印表
    ListPrint(L);
    printf("\n");

    // 删除元素
    Element e;
    ListDelete(L, 3, e);
    printf("\n");

    // 打印表
    ListPrint(L);
    printf("\n");

    // 查找元素
    ListFind(L, 20);
    ListFind(L, 50);
    printf("\n");

    return 0;
}
```

### 1.4 实验结论与结果分析

实验实现了用数组模拟线性表的实现。

相关操作的时间复杂度分析：

- 插入操作：O(1)（末尾）或 O(n)（中间或开头）

- 删除操作：O(1)（末尾）或 O(n)（中间或开头）

- 查找操作：O(n)（顺序查找）

> 顺序表的插入删除操作复杂度较高，且顺序表需要考虑事先分配内存，可能造成内存浪费，可以考虑适用单链表优化。

# 2. 单链表的实现

### 2.1 题目描述

- 单链表的初始化，建立，插入，查找，删除。

### 2.2 程序结果

#### 建立单链表操作页面

- 逐行输入单链表元素
- `'Ctrl-Z' `实现完成输入

![image-20241108121954694](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241108121954694.png)

#### 打印单链表元素

![image-20241108122106215](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241108122106215.png)

#### 单链表插入元素

- 插入函数：` void ListInsert(SingleList &L, int i, Element e)`
- 首先检查 `List ` 是否已满，满则输出Full，否则进行插入操作
- 打印单链表检验插入后的元素是否正确

![image-20241108122136223](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241108122136223.png)

#### 顺序表的元素查询

- 根据值查询单链表中所有符合元素的位置，返回元素位置$index$ 

![image-20241108122412908](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241108122412908.png)

#### 单链表的删除

- 删除函数 ` void ListDelete(SingleList &L, int i)` 

- 删除首先检验是否为空表，空则返回False，否则进行元素查询（按元素位置删除）

	![image-20241108122334775](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241108122334775.png)



### 2.3 源程序

```cpp
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
```

### 2.4 实验结论与结果分析

实验实现了用结构体、指针等模拟单链表表的实现。

相关操作的时间复杂度分析：

- 插入操作：O(1)（头部）或 O(n)（尾部或中间）
- 删除操作：O(1)（头部）或 O(n)（尾部或中间）
- 查找操作：O(n)

>  相比于顺序表可以大大减少内存开销，但插入和删除操作复杂度仍不够底，后期可以考虑使用双向链表等，提高遍历效率。

# 3. 循环链表实现约瑟夫问题

### 3.1 题目描述

- 适用循环链表解决约瑟夫问题

	> **约瑟夫问题描述**：据说著名犹太历史学家 Josephus有过以下的故事：在罗马人占领乔塔帕特后，39 个犹太人与Josephus及他的朋友躲到一个洞中，39个犹太人决定宁愿死也不要被敌人抓到，于是决定了一个自杀方式：41个人排成一个圆圈，由第1个人开始报数，每报数到第3人该人就必须自杀，然后再由下一个重新报数，直到所有人都自杀身亡为止。然而Josephus 和他的朋友并不想遵从。首先从一个人开始，越过k-2个人（因为第一个人已经被越过），并杀掉第k个人。接着，再越过k-1个人，并杀掉第k个人。这个过程沿着圆圈一直进行，直到最终只剩下一个人留下，这个人就可以继续活着。问题是一开始要站在什么地方才能避免自杀？Josephus要他的朋友先假装遵从，他将朋友与自己安排在第16个与第31个位置，于是逃过了这场死亡游戏。

### 3.2 程序结果

#### 循环链表的建立

利用 $for$ 循环建立 $1~41$ 的编号，并打印链表

```cpp
Element 1: 1
Element 2: 2
Element 3: 3
Element 4: 4
Element 5: 5
Element 6: 6
Element 7: 7
Element 8: 8
Element 9: 9
Element 10: 10
Element 11: 11
Element 12: 12
Element 13: 13
Element 14: 14
Element 15: 15
Element 16: 16
Element 17: 17
Element 18: 18
Element 19: 19
Element 20: 20
Element 21: 21
Element 22: 22
Element 23: 23
Element 24: 24
Element 25: 25
Element 26: 26
Element 27: 27
Element 28: 28
Element 29: 29
Element 30: 30
Element 31: 31
Element 32: 32
Element 33: 33
Element 34: 34
Element 35: 35
Element 36: 36
Element 37: 37
Element 38: 38
Element 39: 39
Element 40: 40
Element 41: 41
Circular List Length: 41
```

- 求解得知，最后两位 $kill$ 为编号 $16$ 与编号 $31$  ，即：约瑟夫和他的朋友得以存活，符合题意。

#### 约瑟夫问题的求解

- 设置报数数字为 $3$ ，报数起始位置为 $1$ 。

```cpp
Kill 3
Kill 6
Kill 9
Kill 12
Kill 15
Kill 18
Kill 21
Kill 24
Kill 27
Kill 30
Kill 33
Kill 36
Kill 39
Kill 1
Kill 5
Kill 10
Kill 14
Kill 19
Kill 23
Kill 28
Kill 32
Kill 37
Kill 41
Kill 7
Kill 13
Kill 20
Kill 26
Kill 34
Kill 40
Kill 8
Kill 17
Kill 29
Kill 38
Kill 11
Kill 40
Kill 8
Kill 17
Kill 29
Kill 38
Kill 11
Kill 17
Kill 29
Kill 38
Kill 11
Kill 29
Kill 38
Kill 11
Kill 25
Kill 2
Kill 25
Kill 2
Kill 22
Kill 2
Kill 22
Kill 22
Kill 4
Kill 35
Kill 16
Survivor: 31
```

### 3.3 源程序

```cpp
#include <stdio.h>
#include <stdlib.h>

// 定义循环链表结点
struct CircleList {
    int data;
    struct CircleList *next;
};

// 初始化循环链表
void ListInit(struct CircleList **head) {
    *head = (struct CircleList *)malloc(sizeof(struct CircleList));
    (*head)->next = *head;  // 头结点指向自己，形成初始环

    struct CircleList *p = *head;

    // 构造循环链表：初始数据为 1 到 41
    for (int i = 1; i <= 41; i++) {
        struct CircleList *q = (struct CircleList *)malloc(sizeof(struct CircleList));
        q->data = i;
        q->next = *head;  // 新节点指向头结点
        p->next = q;      // 上一个节点指向新节点
        p = q;            // 更新 p 为新节点
    }

    // 去掉头节点，使链表从 1 开始
    struct CircleList *temp = *head;
    *head = (*head)->next;
    p->next = *head;
    free(temp);
}

// 打印循环链表内容
void ListPrint(struct CircleList *head) {
    struct CircleList *p = head;
    int cnt = 1;

    // 遍历循环链表直到回到头结点
    do {
        printf("Element %d: %d\n", cnt, p->data);
        p = p->next;
        cnt++;
    } while (p != head);  // 循环条件为没有回到头结点
    printf("Circular List Length: %d\n", cnt - 1);
}

// 约瑟夫问题实现
// 参数说明：循环链表头结点 head，报数间隔 m，报数开始位置 k
void Josephus(struct CircleList *head, int m, int k) {
    struct CircleList *p = head;

    // 定位到第 k 个结点(约瑟夫报数游戏起点)
    for (int i = 1; i < k; i++) {
        p = p->next;
    }

    while (p->next != p) {  // 当链表只剩下一个节点时停止
        // 跳过 m-1 个数
        for (int i = 1; i < m - 1; i++) {
            p = p->next;
        }

        // 输出被“杀死”的结点
        printf("Kill %d\n", p->next->data);

        // 删除被“杀死”的结点
        struct CircleList *temp = p->next;
        p->next = temp->next;  // 跳过被删除的节点
        free(temp);            // 释放内存

        // p 指向下一个待操作的节点
        p = p->next;
    }

    // 输出最后的幸存者
    printf("Survivor: %d\n", p->data);
    free(p);  // 释放最后一个节点
}

int main(void) {
    struct CircleList *head = NULL;
    ListInit(&head);  // 初始化循环链表
    ListPrint(head);  // 打印链表

    // 解决约瑟夫问题（间隔 m = 3，从位置 k = 1 开始）
    Josephus(head, 3, 1);

    return 0;
}
```

### 3.4 实验结论与结果分析

使用循环链表实现循环报数

##### 困难点

- :question:如何跳过已经被杀死的节点？

	> 使用临时节点`temp`实现删除节点 

- :question:如何在报数时跳过建立循环链表时的头结点？

	> 在建立链表后即可将原始头节点(无数据)删除，使得新的头结点为编号 1 节点

- :question:将约瑟夫问题封装为函数，利于泛化
