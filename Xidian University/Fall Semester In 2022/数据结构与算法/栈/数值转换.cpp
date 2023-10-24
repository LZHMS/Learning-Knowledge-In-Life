#include<iostream>
#include<cstdlib>
using namespace std;

typedef int SElemType;
typedef bool Status;

const bool OK = true;
const bool ERROR = false;
const SElemType STACK_INIT_SIZE = 100;
const SElemType STACKINCREMENT = 10;
typedef struct{
    SElemType *base;   // 栈底指针
    SElemType *top;    // 栈顶指针
    int stacksize;   // 当前栈的最大容量 
}SqStack;
Status InitStack(SqStack &S)
{
    // 构造空栈S
    S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base) exit(EOVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}
Status Push(SqStack &S, SElemType e)
{
    //首先判断是否栈满
    if(S.top-S.base >= S.stacksize){
        S.base = (SElemType *)realloc(S.base, (S.stacksize+STACKINCREMENT) * sizeof(SElemType));   //申请增量空间
        if(!S.base) exit(EOVERFLOW);
        // 更新回原来位置
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}
Status Pop(SqStack &S, SElemType &e)
{
    // 栈空标志
    if(S.top == S.base) return ERROR;
    e = *--S.top;
    return OK;
}
Status StackEmpty(SqStack S)
{
    if(S.base == S.top) return true;
    return false;
}
Status Conversion()
{
    SqStack S;
    InitStack(S);
    SElemType data;
    int Obj = 0;
    cin >> data >> Obj;
    while(data){
        Push(S,data % Obj);
        data = data/Obj;
    }
    while(!StackEmpty(S))
    {
        SElemType e;
        if(!Pop(S,e)) break;
        cout << e;
    }
    cout << endl;
    return OK;
}
int main()
{
    Conversion();
    return 0;
}