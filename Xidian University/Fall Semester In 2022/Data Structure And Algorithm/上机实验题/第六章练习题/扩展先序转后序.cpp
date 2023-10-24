#include<iostream>
#include<cstdlib>
using namespace std;
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

//----------二叉树的二叉链表存储表示--------------
typedef char TElemType;
typedef bool Status;
// 树节点定义
typedef struct BiTNode {
    TElemType data;
    struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

Status TreeTransOperator(TElemType e)    // 二叉树遍历算子
{
    // 对数据元素操作的应用函数
    cout << e << " ";
    return true;
}

//--------------------非递归遍历算法-------------------------//
//---------------------中序遍历二叉树------------------------//
Status InOrderTranverse_2(BiTree T, Status(*Visit)(TElemType e))
{
    // 中序遍历二叉树T非递归算法二
    mystack<BiTree> S; S.Init(); //创建遍历二叉链表所需要的栈
    BiTree p = T;
    while (p || !S.Empty()) {
        if (p) {
            S.Push(p);       // 根指针进栈
            p = p->lchild;    // 遍历左子树
        }
        else {
            S.Pop(p);
            if (!Visit(p->data)) return false;
            p = p->rchild;
        }
    }
    return true;
}

/*---------------------二叉树创建函数------------------*/
Status CreateBiTree(BiTree& T)
{
    // 递归读入二叉树的各元素，因此最开始的T还是指向根节点
    TElemType ch;
    cin >> ch;
    if (ch == '#') T = NULL;
    else {
        if (!(T = (BiTree)malloc(sizeof(BiTNode)))) return false;
        T->data = ch;          // 生成根节点
        CreateBiTree(T->lchild);   // 递归构造左子树
        CreateBiTree(T->rchild);   // 递归构造右子树
    }
    return true;
}

int main()
{
    BiTree T;    // 构造一棵二叉树
    //cout << "Input binary tree elements in order: (note: '.' means empty tree)\n";
    if (!CreateBiTree(T)) {
        cout << "Space allocate error!\n";
        return 0;
    }
    //cout << "------------------Binary Recursion Traverse----------------------\n";
    //cout << "Binary Tree First Order Traverse:\n";
    //PreOrderTranRecursion(T, TreeTransOperator);
    //cout << endl << "Binary Tree Middle Order Traverse:\n";
    //InOrderTranRecursion(T, TreeTransOperator);
    /*cout << endl << "Binary Tree Post Order Traverse:\n";
    PostOrderTranRecursion(T, TreeTransOperator);

    cout << endl << "------------------Binary NonRecursion Traverse-------------------\n";
    cout << "Binary Tree First Order Traverse 1:\n";
    PreOrderTranverse_1(T, TreeTransOperator);
    cout << endl << "Binary Tree First Order Traverse 2:\n";
    PreOrderTranverse_2(T, TreeTransOperator);
    cout << endl << "Binary Tree Middle Order Traverse 1:\n";
    InOrderTranverse_1(T, TreeTransOperator);
    cout << endl << "Binary Tree Middle Order Traverse 2:\n";*/
    InOrderTranverse_2(T, TreeTransOperator);
    /*cout << endl << "Binary Tree Post Order Traverse 1:\n";
    PostOrderTranverse_1(T, TreeTransOperator);
    cout << endl << "Binary Tree Post Order Traverse 2:\n";
    PostOrderTranverse_2(T, TreeTransOperator);
    cout << endl;*/
    return 0;
}