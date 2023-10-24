#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;

typedef char SElemType;    //栈元素类型
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
SElemType Pop(SqStack &S)
{
    // 栈空标志
    if(S.top == S.base) return ERROR;
    return *--S.top;
}
Status StackEmpty(SqStack S)
{
    if(S.base == S.top) return true;
    return false;
}
Status paren()
{

    //构造字符栈
    SqStack S;
    InitStack(S);
    SElemType ch;
    ch = getchar();
    while(ch != '\n'){
        switch (ch) { //左括号直接进栈；右括号若不栈顶失配，则表达式必不匹配
            case '(': case '[': case '{': Push(S, ch); break;
            case ')': if ((StackEmpty(S)) || ('(' != Pop(S))) return false; break;
            case ']': if ((StackEmpty(S)) || ('[' != Pop(S))) return false; break;
            case '}': if ((StackEmpty(S)) || ('{' != Pop(S))) return false; break;
            default: break; //非括号字符一律忽略
        }
        ch = getchar();
    }
    return StackEmpty(S);
}
int main()
{
    if(paren()) cout << "right" << endl;
    else cout << "wrong" << endl;
    return 0;
}