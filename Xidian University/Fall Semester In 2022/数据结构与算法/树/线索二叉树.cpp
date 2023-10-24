#include<iostream>
#include<cstdlib>
using namespace std;
//--------------二叉树的二叉线索存储表示------------------//   
typedef char TElemType;
typedef bool Status;

typedef enum PointerTag{Link=0, Thread=1}PointerTag;  // Link:指针，Thread:线索
typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag LTag, RTag;    // 左右标志
}BiThrNode, *BiThrTree;

/*-------------------------线索二叉树相关操作函数---------------------------*/
// 二叉树创建函数
Status CreateBiTree(BiThrTree &T);
// 二叉树遍历算子
Status TreeTransOperator(TElemType e);
// 中序二叉树线索化
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T);
Status InThreading(BiThrTree p, BiThrTree &pre);
// 先序二叉树线索化
Status PreOrderThreading(BiThrTree &Thrt, BiThrTree T);
Status PreThreading(BiThrTree p, BiThrTree &pre);
// 中序遍历线索二叉树——遍历方式较线索化遍历更快
Status InOrderTraverseThr(BiThrTree T, Status (*Visit)(TElemType e));
//--------------中序线索二叉树中查找节点的前驱和后继----------------
BiThrTree InorderPreNode(BiThrTree p);
BiThrTree InorderPostNode(BiThrTree p);
//--------------后序线索二叉树中查找节点的前驱和后继----------------
BiThrTree PostorderPreNode(BiThrTree p);
Status FreeBiThrTree(BiThrTree &Thrt);
    
int main()
{
    BiThrTree T, BTHead;
    if(!CreateBiTree(T)){    // 创建二叉树
        cout << "Binary Tree Create Error!\n";
        return 0;
    }
    InOrderThreading(BTHead, T);
    InOrderTraverseThr(BTHead, TreeTransOperator);
    return 0;
}
Status TreeTransOperator(TElemType e)    // 二叉树遍历算子
{
    // 对数据元素操作的应用函数
    cout << e << " ";
    return true;
}
/*---------------------二叉树创建函数------------------*/
Status CreateBiTree(BiThrTree &T)
{
    // 递归读入二叉树的各元素，因此最开始的T还是指向根节点
    TElemType ch;
    cin >> ch;
    if (ch == '.') T = NULL;
    else {
        if (!(T = (BiThrTree)malloc(sizeof(BiThrNode)))) return false;
        T->data = ch;          // 生成根节点
        T->LTag = T->RTag = Link;
        CreateBiTree(T->lchild);   // 递归构造左子树
        CreateBiTree(T->rchild);   // 递归构造右子树
    }
    return true;
}
Status InOrderTraverseThr(BiThrTree T, Status (*Visit)(TElemType e))
{
    // T指向头节点，头节点的左链lchild指向根节
    // 中序遍历二叉线索树的非递归算法，对每个数据调用Visit函数进行遍历算子
    BiThrTree p = T->lchild;
    while(p!=T)
    {
        while(p->LTag == Link) p = p->lchild;
        if(!Visit(p->data)) return false;
        while(p->RTag == Thread && p->rchild != T){
            p = p->rchild;
            Visit(p->data);
        }
        p = p->rchild; 
    }
    return true;
}

Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
    // 中序遍历二叉树T，并将其中序线索化，Thrt指向头节点
    if(!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))){
        cout << "Error for space allocation!\n";
        return false;
    }
    Thrt->LTag = Link; Thrt->RTag = Thread;    // 头节点的左链是指向根节点的指针，右链是指向尾节点的后继
    Thrt->rchild = Thrt;        // 初始右指针回指
    if(!T) Thrt->lchild = Thrt;     // 若二叉树为空则左指针回指
    else{
        Thrt->lchild = T;
        BiThrTree pre = Thrt;    // pre指向刚刚访问过的节点——当前节点的上一个节点
        InThreading(T, pre);
        pre->rchild = Thrt;     // 最后一个节点的右链线索化
        pre->RTag = Thread;
        Thrt->rchild = pre;
    }
    return true;
}
Status InThreading(BiThrTree p, BiThrTree &pre)  
{   
    // pre通过引用来在递归线索化过程中不断更新
    if(p){
        InThreading(p->lchild, pre);    // 左子树线索化
        if(!p->lchild){           // 前驱线索
            p->LTag = Thread;
            p->lchild = pre;     
        }
        if(!pre->rchild){    // 后继线索
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;     // 保持pre指向p的前驱
        InThreading(p->rchild, pre);     // 右子树线索化
    }
    return true;
}


//--------------中序线索二叉树中查找节点的前驱和后继----------------
BiThrTree InorderPreNode(BiThrTree p)
{
    // 寻找节点的中序前驱节点
    // 左子树的最右下的节点
    BiThrTree pre = p->lchild;
    if(p->LTag == 0)   // 有左孩子
        while(pre->RTag == 0)
            pre = pre->rchild;
    return pre;
}
BiThrTree InorderPostNode(BiThrTree p)
{
    // 寻找节点的中序后继节点
    // 右子树的最左下的节点
    BiThrTree post = p->rchild;
    if(p->RTag == 0)   // 有右孩子
        while(post->LTag == 0)
            post = post->lchild;
    return post;
}



//--------------后序线索二叉树中查找节点的前驱和后继----------------
BiThrTree PostorderPreNode(BiThrTree p)
{
    // 寻找节点的后序前驱节点
    BiThrTree pre;
    if(p->LTag == 1) pre = p->lchild;    // 无左孩子时对应lchild存储的便是前驱
    else if(p->LTag == 0){      // 有左孩子时判断有无右孩子
        if(p->RTag == 0)    // 有右孩子
            pre = p->rchild;   // 以右孩子为前驱
        else if(p->RTag ==  1)  // 无右孩子
            pre = p->lchild;   // 以左孩子为前驱
    }
    return pre;
}
/*BiThrTree PostorderPostNode(BiThrTree p, BiThrTree T)
{
    // 寻找节点的后序后继节点
    if(p == T->lchild) return NULL;
    if(p->Rtag == 1) return p->rchild;
    else if(p->RTag == 0){

    }
}*/



Status FreeBiThrTree(BiThrTree &Thrt)
{
    BiThrTree T = Thrt->lchild;
    while(T->LTag == 0) T = T->lchild;   // 中序遍历的第一个节点
    while(T != Thrt){
        // 在中序遍历中，T相对来说是第一个节点，post是后继节点，因此free(T)
        BiThrTree post = T->rchild;  // 获取T的后继节点
        if(T->RTag == 0) // 有右孩子
            while(post->LTag == 0)  // 在有有孩子的情况下寻找后继节点
                post = post->lchild;
        free(T);
        T = post;
    }
    free(Thrt);
    Thrt = NULL;
    return true;
}

