#include<iostream>
#include<queue>
#include"ADL.h"
using namespace std;
//-------------建立无向图的生成森林------------------//
// 以孩子兄弟链表作生成森林的存储结构
#define TElemType string
#define inp(i,x,y) for(i=x;i<=y;i++)
#define Max_Vertex_Num 20
typedef enum{unvisited, visited}VisitIf;

typedef struct CSNode {
       TElemType data;
       struct CSNode  *firstchild,  *nextsibling;  
}CSNode, *CSTree;
typedef struct QElem {        // 用于广度优先生成树中元素结构
       CSTree  node;
       int v;  
}QElem;

VisitIf visite[Max_Vertex_Num];

//-------------------------生成森林函数---------------------------//
Status CreateForest(ALGraph G,  CSTree &T, Status(*CreateTree)(ALGraph G,  int v,  CSTree &T));
Status DFSTree(ALGraph G,  int v,  CSTree &T);   // 深度优先
Status BFSTree(ALGraph G,  int v,  CSTree &T);   // 广度优先
//--------------------生成森林的遍历-------------------------//
Status CSFPreRootOrder(CSTree T, Status(*Visit)(TElemType e));     // 先根遍历
Status CSFPostRootOrder(CSTree T, Status(*Visit)(TElemType e));		// 后根遍历
Status LevelOrderTraverse(CSTree T, Status(*Visit)(TElemType e));     // 层序遍历
Status TreeTransOperator(TElemType e);    // 二叉树遍历算子
Status ForestPrint(CSTree T);       // 森林输出函数
int main()
{
    ALGraph G, GR;
    CreateGraph(G, GR);
    CSTree DFST, BFST;
    CreateForest(G, DFST, DFSTree);
    CreateForest(G, BFST, BFSTree);
    GraphPrint(G, GR);
    cout << "------------------------CS_Forest DFS Traverse-------------------------\n";
    ForestPrint(DFST);
    cout << endl << "------------------------CS_Forest BFS Traverse-------------------------\n";
    ForestPrint(BFST);
    return 0;
}

Status CreateForest(ALGraph G,  CSTree &T, Status(*CreateTree)(ALGraph G,  int v,  CSTree &T))
{   
    // 建立无向图G的生成森林
    CSTree  p,  q;   
    T = NULL; 
    int v = 0;     
    inp(v,0,G.vexnum-1)  visite[v] = unvisited;   // 节点初始化
    inp(v,0,G.vexnum-1)
        if(!visite[v]){
            p = (CSTree) malloc(sizeof(CSNode));
            *p = {G.Vextices[v].data, NULL, NULL};
            if(!T) T = p;
            else q->nextsibling = p;     // 是其他生成树的根
            q = p;                 // q指示当前生成树的根
            CreateTree(G, v, q);        // 建立以p为根的生成树
        }
    return true;
}
//-----------深度优先生成森林------------//
Status DFSTree(ALGraph G,  int v,  CSTree &T)
{   
    // 从第v个顶点出发深度优先遍历图G，建立以T为根的生成树
    CSTree p, q;    
    visite[v] = visited;    // 子树根节点已访问过
    bool first = true;
    for(ArcNode *a=G.Vextices[v].firstarc; a; a=a->nextarc){
        int w = a->adjvex;
        if(!visite[w]){    // 排除根节点的父代节点
            p = (CSTree)malloc(sizeof(CSNode));    // 为当前遍历的节点申请空间
            *p = {G.Vextices[w].data, NULL, NULL}; 
            if(first) {
                T->firstchild = p;     // 找到根节点的第一个孩子 
                first = false; 
            }
            else q->nextsibling = p;    // 其他孩子节点作为上一节点的右兄弟节点
            q = p;                      // 更新上一节点
            DFSTree(G, w, q);           // 递归生成以q为根节点的子树
        }
    }
    return true;
}

//-----------广度优先生成森林------------//
Status BFSTree(ALGraph G,  int v,  CSTree &T)
{
    bool first = true;
    // 处理根节点
    queue<QElem> Q; Q.push({T, v}); visite[v]=visited; 
    while (!Q.empty()) {
        QElem e = Q.front(); Q.pop();
        CSTree q = e.node;
        first = true;    // 标记q节点的第一个孩子
        // 在邻接表中搜寻当前节点未访问过的节点
        for(ArcNode *a=G.Vextices[e.v].firstarc;  a;  a=a->nextarc){
            int w = a->adjvex;
            if(!visite[w]){
                CSTree p = (CSTree)malloc(sizeof(CSNode));
                *p = {G.Vextices[w].data, NULL, NULL};
                Q.push({p, w});visite[w] = visited;

                if(first){
                    q->firstchild = p;  
                    first = false; 
                }
                else q->nextsibling = p;
                q = p;   // 更新上一节点==>指向上一兄弟
            }//if
        }//for
    }//while
    return true;
}

Status TreeTransOperator(TElemType e)    // 二叉树遍历算子
{
    // 对数据元素操作的应用函数
    cout << e << " ";
    return true;
}
Status CSFPreRootOrder(CSTree T, Status(*Visit)(TElemType e))    // 前根遍历
{
	if(T == NULL){
        return true;
    }
	Visit(T->data);
	CSFPreRootOrder(T->firstchild, Visit);
	CSFPreRootOrder(T->nextsibling, Visit);
    return true;
}
Status CSFPostRootOrder(CSTree T, Status(*Visit)(TElemType e))		// 后根遍历
{
	if(T == NULL){
        return true;
    }
	CSFPostRootOrder(T->firstchild, Visit);
	Visit(T->data);
	CSFPostRootOrder(T->nextsibling, Visit);
    return true;
}
Status LevelOrderTraverse(CSTree T, Status(*Visit)(TElemType e))
{
	if(T == NULL){
        cout << "This is an empty tree.\n";
        return true;
    }
	queue<CSNode*> q;
    q.push(T);
    int i = 0, width = 1;
    while(!q.empty())
    {
        CSTree P;
        inp(i,0,width-1){
            if(!q.empty()){
                P = q.front();q.pop();
                q.push(P);
            }
            while(P->nextsibling){
                q.push(P->nextsibling);
                P = P->nextsibling;
            }
        }

        width = q.size();
        cout << "Nodes number of the current layer: " << width << " ";
        inp(i,0,width-1){
            if(!q.empty()){
                P = q.front();q.pop();
            }
            Visit(P->data);
            if(P->firstchild) q.push(P->firstchild);
        }
        cout << endl;
    }
    return true;
}
Status ForestPrint(CSTree T)
{
    int i = 1;
    CSTree P = T;
    while(T){
        cout << "--------------------Subtree " << i++ <<"------------------\n";
        cout << "CS_Forest First root Traverse:\n";
        TreeTransOperator(T->data);
        CSFPreRootOrder(T->firstchild, TreeTransOperator);     // 等于二叉树中先序
        
        cout << endl << "CS_Forest Post root Traverse:\n";
        CSFPostRootOrder(T->firstchild, TreeTransOperator);    // 等于二叉树中中序
        TreeTransOperator(T->data);
        cout << endl;
        T = T->nextsibling;
    }
    cout << "CS_Forest Level Traverse:\n";
    LevelOrderTraverse(P, TreeTransOperator);
    return true;
}