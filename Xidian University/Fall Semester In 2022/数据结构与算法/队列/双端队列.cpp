#include<iostream>
#include<cstdlib>
#include<random>
#include<ctime>
const int Nnum = 999;
using namespace std;
/*----------双端队列(Deque)-------/
/*-------变式——输出受限或输入受限的双端队列：限制其中一个端点的插入或删除操作-----
----------(此类形式不作赘述)-------*/
/*限定插入和删除操作只能在端点处进行*/
typedef struct Qnode {
    int data;
    struct Qnode* next;
}Qnode, * QuePtr;
typedef struct {
    QuePtr front; // 队列头指针
    QuePtr rear;   // 队列尾指针
}LinkQue;
// 对应相关操作
bool InitQueue(LinkQue& Q);
bool Push_Front(LinkQue& Q, int e);
bool Push_Back(LinkQue& Q, int e);
int Pop_Front(LinkQue& Q);
int Pop_Back(LinkQue& Q);
bool ClearQueue(LinkQue& Q);
int QueueLength(LinkQue Q);
int GetHead(LinkQue Q);
int GetRear(LinkQue Q);
bool QueuePrint(LinkQue Q);

int main()
{
    srand(time(NULL));//设置随机数种子，使每次产生的随机序列不同
    int N = 30;
    // 创建一个双端队列
    LinkQue Q;
    if (!InitQueue(Q)) return 0;
    for (int i = 0; i < N; i++) {
        if (rand() % (Nnum + 1) / (float)(Nnum + 1) < 0.5) Push_Back(Q, i + 1);
        else Push_Front(Q, i + 1);
    }
    QueuePrint(Q);
    for (int i = 0; i < N / 2; i++) {
        if (rand() % (Nnum + 1) / (float)(Nnum + 1) < 0.5) {
            int e = Pop_Back(Q);
            if (e == -1) continue;
            else cout << "Pop element back: " << e << endl;
        }
        else {
            int e = Pop_Front(Q);
            if (e == -1) continue;
            else cout << "Pop element head: " << e << endl;
        }
    }
    QueuePrint(Q);
    return 0;
}
// 初始化队列的生成
bool InitQueue(LinkQue& ptr)
{
    ptr.front = (QuePtr)malloc(sizeof(Qnode));
    if (!ptr.front) return false;
    ptr.rear = ptr.front;
    ptr.front->data = 0;
    ptr.front->next = NULL;
    return true;
}
/*----------------------------------------*/
// 元素队首入队列
bool Push_Front(LinkQue& Q, int e)
{
    QuePtr p = (QuePtr)malloc(sizeof(Qnode));
    if (!p) return false;
    p->data = e;
    p->next = Q.front->next;
    Q.front->next = p;
    Q.front->data++;   //更新队列长度
    if (Q.front == Q.rear) Q.rear = p;  // 特判初始状态
    return true;
}
// 元素队尾入队列
bool Push_Back(LinkQue& Q, int e)
{
    QuePtr p = (QuePtr)malloc(sizeof(Qnode));
    if (!p) return false;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    Q.front->data++;   //更新队列长度
    return true;
}
/*------------------------------------*/
/*------------------------------------*/
int Pop_Front(LinkQue& Q)
{
    //首先判断队列是否为空
    if (Q.front == Q.rear) return -1;
    QuePtr p = Q.front->next;
    int e = p->data;
    Q.front->next = p->next;
    // 对最后一个元素进行特判
    if (Q.rear == p) Q.rear = Q.front;
    free(p);
    Q.front->data--;
    return e;
}
int Pop_Back(LinkQue& Q)
{
    //首先判断队列是否为空
    if (Q.front == Q.rear) return -1;
    QuePtr p = Q.front;
    while (p->next != Q.rear) p = p->next;
    int e = Q.rear->data;
    free(Q.rear);
    p->next = NULL;
    Q.rear = p;
    Q.front->data--;
    return e;
}
/*----------------------------------*/
bool ClearQueue(LinkQue& Q)
{
    QuePtr p = Q.front->next;
    while (p) {
        p->data = 0;
        p = p->next;
    }
    return true;
}
int QueueLength(LinkQue Q)
{
    return Q.front->data;
}
int GetHead(LinkQue Q)
{
    return Q.front->next->data;
}
int GetRear(LinkQue Q)
{
    return Q.rear->data;
}
bool QueuePrint(LinkQue Q)
{
    QuePtr p = Q.front->next;
    if (!p) {
        cout << "Empty Queue！" << endl;
        return true;
    }
    cout << "The length of deque: " << QueueLength(Q) << endl;
    cout << "Deque head element: " << GetHead(Q) << ' ' << "Deque end element: " << GetRear(Q) << endl;
    cout << "Deque elements:" << endl;
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
    return true;
}