#include<iostream>
#include<stack>
#include<cstring>
using namespace std;

int main()
{
    char op = '0';
    double ans = 0;
    stack<double> num;
    while(true){
        op = getchar();
        if(op=='\n') break;
        if(op>='0'&&op<='9') num.push(op-'0');
        else{
            double a = num.top();
            num.pop();
            double b = num.top();
            num.pop();
            switch(op){
                case '+':
                ans = a+b;
                break;
                case '-':
                ans = b-a;
                break;
                case '*':
                ans = a*b;
                break;
                case '/':
                ans = b/a;
                break;
                default: break;
            }
            num.push(ans);
        }
    }
    cout << num.top() << endl;
    return 0;
}