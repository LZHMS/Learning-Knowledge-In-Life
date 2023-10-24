#include<cstdlib>
#include<iostream>
#include<string>
#include<limits.h>
using namespace std;
//----------------自定义邻接矩阵模板类-----------------//

//-------------图的数组（邻接矩阵存储）表示-----------//
#define Max_Vertex_Num 20 
#define inp(i,x,y) for(i=x;i<=y;i++)
#define dep(i,x,y) for(i=x;i>=y;i--)
#define INFINITY INT_MAX
#define VRType int 
#define InfoType string
#define VertexType string
#define Status bool

typedef enum { DG, DN, UDG, UDN }GraphKind;    //{有向图，有向网，无向图，无向网}
typedef struct ArcCell {
    VRType adj;   // 顶点关系类型，无权图，用1或0表相邻否；有权图为权值
    InfoType info;   //弧相关信息指针
}ArcCell, AdjMatrix[Max_Vertex_Num][Max_Vertex_Num];

typedef struct {
    VertexType vexs[Max_Vertex_Num];  // 顶点向量
    AdjMatrix arcs;   // 邻接矩阵
    int vexnum, arcnum;  // 图的当前顶点数和弧数
    GraphKind kind;     // 图种类标志 
}MGraph;

int LocateVex(MGraph G, VertexType v);
Status CreateDG(MGraph& G);
Status CreateDN(MGraph& G);
Status CreateUDG(MGraph& G);
Status CreateUDN(MGraph& G);
Status CreateGraph(MGraph& G);
Status GraphPrint(MGraph G);
/*int main()
{
    MGraph G;
    CreateGraph(G);
    GraphPrint(G);
    return 0;
}*/
Status CreateGraph(MGraph& G)
{
    // 采用邻接矩阵表示法，构造图G
    int sign = 0;
    cout << "Input the type of graph(0:DG,1:DN,2:UDG,3:UDN):\n";
    cin >> sign;
    switch (sign) {
    case DG:
        G.kind = DG;
        return CreateDG(G);  // diagraph
    case DN:
        G.kind = DN;
        return CreateDN(G);  // dianetwork
    case UDG:
        G.kind = UDG;
        return CreateUDG(G);  //undiagraph
    case UDN:
        G.kind = UDN;
        return CreateUDN(G);  //undianetwork
    default:return false;
    }
}

