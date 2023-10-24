#include<iostream>
#include<algorithm>
#define Max_Vertex_Num 34
#define inp(i,x,y) for(i=x;i<=y;i++)

struct Edge{
    int lvex;
    int rvex;
    int weight;
}edge[Max_Vertex_Num];
int fa[Max_Vertex_Num];    // 父亲节点

bool cmp(Edge a, Edge b){
	return a.weight < b.weight;
}
int find_father(int x);
bool KruskalMinitree(int n,int m);
int main()
{
    int vexnum = 0, edgenum = 0, i=0;
    scanf("%d%d",&vexnum,&edgenum);
    inp(i,1,edgenum)
        scanf("%d%d%d",&edge[i].lvex,&edge[i].rvex,&edge[i].weight);
    inp(i,1,vexnum) fa[i]=i;
    std::sort(edge+1,edge+edgenum+1,cmp);//排序
    KruskalMinitree(vexnum, edgenum);
    return 0;
}
int find_father(int x)
{
	if(x == fa[x]) return x;
	return find_father(fa[x]);
}
bool KruskalMinitree(int n,int m)
{
	int i=0, num_Edge = 0;//边的数目
	inp(i,1,m){
		int flvex = find_father(edge[i].lvex);
		int frvex = find_father(edge[i].rvex);
		if(flvex != frvex){
			fa[flvex] = frvex;  //合并
            int p = edge[i].lvex < edge[i].rvex?edge[i].lvex:edge[i].rvex;
            int q = edge[i].lvex + edge[i].rvex - p;
            printf("%d %d %d\n",p,q,edge[i].weight);
			num_Edge++;
			if(num_Edge==n-1) break;
		}
	}
	if(num_Edge!=n-1) return false;//退出条件
	else return true;
}