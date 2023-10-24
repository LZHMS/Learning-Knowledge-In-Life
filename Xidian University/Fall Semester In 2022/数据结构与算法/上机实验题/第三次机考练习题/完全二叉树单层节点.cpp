/*
题目：输出完全二叉树的某一层
问题描述
对一棵完全二叉树，输出某一深度的所有节点，有则输出这些节点，无则输出EMPTY。
输入格式
	输入有多组数据。
每组数据第一行输入一个结点数n(1<=n<=1000)，第二行将树中的这n个节点依次输入（每个结点存储的数据是一个数字），
n个结点编号方式是层间从上到下、层内从左到右依次编号；第三行输入一个d代表深度。
当n=0时，表示输入结束。
输出格式
	每组数据在一行上输出该树中第d层的所有节点，节点间用空格隔开。每组数据输出完成后要换行。
样例输入
	4
1 2 3 4
2
0
样例输出
	2 3
样例说明
该完全二叉树的第一层是1，第二层是2 3，第三层是4；题目要求输出第二层，则输出2 3。
*/
#include<iostream>
#include<cmath>
#define Max_num 1003
int Nodes[Max_num];
int main()
{
    int n = 0;
    while(scanf("%d",&n)!=EOF && n){
        for(int i=1;i<=n;i++)
            scanf("%d",&Nodes[i]);
        int obj = 0;
        scanf("%d",&obj);
        if(pow(2,obj-1) > n) printf("EMPTY\n");
        else{
            int pos1 = pow(2,obj-1), pos2 = n < pow(2,obj)-1?n:pow(2,obj)-1;
            for(int i=pos1;i<=pos2;i++)
                printf("%d ",Nodes[i]);
        }
        printf("\n");
    }
    return 0;
}
