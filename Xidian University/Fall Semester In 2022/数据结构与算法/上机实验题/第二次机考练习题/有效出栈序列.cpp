#include<iostream>
#include<stack>
using namespace std;
int Obsnum[1003];
bool Stack_Check(int N)
{
    stack<int> obs;
    int cnt = 0, temp = 0;
    for (int i = 0; i < N; i++) {
        cin >> temp;
        if (obs.empty()) obs.push(Obsnum[cnt++]);
        
        while (obs.top() != temp) {
            if(cnt >= N)
                return false;   //没有找到即不能匹配
            obs.push(Obsnum[cnt++]);
        }
        obs.pop();
    }
    return true;
}
int main()
{
    int N = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        Obsnum[i] = i+1;
    }
    if(Stack_Check(N))
        cout << "yes\n";
    else cout << "no\n";
    return 0;
}