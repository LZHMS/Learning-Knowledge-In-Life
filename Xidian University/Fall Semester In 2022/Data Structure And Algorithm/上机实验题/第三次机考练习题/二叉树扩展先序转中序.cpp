/*
题目：二叉树扩展先序遍历转中序遍历
问题描述
编一个程序，读入用户输入的一串扩展先序遍历字符串，根据此字符串建立一个二叉树（以指针方式存储）。 例如如下的扩展先序遍历字符串： ABC##DE#G##F### 其中“#”表示的是空格，空格字符代表空树。建立起此二叉树以后，再对二叉树进行中序遍历，输出遍历结果。
输入格式
	输入包括1行字符串,长度不超过100。
输出格式
	输出将输入字符串建立二叉树后中序遍历的序列，每个字符后面都有一个空格。每个输出结果占一行。
样例输入
	abc##de#g##f###
样例输出
	c b e g d f a
样例说明
根据给定的扩展先序遍历序列，建立对应的二叉树，然后对所得的二叉树进行中序遍历输出结果即可。
*/

#include<iostream>
#define Max_num 103
char pre[Max_num], order[Max_num], post[Max_num];
void TraverBiTree(int &i, int &j, int &k) 
{
	char ch;
	scanf("%c", &ch);
	if(ch == '#')
		return ;
	else{
		pre[i++] = ch;
		TraverBiTree(i, j, k);   // 中序需再等待一次遍历
		order[j++] = ch;
		TraverBiTree(i, j, k);
		post[k++] = ch;    // 中序需再等待两次遍历
	}
    return ;
}

int main()
{
	int i = 0, j = 0, k = 0;  // 指向前中后序
	TraverBiTree(i, j, k);
	pre[i] = order[j] = post[k] = '\0';
	//printf("%s\n%s\n%s\n", pre, order, post);
    for(int p=0;p<j;p++)
        printf("%c ",order[p]);
	return 0;
}
