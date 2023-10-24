#include<iostream>
#include<stack>
#include<cstring>
using namespace std;
int main()
{
    char str[103];
    scanf("%s",str);
    stack<char> pre;
    int length = strlen(str), flag = 1, i = 0;
    for(i=0;i<length/2;i++)
        pre.push(str[i]);

    if(length%2) i++;
    for(;flag&&i<length;i++){
        if(str[i] != pre.top()) flag = 0;
        pre.pop();
    }
    if(flag) cout << "right\n";
    else cout << "wrong\n";
    return  0;
}
