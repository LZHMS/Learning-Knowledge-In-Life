#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;
//----------------有向图的十字链表存储表示------------------//
#define Max_Vertex_Num 20
#define MAX_Length_Info 10
#define inp(i,x,y) for(i=x;i<=y;i++)
#define dep(i,x,y) for(i=x;i>=y;i--)
#define InfoType char*
#define VertexType string
#define Status bool
typedef enum { DG, DN, UDG, UDN }GraphKind;    //{有向图，有向网，无向图，无向网}

//---------------图的弧结构表示------------------//
typedef struct ArcBox {
    int tailvex, headvex, weight;  // 该弧的尾和头顶点的位置==>指向顺序存储结构中的编号
    struct ArcBox* hlink, * tlink; // 分别为弧头相同和弧尾相同的弧的链域
    // 对每一个节点而言，弧头相同的节点和弧尾相同的节点指向两个链表构成十字链表分别表示入度和出度
    InfoType info;        // 弧信息
}ArcBox;
//---------------图的顶点结构表示-----------------//
typedef struct VexNode {
    VertexType data;
    ArcBox* firstin, * firstout;  // 分别指向该顶点第一条入弧和出弧
    VexNode()
    {
        data = "";
        firstin = firstout = NULL;
    }
}VexNode, Xlist[Max_Vertex_Num];
typedef struct {
    Xlist Vextices;    // 表头向量
    int kind, vexnum, arcnum, IncInfo;          //图种类表识，节点数和弧数，弧有无信息
}OLGraph;

int LocateVex(OLGraph G, VertexType v);
Status GraphAddNode(OLGraph& G, int p1, int p2, int w);
Status CreateDG(OLGraph& G);
Status CreateDN(OLGraph& G);
Status CreateUDG(OLGraph& G);
Status CreateUDN(OLGraph& G);
Status CreateGraph(OLGraph& G);
Status GraphPrint(OLGraph G);

int main()
{
    OLGraph G;
    CreateGraph(G);
    GraphPrint(G);
    return 0;
}
Status CreateGraph(OLGraph& G)
{
    cout << "Input the type of graph(0:DG,1:DN,2:UDG,3:UDN):\n";
    cin >> G.kind;      // 种类标识
    switch (G.kind) {
    case DG:return CreateDG(G);
    case DN:return CreateDN(G);
    case UDG:return CreateUDG(G);
    case UDN:return CreateUDN(G);
    default:return false;
    }
}
Status CreateDG(OLGraph& G)
{
    // 采用十字链表存储表示，构造有向图G(G.kind=DG)
    cout << "Input Vextices number, Arcs number and Incinformation(Yes:1,NO:0):\n";
    cin >> G.vexnum >> G.arcnum >> G.IncInfo;
    int i = 0;
    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) cin >> G.Vextices[i].data;      // 节点顶点值 
    cout << "Input two vertices of the edges:\n";
    inp(i, 0, G.arcnum - 1) {    // 输入各弧并构造十字链表
        VertexType v1, v2;
        cin >> v1 >> v2;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;

        GraphAddNode(G, p1, p2, 1);   // p1->p2
    }
    return true;
}
Status CreateDN(OLGraph& G)
{
    // 采用十字链表存储表示，构造有向网G(G.kind=DN)
    cout << "Input Vextices number, Arcs number and Incinformation(Yes:1,NO:0):\n";
    cin >> G.vexnum >> G.arcnum >> G.IncInfo;
    int i = 0;
    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) cin >> G.Vextices[i].data;      // 节点顶点值 
    cout << "Input two vertices and weight of the edges:\n";
    inp(i, 0, G.arcnum - 1) {    // 输入各弧并构造十字链表
        VertexType v1, v2;
        int w = 0;
        cin >> v1 >> v2 >> w;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;

        GraphAddNode(G, p1, p2, w);   // p1->p2
    }
    return true;
}
Status CreateUDG(OLGraph& G)
{
    // 采用十字链表存储表示，构造无向图G(G.kind=UDG)
    cout << "Input Vextices number, Arcs number and Incinformation(Yes:1,NO:0):\n";
    cin >> G.vexnum >> G.arcnum >> G.IncInfo;
    int i = 0;
    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) cin >> G.Vextices[i].data;      // 节点顶点值 
    cout << "Input two vertices of the edges:\n";
    inp(i, 0, G.arcnum - 1) {    // 输入各弧并构造十字链表
        VertexType v1, v2;
        cin >> v1 >> v2;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;
        GraphAddNode(G, p1, p2, 1);   // p1->p2
        GraphAddNode(G, p2, p1, 1);   // p2->p1
    }
    return true;
}
Status CreateUDN(OLGraph& G)
{
    // 采用十字链表存储表示，构造无向网G(G.kind=UDN)
    cout << "Input Vextices number, Arcs number and Incinformation(Yes:1,No:0):\n";
    cin >> G.vexnum >> G.arcnum >> G.IncInfo;
    int i = 0;
    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) cin >> G.Vextices[i].data;      // 节点顶点值 
    cout << "Input two vertices and weight of the edges:\n";
    inp(i, 0, G.arcnum - 1) {    // 输入各弧并构造十字链表
        VertexType v1, v2;
        int w = 0;
        cin >> v1 >> v2 >> w;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;
        GraphAddNode(G, p1, p2, w);   // p1->p2
        GraphAddNode(G, p2, p1, w);   // p2->p1
    }
    return true;
}
Status GraphAddNode(OLGraph& G, int p1, int p2, int w)
{
    ArcBox* p = (ArcBox*)malloc(sizeof(ArcBox));  // 创建弧单元
    if (!p) return false;

    //十字链表——涉及两个链表的交接==>最终first指针会指向最后输入的一组数据
    *p = { p1, p2, w, G.Vextices[p2].firstin, G.Vextices[p1].firstout, NULL };  // 对弧节点赋值
    G.Vextices[p2].firstin = G.Vextices[p1].firstout = p;  // 完成在入弧和出弧链头的插入
    if (G.IncInfo) {
        p->info = (char*)malloc(MAX_Length_Info*sizeof(char));
        cout << "Input the arc information: ";
        cin >> p->info;
    }
    return true;
}
int LocateVex(OLGraph G, VertexType v)
{
    int i = 0;
    inp(i, 0, G.vexnum - 1) {
        if (G.Vextices[i].data == v)
            return i;
    }
    return -1;
}
Status GraphPrint(OLGraph G)
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
    cout << "The Nodes Path:\n";
    inp(i, 0, G.vexnum - 1) {
        ArcBox* p = G.Vextices[i].firstout;
        ArcBox* q = G.Vextices[i].firstin;
        int Outdegree = 0, Indegree = 0;
        cout << "Out path: ";
        while (p) {
            cout << G.Vextices[p->tailvex].data << "-[" << p->weight << "]->" << G.Vextices[p->headvex].data << "  ";
            p = p->tlink;
            Outdegree++;
        }
        cout << endl << "In path: ";
        while (q) {
            cout << G.Vextices[q->tailvex].data << "-[" << q->weight << "]->" << G.Vextices[q->headvex].data << "  ";
            q = q->hlink;
            Indegree++;
        }

        cout << endl << G.Vextices[i].data;
        cout << "  Vextice Degree: " << Outdegree + Indegree << "  Outdegree: " << Outdegree
            << "  Indegree: " << Indegree << endl;
        cout << endl;
    }
    return true;
}