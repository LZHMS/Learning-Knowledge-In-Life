#include<iostream>
using namespace std;
#define MAXSIZE 100
#define KeyType int
typedef struct{
    KeyType key;         //关键字类型
}ElemType;
typedef struct{
    ElemType r[MAXSIZE+1];
    int length;
}SqList;            // 顺序表类型
int Partition(SqList &L, int low, int high);
int main()
{
    SqList L;
    cin >> L.length;
    for(int i=0;i<L.length;i++){
        cin >> L.r[i+1].key;
    }
    Partition(L, 1, L.length);
    for(int i=0;i<L.length;i++){
        cout << L.r[i+1].key << " ";
    }
    cout << endl;
    return 0;
}
int Partition(SqList &L, int low, int high)
{
    L.r[0] = L.r[low];     // 暂存
    int piv = L.r[low].key;   // 子表的第一个记录当作枢轴
    while(low < high)
    {
        while(low<high && L.r[high].key >= piv) high--;
        L.r[low] = L.r[high];      // 将记录移到低位
        while(low<high && L.r[low].key <= piv) low++;
        L.r[high] = L.r[low];      // 将记录移到高位
    }
    L.r[low] = L.r[0];        // 枢轴记录到位
    return low;
}