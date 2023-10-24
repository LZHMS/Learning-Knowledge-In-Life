#include<iostream>
using namespace std;
#define MAXSIZE 100
#define Status bool
#define KeyType int
#define InfoType int
#define LT(x, y) (x<y?1:0)
typedef struct{
    KeyType key;         //关键字类型
    InfoType info;       // 数据项
}ElemType;
typedef struct{
    ElemType r[MAXSIZE+1];
    int length;
}SqList;            // 顺序表类型
typedef SqList HeapType;    // 堆类型

Status HeapAdjust(HeapType &H, int s, int m);
Status HeapSort(HeapType &H);
int main()
{
    HeapType H;
    cout << "Input the length of the sequence:\n";
    cin >> H.length;
    for(int i=1;i<=H.length;i++)
        cin >> H.r[i].key;
    HeapSort(H);
    cout << "After Heap Sorting output the sequence:\n";
    for(int i=1;i<=H.length;i++)
        cout << H.r[i].key << " ";
    return 0;
}
Status HeapAdjust(HeapType &H, int s, int m)
{
    // 除H.r[s].key之外其余元素均满足堆的定义
    // 本函数调整H.r[s]的关键字使得H.r[s...m]成为一个大顶堆
    ElemType rc = H.r[s];
    for(int j=2*s;j<=m;j*=2){    // 沿key较大的孩子节点向下筛选
        //下句主要从s的孩子节点中挑选最大值，j为其下标
        //判定j<m因为当只有一个孩子即左孩子时不需移动 j
        if(j<m && LT(H.r[j].key, H.r[j+1].key)) j++;
        if(!LT(rc.key, H.r[j].key)) break;    
        H.r[s] = H.r[j];   // 更新较大值（向上传递）
        s = j;    // 沿较大孩子所在子树向下筛选
    }
    H.r[s] = rc;   // 最终定位
    return true;
}

Status HeapSort(HeapType &H)
{
    // 对顺序表H进行堆排序
    for(int i=H.length/2;i>0;--i)  // 初始对所有元素建立大顶堆
        HeapAdjust(H, i, H.length);

    for(int i=H.length;i>1;i--){
        ElemType temp = H.r[1];   // 每次最大值在堆顶H.r[1]
        H.r[1] = H.r[i];          // 每次和最后一个元素交换即输出元素后最后一个元素上堆顶
        H.r[i] = temp;
        HeapAdjust(H, 1, i-1);   // 重新调整
    }
    return true;
}