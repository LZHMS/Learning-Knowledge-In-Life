#include<cstdlib>
//-----------------------自定义栈模板类--------------
typedef bool Status;

// 抽象数据类型定义
template<class TElemType>
struct SqNode{
    TElemType data;
    struct SqNode *next, *pre;    // 基于双向链表模拟栈
};

template<class TElemType>
class mystack
{
    public:
        struct SqNode<TElemType> *base,*top;   // 栈底和栈顶指针
        Status Init()
        {
            if(!(base = (struct SqNode<TElemType>*)malloc(sizeof(struct SqNode<TElemType>)))) return false;
            top = base;    // 判断栈空标志
            base->data = 0;   // 栈顶结点数据域记录栈中元素数
            base->next = NULL;
            base->pre = NULL;
            return true;
        }
        Status Push(TElemType e)
        {
            struct SqNode<TElemType> *stemp;
            if(!(stemp=(struct SqNode<TElemType>*)malloc(sizeof(struct SqNode<TElemType>)))) return false;
            top->next = stemp;
            stemp->data = e;
            stemp->pre = top;
            stemp->next = NULL;
            top = top->next; // 移动top指针始终位于栈顶

            base->data++;      // 栈元素计数
            return true;
        }
        Status Pop(TElemType &e)
        {
            if(top == base) return false;  // 栈空
            struct SqNode<TElemType> *stemp = top;
            top = top->pre;
            top->next = NULL;
            e = stemp->data;
            free(stemp);

            base->data--;
            return true;
        }
        Status Top(TElemType &p)
        {
            if(top == base) return false;
            p = top->data;
            return true;
        }

        Status Empty()
        {
            if(top == base) return true;
            else return false;
        }
        int Size()
        {
            return base->data;
        }
};