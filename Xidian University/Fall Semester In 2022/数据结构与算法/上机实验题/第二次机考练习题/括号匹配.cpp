#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
int main()
{
    stack<char> st;
    char ch;
    ch = getchar();
    while(ch!='\n'){
        switch(ch){
            case '(':case '[':
            case '{':st.push(ch);
                    break;
            case ')':
                if(!st.empty() && st.top() =='(') st.pop();
                else st.push(ch);
                break;
            case ']':
                if(!st.empty() && st.top() =='[') st.pop();
                else st.push(ch);
                break;
            case '}':
                if(!st.empty() && st.top() =='{') st.pop();
                else st.push(ch);
                break;
            default:break;
        }
        ch = getchar();
    }
    if(st.empty()) cout << "right\n";
    else cout << "wrong\n";
    return 0;
}
