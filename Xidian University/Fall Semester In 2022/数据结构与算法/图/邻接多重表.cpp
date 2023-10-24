#include<iostream>
#include<string>
using namespace std;
//--------------------无向图的邻接多重表存储表示-----------------//
#define Max_Vertex_Num 20
#define MAX_Length_Info 10
#define InfoType char
#define VertexType string
#define inp(i,x,y) for(i=x;i<=y;i++)
#define Status bool

typedef enum{unvisited, visited}VisitIf;
typedef enum {UDG, UDN }GraphKind;    //{无向图，无向网}
//------------------边结构定义--------------//
typedef struct EBox{
    VisitIf mark;     // 访问标记
    int ivex, jvex, weight;     // 该边依附的两个顶点位置
    struct EBox *ilink, *jlink;   // 分别指向依附这两个顶点的下一条边
    InfoType *info;    // 该边信息指针  
}EBox;
//------------------顶点结构定义--------------//
typedef struct VexBox{
    VertexType data;     // 节点数据域
    EBox *firstedge;  //指向第一条依附该顶点的边
    VexBox()
    {
        data = "";
        firstedge = NULL;
    }
}VexBox, AMList[Max_Vertex_Num];
//-------------------图结构定义---------------//
typedef struct{
    AMList adjmulist;
    int vexnum, arcnum, kind, IncInfo;     // 无向图的顶点数和边数
}AMLGraph;

int LocateVex(AMLGraph G, VertexType v);
Status GraphAddNode(AMLGraph& G, int p1, int p2, int w);
Status CreateGraph(AMLGraph &G);
Status CreateUDG(AMLGraph &G);
Status CreateUDN(AMLGraph &G);
Status GraphPrint(AMLGraph G);
int main()
{
    AMLGraph G;
    CreateGraph(G);
    GraphPrint(G);
    return 0;
}
Status CreateGraph(AMLGraph &G)
{
    cout << "Input the type of graph(0:UDG,1:UDN):\n";
    cin >> G.kind;      // 种类标识
    switch(G.kind){
        case UDG:return CreateUDG(G);
        case UDN:return CreateUDN(G);
        default:return false;
    }
}
Status CreateUDG(AMLGraph &G)
{
    // 采用邻接多重表存储表示，构造无向图G(G.kind=UDG)
    cout << "Input Vextices number, Arcs number and Incinformation(Yes:1,NO:0):\n";
    cin >> G.vexnum >> G.arcnum >> G.IncInfo;
    int i = 0;
    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) cin >> G.adjmulist[i].data;      // 节点顶点值 
    cout << "Input two vertices of the edges:\n";
    inp(i, 0, G.arcnum - 1) {    // 输入各弧并构造十字链表
        VertexType v1, v2;
        cin >> v1 >> v2;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;
        
        // 由于以边为单元，对两个节点的firstedge都做修改因此只需一次添加即可
        GraphAddNode(G, p1, p2, 1);   // p1<->p2
    }
    return true;
}
Status CreateUDN(AMLGraph &G)
{
    // 采用邻接多重表存储表示，构造无向网G(G.kind=UDN)
    cout << "Input Vextices number, Arcs number and Incinformation(Yes:1,NO:0):\n";
    cin >> G.vexnum >> G.arcnum >> G.IncInfo;
    int i = 0;
    cout << "Input Graph Node Sign:\n";
    inp(i, 0, G.vexnum - 1) cin >> G.adjmulist[i].data;      // 节点顶点值 
    cout << "Input two vertices and weight of the edges:\n";
    inp(i, 0, G.arcnum - 1) {    // 输入各弧并构造十字链表
        VertexType v1, v2;
        int w = 0;
        cin >> v1 >> v2 >> w;     // 输入一条边的顶点
        int p1 = LocateVex(G, v1), p2 = LocateVex(G, v2);
        if (p1 == -1 || p2 == -1) return false;
        
        // 由于以边为单元，对两个节点的firstedge都做修改因此只需一次添加即可
        GraphAddNode(G, p1, p2, w);   // p1<->p2
    }
    return true;
}
int LocateVex(AMLGraph G, VertexType v)
{
    int i = 0;
    inp(i, 0, G.vexnum - 1) {
        if (G.adjmulist[i].data == v)
            return i;
    }
    return -1;
}
Status GraphAddNode(AMLGraph& G, int p1, int p2, int w)
{
    EBox* p = (EBox*)malloc(sizeof(EBox));  // 创建边单元
    if (!p) return false;

    //邻接多重表——涉及两个链表的交接==>最终firstedge指针会指向最后输入的一组数据
    *p = {unvisited, p1, p2, w, G.adjmulist[p1].firstedge, G.adjmulist[p2].firstedge, NULL };  // 对弧节点赋值
         //{mark, ivex, jvex, weight, *ilink, *jlink, *info}
    G.adjmulist[p1].firstedge = G.adjmulist[p2].firstedge = p; // 完成在入弧和出弧链头的插入
    if (G.IncInfo) {
        p->info = (char*)malloc(MAX_Length_Info*sizeof(char));
        cout << "Input the arc information: ";
        cin >> p->info;
    }
    return true;
}
Status GraphPrint(AMLGraph G)
{
    cout << "----------------Output Graph Information-----------------\n";
    cout << "Graph Kind: ";
    switch (G.kind) {
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
        EBox* p = G.adjmulist[i].firstedge;
        int Degree = 0, pos = 0;
        cout << "Paths: ";
        while (p) {
            pos = (p->ivex == i)?p->jvex:p->ivex;
            if(G.IncInfo)
                cout << G.adjmulist[i].data << p->info << "-<" << p->weight << ">-" << G.adjmulist[pos].data << "  ";
            else
                cout << G.adjmulist[i].data << "-<" << p->weight << ">-" << G.adjmulist[pos].data << "  ";
            p = (p->ivex == i)?p->ilink:p->jlink;
            Degree++;
        }
        cout << endl << G.adjmulist[i].data;
        cout << "  Vextice Degree: " << Degree << "  Outdegree: " << Degree<< "  Indegree: " << Degree << "\n\n";
    }
    return true;
}