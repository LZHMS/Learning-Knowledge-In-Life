#include<iostream>
#include<algorithm>
#define Max_Vertex_Num 34
#define inp(i,x,y) for(i=x;i<=y;i++)

int AM[Max_Vertex_Num][Max_Vertex_Num];
int Order[Max_Vertex_Num];
bool Visit[Max_Vertex_Num];
void DFSTranvers(int p, int num, int &cnt);
int main()
{
    int vexnum = 0, edgenum = 0, i=0;
    scanf("%d%d",&vexnum,&edgenum);
    inp(i,0,edgenum-1){
        int p,q;
        scanf("%d%d",&p,&q);
        AM[p][q] = AM[q][p] = 1;
    }
    int cnt = 0, pvexnum = 0;
    inp(i,1,vexnum){
        if(Visit[i]) continue;
        Visit[i] = true;
        pvexnum = 1; // 连通子图的顶点数
        DFSTranvers(i, vexnum, pvexnum);
        Order[cnt++] = pvexnum;
    }
    std::sort(Order, Order+cnt);
    printf("%d\n",cnt);
    inp(i,0,cnt-1)
        printf("%d ",Order[i]);
    return 0;
}
void DFSTranvers(int p, int num, int &cnt)
{
    int i=0;
    inp(i,1,num){
        if(!Visit[i]&&AM[p][i]){
            Visit[i]=true;
            DFSTranvers(i, num, ++cnt);
        }
    }
    return ;
}