#include<iostream>
#define inp(i,x,y) for(i=x;i<=y;i++)
#define dep(i,x,y) for(i=x;i>=y;i--)
#define Max_Vertex_Num 102

// 邻接表数据结构
int head[Max_Vertex_Num],edge[Max_Vertex_Num],ver[Max_Vertex_Num],next[Max_Vertex_Num];

int ve[Max_Vertex_Num];    // 事件或活动最早发生时间
int vl[Max_Vertex_Num];    // 事件最迟发生时间
int indegree[Max_Vertex_Num];   // 顶点入度

bool TopologicalSort(int num, int *T, int &Ttop);
bool CriticalPath(int num);
int main()
{
    int i = 0, j = 0, num = 0, temp = 0, cnt = 0;
    scanf("%d",&num);
    inp(i,0,num-1)   // 创建邻接表
        inp(j,0,num-1){
            scanf("%d",&temp);
            if(temp){
                // 第cnt条边
                ver[++cnt] = j;     // 存储边终点
                edge[cnt] = temp;   //边权
                next[cnt] = head[i];  // 邻接表边衔接
                head[i] = cnt;   // 头节点记录边编号
                indegree[j]++;
            }
        }
    
    if(!CriticalPath(num))
        printf("NO\n");
    return 0;
}

bool TopologicalSort(int num, int *T, int &Ttop)
{      
    // 根据拓扑排序判断有向无环图是否存在回路
    int S[Max_Vertex_Num], Stop = -1,i = 0, j = 0;  /*栈St的指针为top*/
    inp(i,0,num-1)
        if(!indegree[i]) S[++Stop] = i; 
    
    int count = 0;
    while(Stop > -1) {   /*栈不为空时循环*/
        i = S[Stop--]; T[++Ttop] = i;
        count++;
        for(j=head[i]; j; j=next[j]){
            if(--indegree[ver[j]]==0) S[++Stop] = ver[j];   // 零入度进栈
            if(ve[i]+edge[j] > ve[ver[j]])
                ve[ver[j]] = ve[i]+edge[j];  
        }
    }
    if(count < num) return false;   // 有回路  
    else return true;
}

bool CriticalPath(int num)
{ 
    int T[Max_Vertex_Num], Ttop = -1, i = 0, j = 0;    // 存储拓扑逆序序列
    if(!TopologicalSort(num, T, Ttop)){
        return false;  //该有向网有回路返回false
    }

    inp(j,0,num-1) vl[j] = ve[num-1];  //初始化顶点事件的最迟发生时间
    while (Ttop > -1){
        i = T[Ttop--]; 
        for(j=head[i]; j; j=next[j])
            if(vl[ver[j]] - edge[j] < vl[i]) 
                vl[i] = vl[ver[j]] - edge[j];   // 最迟发生时间
    }

    int clength = 0;  // 关键路径长度
    while(i != num-1){
        for (j = head[i]; j; j = next[j])
            if(ve[i]==vl[ver[j]]-edge[j]){
                clength += edge[j];
                break;
            }
        i = ver[j];
    }
    printf("%d\n",clength);
    return true;
}

