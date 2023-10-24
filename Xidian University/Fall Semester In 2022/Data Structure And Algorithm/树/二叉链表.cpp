#include<iostream>
#include"Stack.h"
using namespace std;
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

//--------------------递归遍历算法-------------------------//
Status PreOrderTranRecursion(BiTree T, Status(*Visit)(TElemType e))
{
    /*---------------先序遍历二叉树的递归算法-------------------*/
    // 采用二叉链表存储结构，Visit是对数据元素操作应用的函数
    // 对于一个节点而言，一旦判断节点的三个单元为空即可返回递归上层
    if (T) {   // T所指节点非空
        if (Visit(T->data)) {      // 调用操作函数，Visit采用函数指针，指向操作函数
            if (PreOrderTranRecursion(T->lchild, Visit)) {    // 递归调用：Visit所指函数也进行递归
                if (PreOrderTranRecursion(T->rchild, Visit))  return true;
            }
        }
        return false;
    }
    else return true;
}
Status InOrderTranRecursion(BiTree T, Status(*Visit)(TElemType e))
{
    /*---------------中序遍历二叉树的递归算法-------------------*/
    // 采用二叉链表存储结构，Visit是对数据元素操作应用的函数
    // 对于一个节点而言，一旦判断节点的三个单元为空即可返回递归上层
    if (T) {   // T所指节点非空
        if (InOrderTranRecursion(T->lchild, Visit)) {      // 调用操作函数，Visit采用函数指针，指向操作函数
            if (Visit(T->data)) {    // 递归调用：Visit所指函数也进行递归
                if (InOrderTranRecursion(T->rchild, Visit))  return true;
            }
        }
        return false;
    }
    else return true;
}
Status PostOrderTranRecursion(BiTree T, Status(*Visit)(TElemType e))
{
    /*---------------后序遍历二叉树的递归算法-------------------*/
    // 采用二叉链表存储结构，Visit是对数据元素操作应用的函数
    // 对于一个节点而言，一旦判断节点的三个单元为空即可返回递归上层
    if (T) {   // T所指节点非空
        if (PostOrderTranRecursion(T->lchild, Visit)) {      // 调用操作函数，Visit采用函数指针，指向操作函数
            if (PostOrderTranRecursion(T->rchild, Visit)) {    // 递归调用：Visit所指函数也进行递归
                if (Visit(T->data))  return true;
            }
        }
        return false;
    }
    else return true;
}
//--------------------递归遍历算法-------------------------//

