#include<iostream>
#include<list>
#include<set>
#include<iomanip>
#include<algorithm>
using namespace std;
const int N = 103;
list<pair<pair<int,int>,int>> ls;
set<int> myset;
int a[N], b[N], c[N];
int m,n;
void ListSort()
{
    int cp = m;
    while(cp!=-1){
        int st = find(a,a+n,cp)-a;
        if(myset.find(abs(b[st])) == myset.end()){
            ls.push_back(make_pair(make_pair(a[st],b[st]),c[st]));
            myset.insert(abs(b[st]));
        }else
            ls.back().second = c[st];
        cp = c[st];
    }
}
void ListPrint()
{
    cout << ls.size() << endl;
    for(const auto &it: ls){
        cout << setw(5) << setfill('0') << it.first.first << " ";
        cout << it.first.second << " ";
        if (it.second == -1) cout << "-1" << endl;
        else  cout << setw(5) << setfill('0') << it.second << endl;
    }
}
int main()
{
    cin >> m >> n;
    for(int i=0;i<n;i++) cin >> a[i] >> b[i] >> c[i];
    ListSort();
    ListPrint();
    return 0;
}