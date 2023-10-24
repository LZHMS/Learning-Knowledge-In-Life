#include<iostream>
typedef struct BiTNode{
    int elem;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

bool CreateTree(BiTree &T, int n);
bool BiTNodeInsert(BiTree &T, int elem);
void TranverseOp(int elem);
void PreTranverse(BiTree T, void (*Visit)(int elem));
void OrderTranverse(BiTree T, void (*Visit)(int elem));
void PostTranverse(BiTree T, void (*Visit)(int elem));
int main()
{
    int i=0, j=0, n=0;
    scanf("%d",&n);
    BiTree T = NULL;
    if(!CreateTree(T, n)) return 0;
    PreTranverse(T, TranverseOp);
    printf("\n");
    OrderTranverse(T, TranverseOp);
    printf("\n");
    PostTranverse(T, TranverseOp);
    printf("\n");
    return 0;
}
bool CreateTree(BiTree &T, int n)
{
    for(int i=0,temp=0;i<n;i++){
        scanf("%d", &temp);
        if(!BiTNodeInsert(T, temp)) return false;
    }
    return true;
}
bool BiTNodeInsert(BiTree &T, int elem)
{
    if(!T){
        T = (BiTree)malloc(sizeof(BiTNode));
        T->elem = elem;
        T->lchild = T->rchild = NULL;
    }else if(elem < T->elem)
        BiTNodeInsert(T->lchild, elem);
    else if(elem > T->elem)
        BiTNodeInsert(T->rchild, elem);
    return true;
}
void TranverseOp(int elem)
{
    printf("%d ",elem);
    return ;
}
void PreTranverse(BiTree T, void (*Visit)(int elem))
{
    if(T){
        Visit(T->elem);
        PreTranverse(T->lchild, Visit);
        PreTranverse(T->rchild, Visit);
    }
    return ;
}
void OrderTranverse(BiTree T, void (*Visit)(int elem))
{
    if(T){
        OrderTranverse(T->lchild, Visit);
        Visit(T->elem);
        OrderTranverse(T->rchild, Visit);
    }
    return ;
}
void PostTranverse(BiTree T, void (*Visit)(int elem))
{
    if(T){
        PostTranverse(T->lchild, Visit);
        PostTranverse(T->rchild, Visit);
        Visit(T->elem);
    }
    return ;
}