Status CreateUDN(MGraph& G)
{
    // 采用数组（邻接矩阵）表示法构造无向网G
    int IncInfo = 0, i = 0, j = 0;
    cout << "Input Vextices number, Arcs number and Incinformation(1:Yes,0:NO):\n";
    cin >> G.vexnum >> G.arcnum >> IncInfo;   // IncInfo为0则各弧不含其他信息

    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) cin >> G.vexs[i];   // 节点数据
    inp(i, 0, G.vexnum - 1)  // 初始化邻接矩阵
        inp(j, 0, G.vexnum - 1) G.arcs[i][j] = { INFINITY, "" }; //{adj,info}

    cout << "Input two vertices and weight of the edges:\n";
    inp(i, 0, G.arcnum - 1) {
        VertexType v1, v2;
        int w = 0;
        cin >> v1 >> v2 >> w;     // 输入一条边的顶点和权值
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;

        G.arcs[p1][p2].adj = w;    // 弧<v1,v2>的权值w
        if (IncInfo) cin >> G.arcs[p1][p2].info;     // 如果弧有信息则输入
        G.arcs[p2][p1] = G.arcs[p1][p2];     // 无向图
    }
    return true;
}
Status CreateUDG(MGraph& G)
{
    // 采用数组（邻接矩阵）表示法构造无向图G
    int IncInfo = 0, i = 0, j = 0;
    cout << "Input Vextices number, Arcs number and Incinformation(1:Yes,0:NO):\n";
    cin >> G.vexnum >> G.arcnum >> IncInfo;   // IncInfo为0则各弧不含其他信息

    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) cin >> G.vexs[i];   // 节点数据
    inp(i, 0, G.vexnum - 1)  // 初始化邻接矩阵
        inp(j, 0, G.vexnum - 1) G.arcs[i][j] = { 0, "" }; //{adj,info}

    cout << "Input two vertices of the edges:\n";
    inp(i, 0, G.arcnum - 1) {
        VertexType v1, v2;
        cin >> v1 >> v2;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;

        G.arcs[p1][p2].adj = 1;    // 弧<v1,v2>的权值w
        if (IncInfo) cin >> G.arcs[p1][p2].info;     // 如果弧有信息则输入
        G.arcs[p2][p1] = G.arcs[p1][p2];     // 无向图
    }
    return true;
}
Status CreateDG(MGraph& G)
{
    // 采用数组（邻接矩阵）表示法构造无向图G
    int IncInfo = 0, i = 0, j = 0;
    cout << "Input Vextices number, Arcs number and Incinformation(1:Yes,0:NO):\n";
    cin >> G.vexnum >> G.arcnum >> IncInfo;   // IncInfo为0则各弧不含其他信息

    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) cin >> G.vexs[i];   // 节点数据
    inp(i, 0, G.vexnum - 1)  // 初始化邻接矩阵
        inp(j, 0, G.vexnum - 1) G.arcs[i][j] = { 0, "" }; //{adj,info}

    cout << "Input two vertices of the edges:\n";
    inp(i, 0, G.arcnum - 1) {
        VertexType v1, v2;
        cin >> v1 >> v2;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;

        G.arcs[p1][p2].adj = 1;    // 弧<v1,v2>的权值w
        if (IncInfo) cin >> G.arcs[p1][p2].info;     // 如果弧有信息则输入
    }
    return true;
}
Status CreateDN(MGraph& G)
{
    // 采用数组（邻接矩阵）表示法构造无向图G
    int IncInfo = 0, i = 0, j = 0;
    cout << "Input Vextices number, Arcs number and Incinformation(1:Yes,0:NO):\n";
    cin >> G.vexnum >> G.arcnum >> IncInfo;   // IncInfo为0则各弧不含其他信息

    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) cin >> G.vexs[i];   // 节点数据
    inp(i, 0, G.vexnum - 1)  // 初始化邻接矩阵
        inp(j, 0, G.vexnum - 1){
            if(i==j) G.arcs[i][j] = {0, "" }; //{adj,info}
            else G.arcs[i][j] = {INFINITY, "" }; //{adj,info}
        }

    cout << "Input two vertices and weight of the edges:\n";
    inp(i, 0, G.arcnum - 1) {
        VertexType v1, v2;
        int w = 0;
        cin >> v1 >> v2 >> w;     // 输入一条边的顶点和权值
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;

        G.arcs[p1][p2].adj = w;    // 弧<v1,v2>的权值w
        if (IncInfo) cin >> G.arcs[p1][p2].info;     // 如果弧有信息则输入
    }
    return true;
}
int LocateVex(MGraph G, VertexType v)
{
    int i = 0;
    inp(i, 0, G.vexnum - 1) {
        if (G.vexs[i] == v)
            return i;
    }
    return -1;
}
Status GraphPrint(MGraph G)
{
    cout << "Output Graph Information:\n";
    cout << "Graph Kind: ";
    switch (G.kind) {
    case DG:cout << "directed graph\n";  // diagraph
        break;
    case DN:cout << "directed nets\n";  // dianetwork
        break;
    case UDG:cout << "undirected graph\n";  //undiagraph
        break;
    case UDN:cout << "undirected nets\n";  //undianetwork
        break;
    default:return false;
    }
    cout << "Vextices number: " << G.vexnum << "   " << "Arcs number: " << G.arcnum << endl;
    int i = 0, j = 0;
    cout << "Vextices Vector Information:\n";
    int sign = (G.kind == DG || G.kind == UDG) ? 1 : 0;   // 图标记
    inp(i, 0, G.vexnum - 1) {
        int Outdegree = 0, Indegree = 0;
        inp(j, 0, G.vexnum - 1) {
            if (G.arcs[i][j].adj != INFINITY && (!sign || (sign && G.arcs[i][j].adj != 0))) {
                Outdegree++;
                cout << G.vexs[i] << "-<" << G.arcs[i][j].adj << ">-" << G.vexs[j] << " ";
            }
            if (G.arcs[j][i].adj != INFINITY && (!sign || (sign && G.arcs[j][i].adj != 0))) Indegree++;
        }
        cout << endl << G.vexs[i];
        if (G.kind == DG || G.kind == DN)
            cout << "  Vextice Degree: " << Outdegree + Indegree << "  Outdegree: " << Outdegree
            << "  Indegree: " << Indegree << endl;
        else cout << "  Vextice Degree: " << Outdegree << endl;
    }
    return true;
}