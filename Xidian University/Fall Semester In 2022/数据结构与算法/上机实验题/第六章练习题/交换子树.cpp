#include<iostream>
#include<cstring>
using namespace std;
#define Max_Length 100
#define inp(i,x,y) for(i=x;i<=y;i++)
#define dep(i,x,y) for(i=x;i>=y;i--)
char st[Max_Length]; 

int main()
{
    int n = 0;
    cin >> st[++n];
    char ch = getchar();
    while(ch!='\n'){
        cin >> st[++n];
        ch = getchar();
    }
    
    int j = 0, l = 1, r = 1;
    while(l <= n){
        dep(j,r,l){
            if(j<=n) cout << st[j] << " ";
            else cout << "@ ";
        }
        l = 2*l, r = 2*r+1;
        //cout << l << " " << r <<endl; 
    }
    return 0;
}