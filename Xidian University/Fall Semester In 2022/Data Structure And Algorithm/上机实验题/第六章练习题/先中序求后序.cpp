#include<iostream>
#include<cstring>
using namespace std;
#define Max_Length 27
#define inp(i,x,y) for(i=x;i<=y;i++)
char pre[Max_Length], in[Max_Length], post[Max_Length];
int m = 0, pos = 0;
// m表示先序中的根，l表示子树左界，r表示子树右界
void postorder(int l, int r)
{
    if((r-l) < 0){
        return ;
    }
    int i;
    inp(i,l,r) 
        if(in[i]==pre[m]){
            m++;
            postorder(l,i-1);  // 左子树
            postorder(i+1,r);   // 右子树
            post[pos++] = in[i];
        }
    return ;
}
int main()
{
    cin >> pre >> in;
    int n = strlen(pre);
    postorder(0,n-1);
    cout << post;
    return 0;
}
