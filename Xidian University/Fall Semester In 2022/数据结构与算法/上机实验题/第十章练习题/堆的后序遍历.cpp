#include<iostream>
using namespace std;
#define MAXSIZE 100
#define Status bool
#define KeyType int
#define LT(x, y) (x>y?1:0)
typedef struct{
    KeyType key;         //关键字类型
}ElemType;
typedef struct{
    ElemType r[MAXSIZE+1];
    int length;
}SqList;            // 顺序表类型
typedef SqList HeapType;    // 堆类型
void PostTranver(HeapType H, int root);
Status HeapAdjust(HeapType &H);
int main()
{
    HeapType H;
    cin >> H.length; H.length++;     // n+1
    for(int i=1;i<=H.length;i++)
        cin >> H.r[i].key;
    HeapAdjust(H);
    PostTranver(H, 1);
    return 0;
}
Status HeapAdjust(HeapType &H)
{
    int temp = H.length;
    H.r[0].key = H.r[H.length].key;
    while(temp > 1){
        if(H.r[0].key >= H.r[temp/2].key) break;
        H.r[temp].key = H.r[temp/2].key;
        temp /= 2;
    }
    H.r[temp].key = H.r[0].key;
    return true;
}
void PostTranver(HeapType H, int root)
{
    if(2*root <= H.length) PostTranver(H, 2*root);
    if(2*root+1 <= H.length) PostTranver(H, 2*root+1);
    cout << H.r[root].key << " ";
    return ;
}