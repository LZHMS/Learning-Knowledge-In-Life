#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;

typedef char SElemType;
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
Status StackPrint(SqStack S)
{
    SElemType *mp = S.base;
    while(mp != S.top){
        putchar(*mp);
        mp++;
    }
    putchar('\n');
    return OK;
}
Status ClearStack(SqStack &S)
{
    // 利用栈空标志进行清空
    S.top = S.base;
    return OK;
}
Status DestroyStack(SqStack &S)
{
    if(S.base != NULL) free(S.base);
    return OK;
} 
Status LineEdit()
{
    //构造字符栈
    SqStack S;
    InitStack(S);
    SElemType ch;
    ch = getchar();  //从终端接受一个字符
    while(ch != '^'){
        while(ch != '^' && ch != '\n'){
            switch(ch){
                case '#':Pop(S,ch);  //退字符
                         break;
                case '@':ClearStack(S); //退行
                         break;
                default:Push(S,ch); //字符入栈
            }
            ch = getchar(); //从终端接受下一个字符
        }
        //对缓冲区的一行字符存入数据区，这里只是打印输出
        StackPrint(S);
        ClearStack(S);
        if(ch != '^') ch = getchar();
    }
    DestroyStack(S);
    return OK;
}
int main()
{
    LineEdit();
    return 0;
}