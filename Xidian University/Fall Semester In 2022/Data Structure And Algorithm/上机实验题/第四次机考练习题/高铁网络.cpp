/*
高铁网络
描述：
国家建设高铁网络，网络由一些连接城市的高铁线路构成。现有高铁建设情况可列为一张统计表，
表中列出了每一条高铁线路直接连接的两个城市。国家的建设目标是全国每两个城市之间都可以实现高铁交通（但不一定有直接的高铁线路相连，只要能间接通过高铁线路可达即可）。
问最少还要建设多少条高铁线路？
输入说明：
测试用例的第1行给出两个正整数，分别是城市数目N(<1000)和现有高铁线路数目M。随后的M行对应M条高铁线路，每行给出一对正整数，
分别是该条高铁线路直接连接的两个城市的编号。为简单起见，城市从1到N编号。
输出说明：
在一行上输出最少还需要建设多少条高铁线路。
输入样例：
9 8
1 2
1 3
2 4
3 4
5 7
5 6
6 7
8 9
输出样例：
2
实现提示：
该问题实质为求连通分量的个数减一，可用深度优先或广度优先搜索求解，也可用MFSet求解。
*/
#include<iostream>
#include<algorithm>
#define Max_Vertex_Num 1003
#define inp(i,x,y) for(i=x;i<=y;i++)

int AM[Max_Vertex_Num][Max_Vertex_Num];
bool Visit[Max_Vertex_Num];
void DFSTranvers(int p, int num);
int main()
{
    int vexnum = 0, edgenum = 0, i=0;
    scanf("%d%d",&vexnum,&edgenum);
    inp(i,0,edgenum-1){
        int p,q;
        scanf("%d%d",&p,&q);
        AM[p][q] = AM[q][p] = 1;
    }
    int cnt = 0;
    inp(i,1,vexnum){
        if(Visit[i]) continue;
        Visit[i] = true;
        DFSTranvers(i, vexnum);
        cnt++;
    }
    printf("%d\n",cnt-1);
    return 0;
}
void DFSTranvers(int p, int num)
{
    int i=0;
    inp(i,1,num){
        if(!Visit[i]&&AM[p][i]){
            Visit[i]=true;
            DFSTranvers(i, num);
        }
    }
    return ;
}