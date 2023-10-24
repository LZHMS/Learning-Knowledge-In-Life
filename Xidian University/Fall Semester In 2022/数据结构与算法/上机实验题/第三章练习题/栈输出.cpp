#include<iostream>
#include<stack>
using namespace std;
int Obsnum[1003];
bool Stack_Check(int M, int N)
{
    stack<int> obs;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        int temp = 0;
        cin >> temp;
        if (obs.empty()) {
            /*if (cnt == 5) {
                for (int j = i+1; j < N; j++) cin >> temp;
                return true;
            }
            else */
            obs.push(Obsnum[cnt++]);
        }
        while (obs.top() != temp) {
            if (cnt >= N || obs.size() >= M) {
                for (int j = i+1; j < N; j++) cin >> temp;
                return false;   //没有找到即不能匹配
            }
            obs.push(Obsnum[cnt++]);
        }
        obs.pop();
    }
    return true;
}
int main()
{
    int M = 0, N = 0, k = 0;
    cin >> M >> N >> k;
    for (int i = 0; i < N; i++) {
        cin >> Obsnum[i];
    }
    for (int i = 0; i < k; i++) {
        if (Stack_Check(M, N))
            cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}