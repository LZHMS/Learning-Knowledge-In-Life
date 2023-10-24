#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;
//---------------------图的邻接表存储表示-----------------//
#define inp(i,x,y) for(i=x;i<=y;i++)
#define dep(i,x,y) for(i=x;i>=y;i--)
#define Max_Vertex_Num 20
#define InfoType string
#define VertexType string
#define Status bool

typedef enum { DG, DN, UDG, UDN }GraphKind;    //{有向图，有向网，无向图，无向网}

//----------弧节点结构-------------//
typedef struct ArcNode {
    int adjvex;   // 该弧所指向的顶点位置
    int weight;   // 弧的权值
    struct ArcNode* nextarc;    // 指向下一条弧指针
    InfoType info;       // 该弧相关信息
    ArcNode()
    {
        adjvex = weight = 0;
        nextarc = NULL;
        info = "";
    }
}ArcNode;
//----------头节点结构---------------//
typedef struct VNode {
    VertexType data;   // 顶点信息
    int Outdegree;     // 节点对应的出度
    ArcNode* firstarc;   // 指向第一条依附该顶点的弧的指针
    VNode()
    {
        data = "";
        Outdegree = 0;
        firstarc = NULL;
    }
}VNode, AdjList[Max_Vertex_Num];
//----------图结构定义---------------//
typedef struct {
    AdjList Vextices;
    int vexnum, arcnum;    // 图的顶点数和弧数
    int kind;       // 图的种类标志
}ALGraph;

//--------------头节点定位函数---------------------//
int LocateVex(ALGraph G, VertexType v);
//-------------------构建节点函数------------------//
Status GraphAddNode(ALGraph& G, int p1, int p2, int w, int IncInfo);
//-------------------图创建函数--------------------//
Status CreateDG(ALGraph& G, ALGraph& GR);
Status CreateDN(ALGraph& G, ALGraph& GR);
Status CreateUDG(ALGraph& G, ALGraph& GR);
Status CreateUDN(ALGraph& G, ALGraph& GR);
Status CreateGraph(ALGraph& G, ALGraph& GR);

//------------------图输出函数---------------------//
Status GraphPrint(ALGraph G, ALGraph GR);
/*
int main()
{
    ALGraph G, GR;   // G:邻接表，GR:逆邻接表
    CreateGraph(G, GR);
    GraphPrint(G, GR);
    return 0;
}
*/
Status CreateGraph(ALGraph& G, ALGraph& GR)
{
    cout << "Input the type of graph(0:DG,1:DN,2:UDG,3:UDN):\n";
    cin >> G.kind;      // 种类标识
    GR.kind = G.kind;
    switch (G.kind) {
    case 0:return CreateDG(G, GR);
    case 1:return CreateDN(G, GR);
    case 2:return CreateUDG(G, GR);
    case 3:return CreateUDN(G, GR);
    default:return false;
    }
}

Status CreateDG(ALGraph& G, ALGraph& GR)
{
    // 采用邻接表表示法构造有向图G
    int IncInfo = 0, i = 0, j = 0;
    cout << "Input Vextices number, Arcs number and Incinformation(1:Yes,0:NO):\n";
    cin >> G.vexnum >> G.arcnum >> IncInfo;   // IncInfo为0则各弧不含其他信息
    GR.vexnum = G.vexnum; GR.arcnum = G.arcnum;

    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) {
        cin >> G.Vextices[i].data;   // 节点数据
        GR.Vextices[i].data = G.Vextices[i].data;
    }

    cout << "Input two vertices of the edges:\n";
    inp(i, 0, G.arcnum - 1) {
        VertexType v1, v2;
        cin >> v1 >> v2;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;

        GraphAddNode(G, p1, p2, 1, IncInfo);   // 邻接表中p1->p2 ==> p1的出度
        GraphAddNode(GR, p2, p1, 1, IncInfo);   // 逆邻接表中p1->p2 ==> p2的入度
    }
    return true;
}

Status CreateDN(ALGraph& G, ALGraph& GR)
{
    // 采用邻接表表示法构造有向网G
    int IncInfo = 0, i = 0, j = 0;
    cout << "Input Vextices number, Arcs number and Incinformation(1:Yes,0:NO):\n";
    cin >> G.vexnum >> G.arcnum >> IncInfo;   // IncInfo为0则各弧不含其他信息
    GR.vexnum = G.vexnum; GR.arcnum = G.arcnum;

    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) {
        cin >> G.Vextices[i].data;   // 节点数据
        GR.Vextices[i].data = G.Vextices[i].data;
    }

    cout << "Input two vertices and weight of the edges:\n";
    inp(i, 0, G.arcnum - 1) {
        VertexType v1, v2;
        int w = 0;
        cin >> v1 >> v2 >> w;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;

        GraphAddNode(G, p1, p2, w, IncInfo);   // 邻接表中p1->p2 ==> p1的出度
        GraphAddNode(GR, p2, p1, w, IncInfo);  // 逆邻接表中p1->p2 ==> p2的入度
    }
    return true;
}

