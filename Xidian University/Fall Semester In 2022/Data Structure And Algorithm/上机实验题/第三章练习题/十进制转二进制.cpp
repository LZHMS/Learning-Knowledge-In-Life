#include<iostream>
#include<stack>
using namespace std;
void trans(int a)
{
    stack<int> mystack;
    if(a==0) cout << 0;
    else{
        while(a){
            mystack.push(a%2);
            a /= 2;
        }
        while(!mystack.empty()){
            cout << mystack.top();
            mystack.pop();
        }
    }
    cout << " ";
    return ;
}
int main()
{
    int a = 0,b = 0,c = 0;
    cin >> a >> b >> c;
    trans(a);trans(b);trans(c);
    return 0;
}