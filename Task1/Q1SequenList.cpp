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