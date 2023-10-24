#include<iostream>
#include<cstdlib>
using namespace std;

//---------单链队列——队列的链式存储结构--------//
typedef struct Qnode{
    int data;
    struct Qnode* next;
}Qnode, * QuePtr;
typedef struct{
    QuePtr front; // 队列头指针
    QuePtr rear;   // 队列尾指针
}LinkQue;
// 初始化队列的生成
LinkQue InitQueue()
{
    LinkQue ptr;
    ptr.front = (QuePtr)malloc(sizeof(Qnode));
    if(!ptr.front) error;
    ptr.rear = ptr.front;
    ptr.front->data = 0;
    ptr.front->next = NULL;
    return ptr;
}
// 元素入队列
bool EnQueue(LinkQue &Q, int e)
{
    QuePtr p = (QuePtr)malloc(sizeof(Qnode));
    if(!p) error;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    Q.front->data++;   //更新队列长度
    return true;    
}
// 销毁已有队列
bool DestroyQueue(LinkQue &Q)
{
    //释放包括队列头结点的空间
    while(Q.front){
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return true;
}
bool DeQueue(LinkQue &Q, int &e)
{
    //首先判断队列是否为空
    if(Q.front == Q.rear) return false;
    QuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    // 对最后一个元素进行特判
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    Q.front->data--;
    return true;
}
bool ClearQueue(LinkQue &Q)
{
    QuePtr p = Q.front->next;
    while(p){
        p->data = 0;
        p = p->next;
    }
    return true;
}
bool QueueEmpty(LinkQue Q)
{
    if(Q.front==Q.rear) return true;
    return false;
}
bool QueueLength(LinkQue Q,int &LL)
{
    LL = Q.front->data
    return true;
}
bool GetHead(LinkQue Q, int &e)
{
    e = Q.front->next->data;
    return true;
}