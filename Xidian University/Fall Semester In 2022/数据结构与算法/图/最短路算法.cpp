#include"MGraph.h"
//-----------------最短路算法--------------//
// 采用邻接矩阵存储表示
//-----------------Dijkstra算法求最短路径--------------//
Status DijsMinPath(MGraph G, int v0);
Status DispDijsPaths(MGraph G, int *D, int *fa, bool *final, int v0);
Status MinDijsPrint(MGraph G, int *fa, int v, int v0);
//-----------------Floyd算法求最短路径--------------//
Status FloydMinPath(MGraph G);
Status MinFloydPrint(MGraph G, int *path, int v, int w); 
Status DispFloydPaths(MGraph G, int *D, int *path);
int main()
{
    MGraph G;
    CreateGraph(G);
    GraphPrint(G);
    cout << "----------------------Dijkstra MinPath Problem Page------------------\n";
    cout << "Input the source node: ";
    VertexType sv;
    cin >> sv;
    int v0 = LocateVex(G, sv);
    DijsMinPath(G, v0);
    cout << "-----------------------Floyd MinPath Problem Page---------------------\n";
    FloydMinPath(G);
    return 0;
}
/*-------------------------------Dijkstra ALgorithm-----------------------*/
Status DijsMinPath(MGraph G, int v0)
{
    // D[v]表示v0到v的最短路径带权长度
    // fa[v]=w表示通过w中转，即D(v0,w)+arc(w,v)便于回溯路径
    // final[v]：标识数组，为True当且仅当v属于S, 即已经求得v0到v最短路
    int fa[Max_Vertex_Num], D[Max_Vertex_Num];
    bool final[Max_Vertex_Num];
    int v = 0, w = 0, i = 0;
    // 初始化操作
    inp(v,0, G.vexnum-1){
        final[v] = false;    
        D[v] = G.arcs[v0][v].adj;
        // v0到v邻接
        if(D[v] != INFINITY) fa[v] = v0; // 路径回溯
    }

    final[v0] = true;   // 初始化节点v0属于S集
    // 取min(d(v0,v)) v属于V-S, 即求剩余节点中到v0距离最短得节点v
    inp(i,1,G.vexnum-1){
        // 当前所知离v0顶点的最近距离, 初始未找到为无穷大
        int min_path = INFINITY;   
        inp(w,0,G.vexnum-1){
            if(!final[w])    // w节点在V-S中
                if(D[w] < min_path){  // 取min
                    v = w;      
                    min_path = D[w];
                }
        }
        // 将选中的节点即确定距离得节点加入S集中
        if(min_path != INFINITY) final[v] = true;    
        else break;
        // 通过新选的节点v中转更新V-S中节点距离操作
        inp(w,0,G.vexnum-1){
            if(!final[w] && G.arcs[v][w].adj != INFINITY)    // 避免最大值上溢问题的特判
                if(min_path + G.arcs[v][w].adj < D[w]){
                    D[w] = min_path + G.arcs[v][w].adj;
                    fa[w] = v;    // 上次中转节点    
                }
        }
    }
    DispDijsPaths(G, D, fa, final, v0);
    return true;
}
Status DispDijsPaths(MGraph G, int *D, int *fa, bool *final, int v0)
{    
    int i = 0;
    inp(i, 0, G.vexnum-1){
        if(i != v0){   // 不包括源点
	        if(final[i]){    // 如果已确定最短距离
                cout << "from " << G.vexs[v0] << " to " << G.vexs[i] << " the shortest path length: " << D[i];
                cout << endl << "Display the path:\n" << G.vexs[v0] << "->"; /*输出路径上的起点*/
                MinDijsPrint(G, fa, i, v0);	/*输出路径上的中间点*/
                cout << G.vexs[i] << endl;	/*输出路径上的终点*/
            }
            else cout << "from " << G.vexs[v0] << " to " << G.vexs[i] << " there is no road.\n";
	   }  
    }
    return true;
}
Status MinDijsPrint(MGraph G, int *fa, int v, int v0)
{
    // 回溯输出v到v0的最短路径
    int w = fa[v];
    if(w == v0){
        return true;  // 找到了起点则返回
    }
    MinDijsPrint(G, fa, w, v0);   // 找w顶点的父顶点
    cout << G.vexs[w] << "->";
    return true;
}
/*-------------------------------Dijkstra ALgorithm-----------------------*/

/*-------------------------------Floyd ALgorithm--------------------------*/
Status FloydMinPath(MGraph G)
{  
    // path[v][w]表示v到w最短路径上经过的最后一个节点即w的父节点
    int path[G.vexnum][G.vexnum], D[G.vexnum][G.vexnum];
    int i = 0, j = 0, k = 0;
    inp(i, 0, G.vexnum-1)    //矩阵 D与 path初始化
        inp(j, 0, G.vexnum-1){
            D[i][j] = G.arcs[i][j].adj;
            if(D[i][j] != INFINITY)  path[i][j] = i;     // 头节点 	    	
	        else path[i][j] = -1;	    // i到j无路径	
        }
    
    // 生成D(k)及path(k)
    inp(k, 0, G.vexnum-1)
        inp(i, 0, G.vexnum-1)
            inp(j, 0, G.vexnum-1)
                // 加入Vk节点
                if(D[i][k] != INFINITY && D[k][j] != INFINITY)    // 解决INF运算溢出的问题
                    if(D[i][j] > D[i][k] + D[k][j]){ 
                        D[i][j] = D[i][k] + D[k][j];
                        path[i][j] = path[k][j];   //缩短路径长度, 经过 k 到 j
                        //注解：相当于对<i,j>路径改向，<i,j>方向改为经k的<k,j>方向
                    }
    DispFloydPaths(G, &D[0][0], &path[0][0]);
    return true;
}
Status DispFloydPaths(MGraph G, int *D, int *path)
{    
    int i = 0, j = 0, k = 0;
    inp(i,0,G.vexnum-1){
        cout << "-------------------------------------------------------------\n";
        inp(j,0,G.vexnum-1){
            if(i == j) continue;     // 不包括节点自身
            if(D[i*G.vexnum + j] != INFINITY){
                cout << "from " << G.vexs[i] << " to " << G.vexs[j] << " the shortest path length: " << D[i*G.vexnum + j] << endl;
                cout << "Display the path:\n" << G.vexs[i] << "->"; /*输出路径上的起点*/
                MinFloydPrint(G, path, i, j);	/*输出路径上的中间点*/
                cout << G.vexs[j] << endl;	/*输出路径上的终点*/
            }
            else cout << "from " << G.vexs[i] << " to " << G.vexs[j] << " there is no road.\n";
        }
        cout << "-------------------------------------------------------------\n";
    }
    return true;
}
Status MinFloydPrint(MGraph G, int *path, int v, int w)    
{
    // 回溯输出v到w的最短路径
    int p = path[v*G.vexnum + w];
    if(p == v){
        return true;  // 找到了起点则返回
    }
    MinFloydPrint(G, path, v, p);   // 找w顶点的父顶点
    cout << G.vexs[p] << "->";
    return true;
}
/*-------------------------------Floyd ALgorithm--------------------------*/