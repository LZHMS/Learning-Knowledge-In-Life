// 问题描述
/*
Input
The first line contains two integers n and num (1 < n < 500000, 1 < num < 2000000000).
indicating the number of tree nodes and the target number.
Then n - 1 lines follow. Each line contains three integers u, u, w 
(1 < u, u < n, 1 < w < 100)describing an edge.
The first two integers are the indices of nodes that form an edge and the lastinteger indicates the weight of the edge.
Output
Output an integer which means how many paths satisfying the sum of edge weights in the pathequals to num.
Sample input
6 6
1 2 2
1 3 3
3 4 4
3 5 3
2 6 4
Sample output
2
*/
#include<iostream>
#include<queue>
using namespace std;
#define Max_num 500001
int head[Max_num], val[Max_num];
int w[Max_num],Next[Max_num], tot;
void add(int u, int v, int wtemp);
int main(int argc, char* argv[])
{
    for(int i=0;i<argc;i++){
        cout << "arg " << i << ": " << argv[i] << endl;
    }
    int n, num;cin >> n >> num;
    int u,v,wtemp;
    for(int i=1;i<n;i++){
        cin >> u >> v >> wtemp;
        add(u,v,wtemp);
    }
    int ans = 0;
    queue<pair<int, int>> q;
    q.push(make_pair(1, 0));   // 当前节点，已经走过的边权和
    while(!q.empty()){
        int h = q.front().first, wt = q.front().second;
        q.pop();
        if(!head[h] && wt == num){
            ans++;
            continue;
        }
        for(int i=head[h];i;i=Next[i]){
            q.push(make_pair(val[i], wt+w[i]));
        }
    }
    cout << ans << endl;
    return 0;
}
void add(int u, int v, int wtemp)
{
    val[++tot] = v, w[tot] = wtemp;
    Next[tot] = head[u], head[u] = tot;
    return ;
}