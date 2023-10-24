#include <stdio.h>
#include <stdlib.h>

void TraversalBiTree(char *pre, int &i, char *inorder, int &j, char *post, int &k) 
{//������չ����������У������������ͺ����������
	char ch;

	scanf("%c", &ch);
	if(ch == '.')
		return;
	else{
		pre[i] = ch;//���������������
		i++;
		TraversalBiTree(pre, i, inorder, j, post, k);
		inorder[j] = ch;//���������������
		j++;
		TraversalBiTree(pre, i, inorder, j, post, k);
		post[k] = ch;//��������������
		k++;
	}
}

void main()
{
	char pre[100], inorder[100], post[100];
	int i, j, k;

	i=j=k=0;
	TraversalBiTree(pre, i, inorder, j, post, k); //��չ����������� AB.DF..G..C.E.H..
	pre[i] = inorder[j] = post[k] = '\0';
	printf("%s\n", pre);
	printf("%s\n", inorder);
	printf("%s\n", post);
}
