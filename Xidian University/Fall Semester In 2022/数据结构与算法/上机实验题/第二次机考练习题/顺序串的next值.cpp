#include <iostream>
#include<cstring>
using namespace std;
#define Max_num 103
int main()
{
	int next[Max_num]={0}, n = 0;
	char alpha[Max_num], T[Max_num];
	scanf("%d\n",&n);
    for(int i=0;i<n;i++){
        scanf("%c",&alpha[i]);
        T[i] = alpha[i];
        getchar();
    }
	next[0]=-1;
	int i = 0, j = -1;
	while(i < n)
	{
		if(j==-1||T[i]==T[j]){
    		next[++i]=++j; //前移一位，j表示相等前缀码的个数
		}
		else j=next[j];
	}   
	for(i = 0;i < n;i++)
		printf("%d ",next[i]);
  return 0;	
}
