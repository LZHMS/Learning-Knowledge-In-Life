#include<iostream>
#include<cstring>
#include<stack>
#include<queue>
#define Max_num 203
using namespace std;
int main()
{
    char str[Max_num];
    scanf("%s",str);
    stack<char> lang;
    stack<char> q;
    for(int i=strlen(str)-1;i>=0;i--)
        lang.push(str[i]);
    
    while(!lang.empty()){
        char temp = lang.top();lang.pop();
        if(temp == 'A') cout << "sae";
        else if(temp == 'B') cout << "tsaedsae";
        else if(temp == '('){
            char root = lang.top();lang.pop();
            while(!lang.empty() && lang.top() != ')'){
                q.push(lang.top());lang.pop();
            }
            lang.pop();
            while(!q.empty()){
                cout << root;
                if(q.top() == 'A') cout << "sae";
                else if(q.top() == 'B') cout << "tsaedsae";
                else cout << q.top();
                q.pop();
            }
            cout << root;
        }else cout << temp;
    }
    return 0;
}
