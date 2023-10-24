#include<iostream>
#define inp(i,x,y) for(i=x;i<=y;i++)
int main()
{
    int m = 0,n = 0;
    while(scanf("%d%d",&m,&n)){
        if(!m&&!n) break;
        int cnt = 1, i;
        int l = 2*m, r = 2*m+1;
        while(l <= n){
            inp(i,l,r){
                if(i>n) break;
                else cnt++;
            }
            if(i > n) break;
            l = 2*l;r = 2*r+1;
        }
        printf("%d\n",cnt);
    }
    return 0;
}