#include<iostream>
#include<cstring>
using namespace std;
#define Max_Length 1025
#define inp(i,x,y) for(i=x;i<=y;i++)
int pre[Max_Length], in[Max_Length];

int m = 0;
// 替换原则
// m表示先序中的根，l表示子树左界，r表示子树右界
int SumTree(int l, int r)
{
    int i, temp;
    if(r == l){   // 满二叉树的性质决定的
        temp = in[r];
        in[r] = 0;
        m++;     //使得前序中越过自身节点
        return temp;
    }
    inp(i,l,r){
        if(in[i]==pre[m]){
            m++;
            temp = in[i];
            in[i] = SumTree(l, i-1) + SumTree(i+1, r);
            //cout << temp << " "<< in[i] << " " << i << " " << l << " " << r << endl;
            break;
        }
    }
    return temp+in[i];
}
int main()
{
    int n = 0, i = 0;
    cin >> n;
    inp(i,0,n-1) cin >> pre[i];
    inp(i,0,n-1) cin >> in[i];

    SumTree(0,n-1);
    inp(i,0,n-1) cout << in[i] << " ";
    return 0;
}
