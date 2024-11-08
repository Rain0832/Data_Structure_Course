#include <stdio.h>
#include <stdlib.h>

// 定义循环链表结点
struct CircleList {
    int data;
    struct CircleList *next;
};

// 初始化循环链表，形成 1-5 的数据环
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
