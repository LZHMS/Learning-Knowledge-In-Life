#include<iostream>
#include<climits>
#include<string>
using namespace std;
#define inp(i,x,y) for(i=x;i<=y;i++)
#define Status bool
#define MAXSIZE 100
#define Max_time_num 4
#define KeyType int 
#define LT(x,y) (x < y ? 1:0)
typedef struct{
    KeyType key;         //关键字类型
}ElemType;
typedef struct{
    ElemType r[MAXSIZE+1];    // r[0]作哨兵
    int length;
}SqList;            // 顺序表类型
Status ShellInsert(SqList &L, int dk);
int main()
{
    int i = 0;
    SqList L;
    cin >> L.length;
    inp(i,1,L.length) cin >> L.r[i].key;
    ShellInsert(L, L.length/2);
    inp(i,1,L.length) cout << L.r[i].key << " ";
    cout << endl;
    return 0;
}
Status ShellInsert(SqList &L, int dk)
{
    int i = 0, j = 0;
    inp(i, dk+1, L.length){
        if(LT(L.r[i].key, L.r[i-dk].key)){
            L.r[0] = L.r[i];   
            for(j=i-dk;j>0 && LT(L.r[0].key, L.r[j].key); j-=dk)
                L.r[j+dk] = L.r[j];
            L.r[j+dk] = L.r[0];
        }
    }
    return true;
}
