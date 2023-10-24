#include<iostream>
using namespace std;
#define Max_vex_num 101
#define Max_edge_num 101
// 邻接表的数组表示
typedef struct AList{
    int tot;  
    int head[Max_vex_num];    // 表头
    int edge[Max_edge_num];
    int ver[Max_edge_num];
    int next[Max_edge_num];
    AList(){
        tot = 0;
    }
}AList;
AList AL;
void AListAdd(int x, int y, int z);
int main()
{
    int num = 0, x = 0,y = 0;
    cin >> num;
    for(int i=1;i<=num-1;i++){
        cin >> x >> y;
        AListAdd(x,y,1);
    }
    for(int x=1;x<=num;x++)
        // 访问从x出发的所有边
        for(int i=AL.head[x];i;i=AL.next[i])
            cout << x << " " << AL.ver[i] << " " << AL.edge[i] << endl;
    return 0;
}
void AListAdd(int x, int y, int z)
{
    AL.edge[++AL.tot] = z;
    AL.ver[AL.tot] = y;
    AL.next[AL.tot] = AL.head[x], AL.head[x] = AL.tot;
    return ;
}
