#include<iostream>
#include<algorithm>
using namespace std;
#define Max_Vertex_Num 103

bool Visit[Max_Vertex_Num];
int AM[Max_Vertex_Num][Max_Vertex_Num];
int DFSTranvers(int p, int num);
int main()
{
    int n = 0, vexnum = 0;cin >> n;
    while(n--){
        cin >> vexnum;
        for(int i=1;i<=vexnum;i++){
            for(int j=1;j<=vexnum;j++)
                scanf("%d",&AM[i][j]);
            Visit[i] = false;
        }
        /*int ans = 0;
        for(int i=1;i<=vexnum;i++){
            if(Visit[i]) continue;
            Visit[i] = true;
            ans += DFSTranvers(i, vexnum);
        }*/
        Visit[1] = true;
        if(DFSTranvers(1, vexnum)) cout << 1;
        else cout << 0;
    }
    return 0;
}
int DFSTranvers(int p, int num)
{
    int sign = 0;
    for(int i=1;i<=num;i++){
        if(Visit[i]&&AM[p][i]) sign = 1;
        if(!Visit[i]&&AM[p][i]){
            Visit[i]=true;
            sign += DFSTranvers(i, num);
            Visit[i] = false;
        }
    }
    return sign;
}