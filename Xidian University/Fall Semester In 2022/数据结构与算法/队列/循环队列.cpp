#include<iostream>
#include<cstdlib>
#include<ctime>
#include<random>
using namespace std;
/*-------本代码实现的循环队列基于顺序存储结构-----------*/
#define MAXQSIZE 100   //最大队列长度
#define Nmax 999   //控制随机数的精度
typedef struct{
    int *base;
    int front;  //头指针,若队列非空,指向队首元素
    int rear;   //尾指针,若队列非空,指向队尾元素的下一位置
}QuePtr;
//-------循环队列基本操作---------
//每一步的取余操作都是为了循环队列的实现
bool InitQueue(QuePtr &Q);
int QueLength(QuePtr Q);
bool EnQue(QuePtr &Q, int e);
int DeQue(QuePtr &Q);
void QueuePrint(QuePtr Q);
int main()
{
    srand(time(NULL));
    QuePtr Q;
    if(!InitQueue(Q)){
        cout << "OVERFLOW!" << endl;
        return 0;
    }
    int N = 300;
    for(int i=0;i<N;i++){
        if(!EnQue(Q, i+1)){
            int m = rand()%50;
            for(int j=0;j<m;j++)
                if(DeQue(Q) == -1) continue;
        }
    }
    cout << "The length of queue: " << QueLength(Q) << endl;
    QueuePrint(Q);
    return 0;
}
bool InitQueue(QuePtr &Q)
{
    Q.base = (int*)malloc(MAXQSIZE * sizeof(int));
    if(!Q.base) return false;
    Q.front = Q.rear = 0;
    return true;
}
int QueLength(QuePtr Q)
{
    return (Q.rear-Q.front+MAXQSIZE) % MAXQSIZE;
}
bool EnQue(QuePtr &Q, int e)
{
    if((Q.rear+1)%MAXQSIZE == Q.front) return false;  //默认损失一个存储位置
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear+1)%MAXQSIZE;
    return true;
}
int DeQue(QuePtr &Q)
{
    if(Q.front == Q.rear) return -1;  //队列为空
    int e = Q.base[Q.front];
    Q.front = (Q.front+1)%MAXQSIZE;
    return e;
}
void QueuePrint(QuePtr Q)
{
    cout << "Elements in queue:" << endl; 
    for(int i = Q.front;i%MAXQSIZE != Q.rear;i++){
        cout << Q.base[i] << " ";
    }
    cout << endl;
    return ;
}