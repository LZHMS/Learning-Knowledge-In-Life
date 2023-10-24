#include<iostream>
#include<queue>
#define inp(i,x,y) for(i=x;i<=y;i++)
#define Max_Vertex_Num 104

int AM[Max_Vertex_Num][Max_Vertex_Num];
bool Visit[Max_Vertex_Num];
int main()
{
    int i=0, j=0, vexnum=0, cnt=1;
    scanf("%d",&vexnum);
    inp(i,1,vexnum)
        inp(j,1,vexnum)
            scanf("%d",&AM[i][j]);
    std::queue<int> Q;Q.push(1);
    Visit[1]=true;
    while(!Q.empty()){
        int head = Q.front(),sign = 0;Q.pop();
        printf("%d ",head);
        inp(i,1,vexnum){
            if(!Visit[i]&&AM[head][i]){
                Visit[i] = true;
                Q.push(i);
            }
            if(!sign && !Visit[i]) sign = i;
        }
        if(Q.empty() && sign){
            cnt++;
            Q.push(sign);
            Visit[sign] = true;
        }
    }
    printf("\n%d\n",cnt);
    return 0;
}