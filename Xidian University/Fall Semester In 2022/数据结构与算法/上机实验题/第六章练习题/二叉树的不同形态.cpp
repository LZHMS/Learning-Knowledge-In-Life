//Creat by 绝迹
#include <iostream>
#include <cstdlib>
using namespace std;
//----------------二叉树不同形态-----------------//
//定义二叉树结点
typedef struct BTreeNode
{
    int data;
    struct BTreeNode *lchild,*rchild;
}BTreeNode,*BTree;

int ce_xu[1025];
int in_tr[1025];
BTree CreateTree(int l1,int r1,int l2,int r2)
{
    if (l2 > r2)      // 层序遍历完
        return NULL;
    else
    {
        BTree root = (BTree) malloc(sizeof(BTreeNode));

        int i=0, j=0,flag = 0;
        for (i = l1; i <= r1; ++i) {
            for (j = l2; j <= r2; ++j) {
                if (ce_xu[i] == in_tr[j]) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
                break;
        }

        root->data = ce_xu[i];
        root->lchild = CreateTree(l1 + 1, r1, l2, j - 1);
        root->rchild = CreateTree(l1 + 1, r1, j + 1, r2);
        return root;
    }
}

void postorder(BTree BT)
{
    if(BT)
    {
        postorder(BT->lchild);
        postorder(BT->rchild);
        printf("%d ",BT->data);
    }
    return ;
}

void preorder(BTree BT)
{
    if(BT)
    {
        printf("%d ",BT->data);
        preorder(BT->lchild);
        preorder(BT->rchild);
    }
    return ;
}

void printleaf(BTree BT)
{
    if (BT == NULL)
        return;
    else
    {
        if (BT->lchild == NULL && BT->rchild == NULL)
        {
            printf("%d ",BT->data);
        }
        printleaf(BT->lchild);
        printleaf(BT->rchild);
    }
    return ;
}

int main()
{
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> ce_xu[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> in_tr[i];
    }
    BTree BT = NULL;
    BT = CreateTree(0,n-1,0,n-1);
    
    printleaf(BT);
    printf("\n");
	preorder(BT);
    printf("\n");
    postorder(BT); 
    return 0;
}

