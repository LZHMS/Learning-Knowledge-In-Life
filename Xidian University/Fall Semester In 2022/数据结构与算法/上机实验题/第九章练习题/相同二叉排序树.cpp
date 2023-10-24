#include<iostream>
#include<cstring>
using namespace std;

typedef struct BiTNode
{
	char elem;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

int len, flag = 0;
void BiTNodeInsert(BiTree &T, char elem);
void CreateTree(BiTree &T, char *e);   //建树
void PreTranverse(BiTree T, BiTree B);   //先序遍历记录相同节点个数
void BiTreeFree(BiTree &T);
int main()
{
	int n=0;
	char ch, data[21], stemp[21];
	
	while(scanf("%d",&n) != EOF && n != 0)
	{
        BiTree T = NULL, B = NULL;
		getchar();
	    cin >> data;
		len = strlen(data);
	    CreateTree(T, data);  

	    while(n--)
	    {
		  flag = 0, B = NULL;
		  cin >> stemp;
		  CreateTree(B, stemp);   //建立将要被判断的树
		  PreTranverse(T, B);    //判断
          BiTreeFree(B);

		  if(flag == len)//相同节点数等于节点数
			 printf("YES\n");
		  else
			printf("NO\n");
	    }
	}
	return 0;
}
void BiTNodeInsert(BiTree &T, char elem)
{
	if(!T)     // 空树
	{
		T=(BiTree)malloc(sizeof(BiTNode));
		T->elem = elem;
		T->lchild = T->rchild=NULL;
	}
	else if(elem < T->elem)
		BiTNodeInsert(T->lchild, elem);
	else if(elem>T->elem)
		BiTNodeInsert(T->rchild, elem);
    return ;
}
void CreateTree(BiTree &T, char *e)   //建树
{
	for(int i=0;i<len;i++, e++)
		BiTNodeInsert(T, *e);
	return ;
}
void PreTranverse(BiTree T, BiTree B)   //先序遍历记录相同节点个数
{
	if(T && B)
	{
		if(T->elem == B->elem)
		{
	       flag++;      
		   PreTranverse(T->lchild, B->lchild);     // 左子树
		   PreTranverse(T->rchild, B->rchild);     // 右子树
		}
	}
    return ;
}
void BiTreeFree(BiTree &T)
{
    if(T){
        BiTreeFree(T->lchild);
        BiTreeFree(T->rchild);
        free(T);T = NULL;
    }
    return ;
}
