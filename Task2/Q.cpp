#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QElemtype Car
#define SElemtype Car

#define STACK_SIZE 5            // 栈容量
#define STACK_INCREMENT 3       // 栈扩容增量
#define PRICE 1                 // 价格收费 1元/秒

// 车辆结构体
typedef struct Car {
    int carNum;        // 车牌号
    time_t enterTime;  // 入场时间
} Car;

// 队列模拟：便道停车
// 链队列

// 存储结构定义
typedef struct Qnode {
    QElemtype data;         // 数据域（存储车牌号和入场时间）
    struct Qnode *next;     // 指针域
} Qnode, *Qptr;

typedef struct {
    Qptr front;             // 队头指针
    Qptr rear;              // 队尾指针
} LinkQ;

// 链队列初始化
bool InitQueue(LinkQ &Q) {
    Q.front = Q.rear = (Qptr)malloc(sizeof(Qnode)); // 申请一个节点空间
    if (!Q.front) {
        return false;
    }
    Q.front->next = NULL;
    return true;
}

// 打印队列
void PrintQueue(LinkQ &Q) {
    int cnt = 0;
    Qptr p = Q.front->next;
    while (p != NULL) {
        printf("车辆 %d ： 车牌号 %d\n", cnt + 1, p->data.carNum);
        p = p->next;
        cnt++;
    }
    printf("共 %d 辆车在便道上\n", cnt);
}

// 链队列入队操作
bool EnQueue(LinkQ &Q, QElemtype e) {
    Qptr p = (Qptr)malloc(sizeof(Qnode));
    if (!p) {
        return false;
    }
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return true;
}

// 链队出队操作
bool DeQueue(LinkQ &Q, QElemtype &e) {
    if (Q.rear == Q.front) {
        return false;
    }
    Qptr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (p == Q.rear) {
        Q.rear = Q.front;
    }
    free(p);
    return true;
}

// 栈模拟：停车场停车、临时让路停车
// 顺序栈
typedef struct {
    SElemtype *base; // 栈底指针
    SElemtype *top;  // 栈顶指针
    int stacksize;   // 当前栈容量
} SquenceS;

// 顺序栈初始化
bool InitStack(SquenceS &S) {
    S.base = (SElemtype *)malloc(STACK_SIZE * sizeof(SElemtype));
    if (!S.base) {
        return false;
    }
    S.top = S.base;
    S.stacksize = STACK_SIZE;
    return true;
}

// 打印栈
void PrintStack(SquenceS &S) {
    int cnt = 0;
    SElemtype *p = S.base;
    while (p != S.top) {
        printf("车辆 %d ： 车牌号 %d\n", cnt + 1, p->carNum);
        p++;
        cnt++;
    }
    printf("共 %d 辆车在停车场内\n", cnt);
}

// 顺序栈入栈操作
bool PushStack(SquenceS &S, SElemtype e) {
    // 栈满，扩容
    if (S.top - S.base >= S.stacksize) {
        SElemtype *I_temp = (SElemtype *)realloc(S.base, (S.stacksize + STACK_INCREMENT) * sizeof(SElemtype));
        if (!I_temp) {
            return false;
        }
        S.base = I_temp;
        S.top = S.base + S.stacksize;
        S.stacksize += STACK_INCREMENT;
    }
    *(S.top) = e;
    S.top++;
    return true;
}

// 顺序栈出栈操作
bool PopStack(SquenceS &S, SElemtype &e) {
    if (S.top == S.base) {
        return false;
    }
    S.top--;
    e = *(S.top);
    return true;
}

// 停车费计算
int CalculateFee(time_t enterTime) {
    time_t currentTime = time(NULL);
    double seconds = difftime(currentTime, enterTime); // 时间差（秒）
    return (int)(seconds * PRICE); // 每秒1元
}

// 显示菜单
void showMenu(SquenceS &parkLot, LinkQ &parkWay) {
    printf("欢迎来到停车场\n");
    printf("当前停车场状态：\n");
    PrintStack(parkLot);
    printf("当前便道停车状态：\n");
    PrintQueue(parkWay);
    printf("\n");
    printf("1. 入车\n");
    printf("2. 出车\n");
    printf("3. 刷新页面\n");
    printf("4. 退出程序\n");
    printf("请选择操作：");
}

int main(void) {
    // 栈模拟停车场停车
    SquenceS parkLot;
    InitStack(parkLot);

    // 栈模拟临时让路停车
    SquenceS tempLot;
    InitStack(tempLot);

    // 链队列模拟便道停车
    LinkQ parkWay;
    InitQueue(parkWay);

    int select = 0;
    while (true) {
        showMenu(parkLot, parkWay);
        scanf("%d", &select);
        switch (select) {
            case 1: { // 入车
                int carNum;
                printf("请输入车辆编号：");
                scanf("%d", &carNum);
                Car newCar = {carNum, time(NULL)};
                if (parkLot.top - parkLot.base < STACK_SIZE) {
                    PushStack(parkLot, newCar);
                    printf("车辆 %d 成功进入停车场！\n", carNum);
                } else {
                    printf("停车场已满，车辆 %d 已进入便道！\n", carNum);
                    EnQueue(parkWay, newCar);
                }
                break;
            }

            case 2: { // 出车
                int carNum;
                printf("请输入要出车的车辆编号：");
                scanf("%d", &carNum);

                // 检查车辆是否在便道
                Qptr prev = parkWay.front;
                Qptr curr = parkWay.front->next;
                bool foundInQueue = false;

                while (curr != NULL) {
                    if (curr->data.carNum == carNum) {
                        foundInQueue = true;
                        prev->next = curr->next;
                        if (curr == parkWay.rear) {
                            parkWay.rear = prev;
                        }
                        free(curr);
                        printf("车辆 %d 从便道离去，不收停车费！\n", carNum);
                        break;
                    }
                    prev = curr;
                    curr = curr->next;
                }

                if (foundInQueue) break; // 已处理完，退出 case

                // 检查车辆是否在停车场
                Car tempCar;
                bool foundInStack = false;
                while (PopStack(parkLot, tempCar)) {
                    if (tempCar.carNum == carNum) {
                        foundInStack = true;
                        int fee = CalculateFee(tempCar.enterTime);
                        printf("车辆 %d 成功出车！停车费用：%d元\n", carNum, fee);
                        break;
                    } else {
                        PushStack(tempLot, tempCar);
                    }
                }

                // 恢复让车道车辆
                while (PopStack(tempLot, tempCar)) {
                    PushStack(parkLot, tempCar);
                }

                if (!foundInStack) {
                    printf("未找到车辆 %d！\n", carNum);
                }
                break;
            }

            case 3: // 刷新页面
                break;

            case 4: // 退出程序
                printf("程序结束。\n");
                return 0;

            default:
                printf("无效选择，请重新输入。\n");
                break;
        }
        system("pause");
        system("cls");
    }
    return 0;
}
