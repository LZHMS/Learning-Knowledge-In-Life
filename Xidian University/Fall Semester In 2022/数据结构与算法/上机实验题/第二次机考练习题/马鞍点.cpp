#include<iostream>
#define Max_num 104
#define inp(i,x,y) for(i=x;i<=y;i++)
#define dep(i,x,y) for(i=x;i>=y;i--)
int AM[Max_num][Max_num];
int main()
{
    int i=0,j=0,k=0,col = 0, row = 0,sign = 0;
    scanf("%d%d",&row,&col);

    inp(i,1,row)
        inp(j,1,col)
            scanf("%d",&AM[i][j]);

    inp(i,1,row){
        int minpos = 1, maxpos = 1;   // 行最小值，列最大值
        inp(j,2,col)
            if(AM[i][j] < AM[i][minpos]) minpos = j;

        inp(k,1,col){
            maxpos = 1;
            if(AM[i][k] == AM[i][minpos]){   // 查多个最小值
                inp(j,2,row)
                    if(AM[j][k] > AM[maxpos][k]) maxpos = j;
                
                if(maxpos == i){
                    sign = 1;
                    printf("%d %d %d\n",i,k,AM[i][k]);
                }
            }
        }
    }
    if(!sign) printf("NO\n");
    return 0;
}