//--------------------非递归遍历算法-------------------------//
//---------------------先序遍历二叉树------------------------//
Status PreOrderTranverse_1(BiTree T, Status(*Visit)(TElemType e))
{
    // 先序遍历二叉树T的非递归算法一
    mystack<BiTree> S; S.Init(); //创建并初始化遍历二叉链表所需要的栈
    S.Push(T);    // 根指针进栈
    BiTree p;     // 创建二叉树游标指针
    while (!S.Empty()) {
        while (S.Top(p) && p) {
            if (!Visit(p->data)) return false;
            S.Push(p->lchild);
        }
        S.Pop(p);    // 将向左尽头的空指针弹出
        if (!S.Empty()) {
            S.Pop(p);   // 根节点出栈
            S.Push(p->rchild);   // 遍历后转向
        }
    }
    return true;
}
Status PreOrderTranverse_2(BiTree T, Status(*Visit)(TElemType e))
{
    // 先序遍历二叉树T非递归算法二
    mystack<BiTree> S; S.Init(); //创建遍历二叉链表所需要的栈
    BiTree p = T;
    while (p || !S.Empty()) {
        if (p) {
            if (!Visit(p->data)) return false;
            S.Push(p);       // 根指针进栈
            p = p->lchild;    // 遍历左子树,当p=NULL时未进栈
        }
        else {
            S.Pop(p);
            p = p->rchild;
        }
    }
    return true;
}
//---------------------中序遍历二叉树------------------------//
Status InOrderTranverse_1(BiTree T, Status(*Visit)(TElemType e))
{
    // 中序遍历二叉树T的非递归算法一
    mystack<BiTree> S; S.Init(); //创建并初始化遍历二叉链表所需要的栈
    S.Push(T);    // 根指针进栈
    BiTree p;     // 创建二叉树游标指针
    while (!S.Empty()) {
        while (S.Top(p) && p) S.Push(p->lchild);   // 向左走到尽头
        S.Pop(p);    // 将向左尽头的空指针弹出
        if (!S.Empty()) {    
            S.Pop(p);   // 根节点出栈
            if (!Visit(p->data)) return false;   //遍历
            S.Push(p->rchild);   // 遍历后转向
        }
    }
    return true;
}

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
//---------------------后序遍历二叉树------------------------//
Status PostOrderTranverse_1(BiTree T, Status(*Visit)(TElemType e))
{
    // 后序遍历二叉树T的非递归算法一
    mystack<BiTree> S; S.Init(); //创建并初始化遍历二叉链表所需要的栈
    S.Push(T);    // 根指针进栈
    BiTree p,lastp = NULL;     // 创建二叉树游标指针
    while (!S.Empty()) {
        while (S.Top(p) && p) S.Push(p->lchild);   // 向左走到尽头
        S.Pop(p);    // 将向左尽头的空指针弹出
        if (!S.Empty()) {
            S.Top(p);   // 获取根节点 
            if (p->rchild == NULL||p->rchild == lastp) {   // 节点信息无用时直接出栈
                S.Pop(p);  // 此时结点才可出栈
                lastp = p;
                if (!Visit(p->data)) return false;   //遍历
                S.Push(NULL);       //保证返回上层结点而不是下一轮继续向左走
            }else S.Push(p->rchild);
        }
    }
    return true;
}
Status PostOrderTranverse_2(BiTree T, Status(*Visit)(TElemType e))
{
    // 后序遍历二叉树T非递归算法二
    mystack<BiTree> S; S.Init(); //创建遍历二叉链表所需要的栈
    BiTree p = T,lastp = NULL;
    while (p || !S.Empty()) {
        if (p) {
            S.Push(p);       // 根指针进栈
            p = p->lchild;    // 遍历左子树,当p=NULL时未进栈
        }
        else {
            S.Top(p);
            if (p->rchild == NULL || p->rchild == lastp) {
                S.Pop(p);
                if (!Visit(p->data)) return false;
                lastp = p;
                p = NULL;          // 往回溯，置于NULL
            }
            else p = p->rchild;        // 控制右移转向
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
    if (ch == '.') T = NULL;
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
    cout << "Input binary tree elements in order: (note: '.' means empty tree)\n";
    if (!CreateBiTree(T)) {
        cout << "Space allocate error!\n";
        return 0;
    }
    cout << "------------------Binary Recursion Traverse----------------------\n";
    cout << "Binary Tree First Order Traverse:\n";
    PreOrderTranRecursion(T, TreeTransOperator);
    cout << endl << "Binary Tree Middle Order Traverse:\n";
    InOrderTranRecursion(T, TreeTransOperator);
    cout << endl << "Binary Tree Post Order Traverse:\n";
    PostOrderTranRecursion(T, TreeTransOperator);

    cout << endl << "------------------Binary NonRecursion Traverse-------------------\n";
    cout << "Binary Tree First Order Traverse 1:\n";
    PreOrderTranverse_1(T, TreeTransOperator);
    cout << endl << "Binary Tree First Order Traverse 2:\n";
    PreOrderTranverse_2(T, TreeTransOperator);
    cout << endl << "Binary Tree Middle Order Traverse 1:\n";
    InOrderTranverse_1(T, TreeTransOperator);
    cout << endl << "Binary Tree Middle Order Traverse 2:\n";
    InOrderTranverse_2(T, TreeTransOperator);
    cout << endl << "Binary Tree Post Order Traverse 1:\n";
    PostOrderTranverse_1(T, TreeTransOperator);
    cout << endl << "Binary Tree Post Order Traverse 2:\n";
    PostOrderTranverse_2(T, TreeTransOperator);
    cout << endl;
    return 0;
}