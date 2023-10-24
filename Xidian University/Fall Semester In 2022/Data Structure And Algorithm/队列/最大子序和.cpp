#include<iostream>
#include<cstring>
using namespace std;
#define inp(i,x,y) for(i=x;i<=y;i++)
#define dep(i,x,y) for(i=x;i>=y;i--)

typedef long long ll;

inline int read()
{
    int x=0,f=1;
    char ch = getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        x = x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}


const int N = 3e5+5;
int n,m;
ll presum[N];
int q[N];   // 模拟队列窗口

int main()
{
    int i,j,hh=0,tt=-1; // 指向当前窗口的首尾
    ll ans=-1e18;     // 初始置于无穷小
    
    n = read(),m=read();
    // 读入前缀和
    inp(i,1,n) presum[i]=read(),presum[i]+=presum[i-1];

    q[++tt]=0;
    //维持一个单调增队列，队首元素的前缀和最小
    inp(i,1,n){
        // 寻找窗口最值(在队首位置)
        ans=max(ans,presum[i]-presum[q[hh]]);
        while(hh<=tt&&presum[q[tt]]>presum[i]) --tt;
        q[++tt]=i;
        if(i-q[hh]>=m) ++hh;       
    }
    printf("%lld\n",ans);
    return 0;
}