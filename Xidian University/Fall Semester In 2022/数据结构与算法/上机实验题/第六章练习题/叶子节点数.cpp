#include<iostream>
#include<cstring>
using namespace std;
#define Max_Length 100
char st[Max_Length]; 

int main()
{
    cin >> &st[1];
    
    int cnt = 0, n = strlen(&st[1]);
    st[n] = '@';
    for(int i=1;i<=n;i++){
        if(st[i]=='@') continue;
        if(2*i+1 <= n){
            if(st[2*i]=='@'&&st[2*i+1]=='@'){
                printf("%c ",st[i]);
                cnt++;
            }
        }else{
            printf("%c ",st[i]);
            cnt++;
        }
    }
    cout << endl << cnt << endl;
    return 0;
}