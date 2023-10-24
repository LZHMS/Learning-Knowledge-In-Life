#include<iostream>
#include<stack>
using namespace std;
const int Max_num = 10;
int a[Max_num];

bool Check(int n)
{
    int p = 1, m = 0;
    stack<int> st;
    while(p < n){
        cin >> m;
        if(st.empty()) st.push(a[p++]);
        while( p<=n && st.top()!=m ) st.push(a[p++]);
        if(p > n) return false;
        st.pop();
    }
    return st.empty();
}

int main()
{
    int n;cin >> n;
    for(int i=1;i<=n;i++) a[i] = i;
    if(Check(n))
        cout << "yes\n";
    else
        cout << "no\n";
    return 0;
}