Status CreateUDG(ALGraph& G, ALGraph& GR)
{
    // 采用邻接表表示法构造无向图G
    int IncInfo = 0, i = 0, j = 0;
    cout << "Input Vextices number, Arcs number and Incinformation(1:Yes,0:NO):\n";
    cin >> G.vexnum >> G.arcnum >> IncInfo;   // IncInfo为0则各弧不含其他信息
    GR.vexnum = G.vexnum; GR.arcnum = G.arcnum;

    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) {
        cin >> G.Vextices[i].data;   // 节点数据
        GR.Vextices[i].data = G.Vextices[i].data;
    }

    cout << "Input two vertices of the edges:\n";
    inp(i, 0, G.arcnum - 1) {
        VertexType v1, v2;
        cin >> v1 >> v2;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;

        // 对无向图而言，逆邻接表作用不是很显著，实际使用中可删除
        GraphAddNode(G, p1, p2, 1, IncInfo);   // p2挂在p1链表上
        GraphAddNode(G, p2, p1, 1, IncInfo);   // p1挂在p2链表上
        GraphAddNode(GR, p1, p2, 1, IncInfo);
        GraphAddNode(GR, p2, p1, 1, IncInfo);
    }
    return true;
}

Status CreateUDN(ALGraph& G, ALGraph& GR)
{
    // 采用邻接表表示法构造无向网G
    int IncInfo = 0, i = 0, j = 0;
    cout << "Input Vextices number, Arcs number and Incinformation(1:Yes,0:NO):\n";
    cin >> G.vexnum >> G.arcnum >> IncInfo;   // IncInfo为0则各弧不含其他信息
    GR.vexnum = G.vexnum; GR.arcnum = G.arcnum;

    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) {
        cin >> G.Vextices[i].data;   // 节点数据
        GR.Vextices[i].data = G.Vextices[i].data;
    }

    cout << "Input two vertices and weight of the edges:\n";
    inp(i, 0, G.arcnum - 1) {
        VertexType v1, v2;
        int w = 0;
        cin >> v1 >> v2 >> w;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;

        GraphAddNode(G, p1, p2, w, IncInfo);    // 附权值w
        GraphAddNode(G, p2, p1, w, IncInfo);
        GraphAddNode(GR, p1, p2, w, IncInfo);
        GraphAddNode(GR, p2, p1, w, IncInfo);
    }
    return true;
}

Status GraphAddNode(ALGraph& G, int p1, int p2, int w, int IncInfo)
{
    // 将弧的头节点p2挂在尾节点p1的链表上
    ArcNode* p = G.Vextices[p1].firstarc;
    int sign = 0;
    while (p) { 
        if (p->adjvex == p2) {     //如果已经存在
            sign = 1;
            if (IncInfo) cin >> p->info;     // 如果弧有信息则输入
            break;
        }
        if (!p->nextarc) break;
        p = p->nextarc;
    }
    if (!sign) {
        if (!p) {
            p = (ArcNode*)malloc(sizeof(ArcNode));
            G.Vextices[p1].firstarc = p;
        }
        else {
            p->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
            p = p->nextarc;
        }

        p->adjvex = p2;
        p->weight = w;    // 弧<v1,v2>的权值w   
        p->nextarc = NULL;
        if (IncInfo) cin >> p->info;     // 如果弧有信息则输入
        G.Vextices[p1].Outdegree++;
    }
    return true;
}

int LocateVex(ALGraph G, VertexType v)
{
    int i = 0;
    inp(i, 0, G.vexnum - 1) {
        if (G.Vextices[i].data == v)
            return i;
    }
    return -1;
}

Status GraphPrint(ALGraph G, ALGraph GR)
{
    cout << "----------------Output Graph Information-----------------\n";
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
    cout << endl << "----------------Vextices Vector Information----------------\n";
    int sign = (G.kind == DG || G.kind == DN) ? 1 : 0;   // 图标记
    cout << "The Nodes Path:\n";
    inp(i, 0, G.vexnum - 1) {
        ArcNode* p = G.Vextices[i].firstarc;
        ArcNode* q = GR.Vextices[i].firstarc;
        if (sign) {
            cout << "Out path: ";
            while (p) {
                cout << G.Vextices[i].data << "-[" << p->weight << "]->" << G.Vextices[p->adjvex].data << "  ";
                p = p->nextarc;
            }
            cout << endl << "In path: ";
            while (q) {
                cout << GR.Vextices[q->adjvex].data << "-[" << q->weight << "]->-" << GR.Vextices[i].data << "  ";
                q = q->nextarc;
            }
            cout << endl << G.Vextices[i].data;
            cout << "  Vextice Degree: " << G.Vextices[i].Outdegree + GR.Vextices[i].Outdegree << "  Outdegree: " << G.Vextices[i].Outdegree
                << "  Indegree: " << GR.Vextices[i].Outdegree << endl;
        }
        else {
            cout << "Out path: ";
            while (p) {
                cout << G.Vextices[i].data << "-<-[" << p->weight << "]->-" << G.Vextices[p->adjvex].data << "  ";
                p = p->nextarc;
            }
            cout << endl << G.Vextices[i].data;
            cout << "  Vextice Degree: " << G.Vextices[i].Outdegree << endl;
        }
        cout << endl;
    }
    return true;
}