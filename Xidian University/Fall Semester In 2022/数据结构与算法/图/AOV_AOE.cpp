#include<iostream>
#include<cstring>
#include"ADL.h"
#define inp(i,x,y) for(i=x;i<=y;i++) 
#define Max_Vertex_Num 20
//-------------------AOV-------------------//
Status FindInDegree(ALGraph G, int *indegree);
Status TopologicalSort(ALGraph G, int *T, int &Ttop);
Status CriticalPath(ALGraph G);
int ve[Max_Vertex_Num];    // 顶点事件最早发生时间
int vl[Max_Vertex_Num];    // 顶点事件最迟发生时间
int main()
{
    ALGraph G, GR;
    CreateGraph(G, GR);
    GraphPrint(G, GR);
    CriticalPath(G);
    return 0;
}
Status TopologicalSort(ALGraph G, int *T, int &Ttop)
{      
    // 有向无环图的拓扑排序
    //求各顶点时间的最早发生时间ve(全局变量)
    //若G无回路，则用T返回G的一个拓扑序列，且函数返回OK，否则返回ERROR
    int S[Max_Vertex_Num], Stop = -1, i = 0;  /*栈St的指针为top*/
    int *indegree = new int[G.vexnum];
    if(!FindInDegree(G, indegree)) return false;    //indegree顶点入度
    inp(i,0,G.vexnum-1)
        if(!indegree[i]) S[++Stop] = i; 
    
    int count = 0;
    cout << "Directed acycline graph topologicalsort:\n";
    while(Stop > -1) { /*栈不为空时循环*/
        i = S[Stop--]; T[++Ttop] = i;   // i号顶点入T栈
        count++;
        cout << G.Vextices[i].data << " ";  // 输出拓扑排序
        for(ArcNode* p=G.Vextices[i].firstarc; p; p=p->nextarc){
            int k = p->adjvex;      // 邻接弧头节点位置
            if(--indegree[k]==0) S[++Stop] = k;   // 零入度进栈
            if(ve[i]+p->weight > ve[k]) ve[k] = ve[i] + p->weight;  
        }
    }
    cout << endl;
    delete[] indegree;
    if(count < G.vexnum)  return false;   // 有回路  
    else return true;
}// TopologicalOrder

Status FindInDegree(ALGraph G, int *indegree) 
{   
    int i;
    //inp(i,0,G.vexnum-1) indegree[i] = 0;
    memset(indegree, 0, G.vexnum*sizeof(int));  
    inp(i,0,G.vexnum-1){  //扫描邻接表，计算各顶点的入度
        for(ArcNode *p=G.Vextices[i].firstarc;  p;  p=p->nextarc)
            indegree[p->adjvex]++; 
    }
    return true;
}
Status CriticalPath(ALGraph G)
{ 
    // G为有向网，输出G的各项关键活动
    int T[Max_Vertex_Num], Ttop = -1, j = 0;    // 存储拓扑排序序列，模拟栈                                                 //建立用于产生拓扑逆序的栈T
    if(!TopologicalSort(G, T, Ttop)){
        cout << "This graph has a cicle.\n";
        return false;  //该有向网有回路返回false
    }else cout << "--------------Critical Path Table-----------------\n";
    inp(j,0,G.vexnum-1) vl[j] = ve[G.vexnum-1]; //初始化顶点事件的最迟发生时间
    while (Ttop > -1){        //按拓扑逆序求各顶点的vl值
        j = T[Ttop--]; 
        for(ArcNode *p=G.Vextices[j].firstarc; p; p=p->nextarc){
            int k = p->adjvex, dut = p->weight;     // dut<j,k>
            // vl[k]已经求得，与j各邻接弧k的所有vl[k]-dut要最小，保证耗时最长的相对于vl[k]能准时  
            if(vl[k] - dut < vl[j])  vl[j] = vl[k] - dut;   // min(vl(k)-dut<j,k>)   
        }// for
    } //while

    // 求e、l和关键活动
    cout << "Activities on edge:\n";
    cout << "---------------------------------------------\n";
    cout << "|  Edge  | duration | e | l | l-e | CriActi |\n";   // title
    inp(j,0,G.vexnum-1)                    
        for (ArcNode *p = G.Vextices[j].firstarc; p; p = p->nextarc) {
            int k = p->adjvex, dut= p->weight;
            int ee = ve[j], el = vl[k]-dut;
            string tag = (ve[j]==(vl[k]-dut))? "Yes":"No ";
            cout << "|<" << G.Vextices[j].data << ", " << G.Vextices[k].data << ">|    ";
            cout << dut << "     | " << ee << " | " << el << " |  " << el-ee << "  |   " << tag << "   |\n"; //输出关键活动
    }
    cout << "---------------------------------------------\n";
    cout << "Events on vertex:\n";
    cout << "--------------------\n";
    cout << "| Vertex | ve | vl |\n";   //title
    inp(j,0,G.vexnum-1)
        cout << "|   " << G.Vextices[j].data << "   | " << ve[j] << "  | " << vl[j] << "  |" << endl;
    cout << "--------------------\n";
    return true;
}//CriticalPath

