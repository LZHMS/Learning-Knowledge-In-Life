#include<iostream>
#include<list>
using namespace std;

int main()
{
    int num = 0;
    cin >> num;
    list<int> q;
    for(int i=1;i<=num;i++){
        if(i%2==1||num<=3) q.push_back(i);
    }
    while(q.size()>3){
        auto it = q.begin();
        it++;it++;
        int temp = q.size();
        for(int i=3;i<=temp;i+=3){
            it = q.erase(it);
            it++;it++;
        }
        if(q.size()<=3) break;
        it = q.begin();it++;
        temp = q.size();
        for(int i=2;i<=temp;i+=2){
            it = q.erase(it);
            it++;
        }
    }
    for (auto it = q.begin(); it != q.end(); it++)
    {
        cout << *it << " ";
    }
    return 0;
}
