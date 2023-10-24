#include<iostream>
#include<string>
#include<stack>
using namespace std;
//两数的四则运算
double value(double op1, double op2, char ch)
{
    switch (ch) {
    case '+': return op1 + op2;
    case '-': return op1 - op2;
    case '*': return op1 * op2;
    case '/': return op1 / op2;
    }
    return 0;
}
int main()
{
    string str;
    getline(cin, str);
    stack<char> s;
    int i = 0;
    while (str[i] != '\0')
        s.push(str[i++]);
    stack<double> result;

    while (!s.empty()) {
        char temp = s.top(); s.pop();
        double base = 1, numtemp = 0;
        if (temp >= '0' && temp <= '9') {
            while (!s.empty() && temp >= '0' && temp <= '9') {
                numtemp += base * (temp - '0');
                base *= 10;
                temp = s.top(); s.pop();
            }
        }
        else if(!s.empty()) s.pop();
        if (numtemp > 0)
            result.push(numtemp);
        else {
            double op1 = result.top();
            result.pop();
            double op2 = result.top();
            result.pop();
            result.push(value(op1, op2, temp));
        }
    }
    cout << result.top();
    return 0;
}
