#include<iostream>
using namespace std;
#define Status bool
#define Max_num 100
#define LT(x,y) (x<y?1:0)
/*-------------2-路归并排序-------------*/
typedef struct{
    int key;
}RcdType;
typedef struct{
    RcdType r[Max_num];
    int length;
}SqList;
//---------------非递归算法-------------
Status NonCurMerge(SqList &L);
Status MergeSort(RcdType *SR, RcdType *TR, int i, int m, int n);
//-----------------递归算法--------------
Status CurMerge(SqList &L);
Status MSort(RcdType *SR, RcdType *TR, int s, int t);
int main()
{
    SqList L1, L2;
    cout << "Input the length of sequence: ";
    cin >> L1.length;
    cout << "Input the elements of the sequence:\n";
    for(int i=1;i<=L1.length;i++)
        cin >> L1.r[i].key;
    L2 = L1;
    //------- 非递归算法---------
    NonCurMerge(L1);
    cout << "Output the sequence with NonCurrSortAlgorithm:\n";
    for(int i=1;i<=L1.length;i++)
        cout << L1.r[i].key << " ";
    cout << endl;
    //--------递归算法------------
    CurMerge(L2);
    cout << "Output the sequence with CurrSortAlgorithm:\n";
    for(int i=1;i<=L2.length;i++)
        cout << L2.r[i].key << " ";
    cout << endl;
    return 0;
}
Status NonCurMerge(SqList &L)
{
    SqList T;  // 内存辅助空间
    int delta = 1, n = L.length;
    T = L;
    while(delta < n){
        for(int i=1;i<=n;i+=2*delta){
            if(i+2*delta>=n) MergeSort(L.r,T.r,i,i+delta-1,n);
            else MergeSort(L.r,T.r,i,i+delta-1,i+2*delta-1);
        }
        L = T;    // 赋值转换存储方向
        delta *= 2;
    }
    return true;
}
Status MergeSort(RcdType *SR, RcdType *TR, int i, int m, int n)
{
    // 有序表归并函数 SR[i...m]、SR[m+1...n]---->TR[i...n]
    int j = m+1, k = i;
    while(i<=m&&j<=n){    // 取最小值
        if(LT(SR[i].key, SR[j].key)) TR[k++] = SR[i++];
        else TR[k++] = SR[j++];
    }
    while(i<=m) TR[k++] = SR[i++];
    while(j<=n) TR[k++] = TR[j++];
    return true;
}
// --------------递归算法-------------------
Status CurMerge(SqList &L)
{
    // 对顺序表进行归并排序
    MSort(L.r, L.r, 1, L.length);
    return true;
}
Status MSort(RcdType *SR, RcdType *TR, int s, int t)
{
    // 将SR[s..t]归并排序到TR[s...t] 
    RcdType TRtemp[Max_num];   // 内存辅助空间
    if(s==t) TR[s] = SR[s];
    else{
        int m = (s + t)/2;
        MSort(SR, TRtemp, s, m);
        MSort(SR, TRtemp, m+1, t);
        MergeSort(TRtemp, TR, s, m, t);  
    }           
    return true; 
 }           