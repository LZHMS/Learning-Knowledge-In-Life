#include<iostream>
#define Max_Vertex_Num 102
#define inp(i,x,y) for(i=x;i<=y;i++)

int AM[Max_Vertex_Num][Max_Vertex_Num];
int Order[Max_Vertex_Num], Top = 0;
bool Visit[Max_Vertex_Num];

void DFSTranvers(int p, int num);
int main()
{
    int i = 0, j = 0, num = 0;
    scanf("%d",&num);
    inp(i,1,num)
        inp(j,1,num)
            scanf("%d",&AM[i][j]);

    int cnt = 0;  // 连通分量数
    inp(i,1,num){
        if(Visit[i]) continue;
        Visit[i] = true;
        Order[++Top] = i;
        DFSTranvers(i, num);
        cnt++;
    }
    inp(i,1,Top){
        printf("%d ",Order[i]);
    }
    printf("\n%d\n",cnt);
    return 0;
}
void DFSTranvers(int p, int num)  // p当前节点
{
    int i = 0;
    inp(i,1,num){
        if(!Visit[i]&&AM[p][i]){
            Visit[i] = true;
            Order[++Top] = i;
            DFSTranvers(i, num);
        }
    }
    return ;
}

