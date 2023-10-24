#include<iostream>
using namespace std;
#define MAXSIZE 100
#define Status bool
#define KeyType int
#define InfoType int
typedef struct{
    KeyType key;         //关键字类型
    InfoType info;       // 数据项
}ElemType;
typedef struct{
    ElemType r[MAXSIZE+1];
    int length;
}SqList;            // 顺序表类型
/*---------------快速排序---------------*/
int Partition(SqList &L, int low, int high);
// 利用三者取中法则改进
int AdvancedPartition(SqList &L, int low, int high);
Status QuickSort(SqList &L);
Status QSort(SqList &L, int low,int high);
int main()
{
    SqList L;
    cout << "Input the length of sequence: ";
    cin >> L.length;
    for(int i=0;i<L.length;i++){
        cin >> L.r[i+1].key;
    }
    QuickSort(L);
    cout << "After quick sorting output the sequence:\n";
    for(int i=0;i<L.length;i++){
        cout << L.r[i+1].key << " ";
    }
    cout << endl;
    return 0;
}
Status QuickSort(SqList &L)
{
    // 对顺序表做快速排序
    QSort(L, 1, L.length);
    return true;
}
Status QSort(SqList &L, int low,int high)
{
    if(low < high){      // 长度大于1
        int piv = AdvancedPartition(L, low, high);   // 寻找枢轴位置
        // 由于枢轴位置已到位，故跳过枢轴位，将序列一分为二，递归排序
        QSort(L, low, piv-1);
        QSort(L, piv+1, high);
    }
    return true;
}
int Partition(SqList &L, int low, int high)
{
    // 寻找枢轴函数，在low和high之间寻找枢轴，使枢轴记录到位，并返回其位置
    // 使得枢轴之前(后)均不大于(小于)它
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
    return low;     // 返回枢轴位置
}
int AdvancedPartition(SqList &L, int low, int high)
{
    // 利用三者取中规则寻找枢轴函数
    int piv = 0, inpiv = 0;   // 记录子表的枢轴,枢轴下标
    int maxv = L.r[low].key > L.r[high].key?low:high;
    int minv = low + high - maxv;
    int midv = (low+high)/2;
    if(L.r[midv].key < L.r[minv].key) inpiv = minv;
    else if(L.r[midv].key > L.r[maxv].key) inpiv = maxv;
    else inpiv = midv;
    // 进行转换
    L.r[0] = L.r[inpiv];
    piv = L.r[inpiv].key;
    if(inpiv != low) L.r[inpiv] = L.r[low];
    while(low < high)
    {
        while(low<high && L.r[high].key >= piv) high--;
        L.r[low] = L.r[high];      // 将记录移到低位
        while(low<high && L.r[low].key <= piv) low++;
        L.r[high] = L.r[low];      // 将记录移到高位
    }
    L.r[low] = L.r[0];        // 枢轴记录到位
    return low;     // 返回枢轴位置
}