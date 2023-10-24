#include<iostream>
#define inp(i,x,y) for(i=x;i<=y;i++)
#define Max_Vertex_Num 21
#define INFINITY 0

int AM[Max_Vertex_Num][Max_Vertex_Num];
void DijsMinPath(int vexnum, int v0);
int main()
{
    int i=0, vexnum, edgenum, svex;
    scanf("%d%d%d",&edgenum,&vexnum, &svex);
    inp(i,1,edgenum){
        int p,q,w;
        scanf("%d%d%d",&p,&q,&w);
        AM[p][q] = w;
    }
    DijsMinPath(vexnum, svex);
    return 0;
}
void DijsMinPath(int vexnum, int v0)
{
    int D[24];
    bool final[24];
    int v = 0, w = 0, i = 0;
    inp(v, 1, vexnum){
        final[v] = false;
        D[v] = AM[v0][v];
    }
    final[v0] = true;
    inp(i,2,vexnum){
        int min_path = 3000;   
        inp(w,1,vexnum){
            if(!final[w] && D[w] != INFINITY && D[w] < min_path){
                v = w;
                min_path = D[w];
            }
        }
        if(min_path != 3000) final[v] = true;    
        else break;

        inp(w,1,vexnum){
            if(!final[w] && AM[v][w] != INFINITY && (!D[w]||min_path + AM[v][w] < D[w]))
                D[w] = min_path + AM[v][w];
        }
    }
    int sign = 1, ans = 0;
    inp(i, 1, vexnum){
        if(i == v0) continue;   // 不包括源点
        if(final[i]) ans = ans>D[i]?ans:D[i];
        else{
            sign = 0;
            break;
        }
    }
    if(sign) printf("%d\n",ans);
    else printf("-1\n");
    return ;
}