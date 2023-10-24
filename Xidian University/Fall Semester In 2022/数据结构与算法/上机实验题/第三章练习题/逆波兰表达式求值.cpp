#include<iostream>
#include<cstring>
int main()
{
	char str[100];
	int top = -1, stack[100];
	scanf("%s",str);
	for(int i=0;str[i]!=0;i++)
	{
      if(str[i]>='0' && str[i]<='9')   //操作数
		  stack[++top] = str[i]-'0';
	  else{
		  int t1 = stack[top--], t2 = stack[top--];
		  if(str[i] == '+')
			  stack[++top] = t2 + t1;    //运算结果入栈
		  else if(str[i] == '-')
			  stack[++top] = t2 - t1;
		  else if(str[i] == '*')
			  stack[++top] = t2 * t1;
		  else if(str[i] == '/')
			  stack[++top] = t2 / t1;
	  }
	}
	printf("%d\n", stack[top]);
	return 0;
}