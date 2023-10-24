#include<iostream>
#define Max_Vertex_Num 102
#define inp(i,x,y) for(i=x;i<=y;i++)
#define INFINITY 10000

int AM[Max_Vertex_Num][Max_Vertex_Num];
int path[Max_Vertex_Num][Max_Vertex_Num];  // 最短路径
int D[Max_Vertex_Num][Max_Vertex_Num];   // 最短距离
void FloydMinPath(int num);
void DispFloydPath(int u, int v);
void MinFloydPrint(int u, int v);
int main()
{
    int i = 0, j = 0, num = 0;
    scanf("%d",&num);
    inp(i,0,num-1)
        inp(j,0,num-1)
            scanf("%d",&AM[i][j]);
    FloydMinPath(num);
    scanf("%d%d",&i,&j);
    while(i != -1&&j != -1){
        DispFloydPath(i, j);
        scanf("%d%d",&i,&j);
    }
    return 0;
}
void FloydMinPath(int num)
{
    int i = 0, j = 0, k = 0;
    inp(i, 0, num-1)    //矩阵 D与 path初始化
        inp(j, 0, num-1){
            D[i][j] = AM[i][j];
            if(D[i][j] != INFINITY)  path[i][j] = i;     // 头节点 	    	
	        else path[i][j] = -1;	    // i到j无路径	
        }
    
    inp(k, 0, num-1)
        inp(i, 0, num-1)
            inp(j, 0, num-1)
                if(D[i][k] != INFINITY && D[k][j] != INFINITY)
                    if(D[i][j] > D[i][k] + D[k][j]){ 
                        D[i][j] = D[i][k] + D[k][j];
                        path[i][j] = path[k][j];
                    }
    return ;
}
void DispFloydPath(int u, int v)
{
    if(D[u][v] != INFINITY){
        printf("%d\n%d ",D[u][v],u);
        MinFloydPrint(u, v);	/*输出路径上的中间点*/
        printf("%d\n",v);
    }
    else printf("NO\n");
    return ;
}
void MinFloydPrint(int u, int v)    
{
    int p = path[u][v];
    if(p == u){
        return ;
    }
    MinFloydPrint(u, p);
    printf("%d ",p);
    return ;
}