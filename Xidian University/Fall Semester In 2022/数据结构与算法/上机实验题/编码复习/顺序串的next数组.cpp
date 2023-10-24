#include<iostream>
using namespace std;
const int Max_num = 200; 
int main()
{
    char st[Max_num];
    int Next[Max_num], nextval[Max_num];
    int n; cin >> n;
    for(int i=0;i<n;i++){
        cin >> st[i];
    }
    int i=0,j=-1;Next[0] = -1;
    while(i<n){
        if(j==-1||st[i]==st[j]){
            i++,j++;
            Next[i] = j;
        }else
            j = Next[j];
    }
    i=0,j=-1;nextval[0] = -1;
    while(i<n){
        if(j==-1||st[i]==st[j]){
            i++,j++;
            if(st[i]!=st[j]) nextval[i] = j;
            else nextval[i] = nextval[j];
        }else
            j = nextval[j];
    }
    cout << "Output the next array:\n";
    for(int i=0;i<n;i++){           
        cout << Next[i] << ' ';
    }
    cout << "\nOutput the nextval array:\n";
    for(int i=0;i<n;i++){           
        cout << nextval[i] << ' ';
    }
    return 0;
}