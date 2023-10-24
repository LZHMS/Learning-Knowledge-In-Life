#include<iostream>
#include<climits>
#include<string>
using namespace std;
#define inp(i,x,y) for(i=x;i<=y;i++)
#define dep(i,x,y) for(i=x;i>=y;i--)

#define Status bool
#define MAXSIZE 100
#define Max_time_num 4
#define KeyType int 
#define InfoType string
#define LT(x,y) (x < y ? 1:0)
typedef struct{
    KeyType key;         //关键字类型
    InfoType info;       // 数据项
}ElemType;
typedef struct{
    ElemType r[MAXSIZE+1];    // r[0]作哨兵
    int length;
}SqList;            // 顺序表类型
// 表插入排序数据结构
typedef struct{
    KeyType key;    
    int next;
}SLNode;
typedef struct{
    SLNode r[MAXSIZE+1];    // 0号单元为表头结点
    int length;      // 链表当前长度
}SLinkList;       // 静态链表类型

//----------------直接插入排序--------------
Status InsertSort(SqList L);
//----------------折半插入排序--------------
Status BInsertSort(SqList L);
//----------------表插入排序--------------
Status ListInsertSort(SLinkList &SL);
Status Arrange(SLinkList &SL);   // 重排
//-----------------希尔排序--------------
Status ShellInsert(SqList &L, int dk);
Status ShellSort(SqList L,int* dlta,int t);
int main()
{
    int i = 0, j = 0;

    SqList L;
    cin >> L.length;
    inp(i,1,L.length) cin >> L.r[i].key;

    // 进行排序
    InsertSort(L);
    BInsertSort(L);
    // 希尔排序增量数组
    int* dlta = new int[Max_time_num];
    inp(i, 0, Max_time_num)
        if(i<=2) dlta[i] = i+1;
        else if(i==3) dlta[i] = 5;
        else dlta[i] = 9;
    
    ShellSort(L, dlta, 3);
    // 表排序
    SLinkList SL;
    cin >> SL.length;
    inp(i,1,SL.length){
        cin >> SL.r[i].key;
    }
    SL.r[i].key = INT_MAX;
    if(ListInsertSort(SL)){
        cout << "List InsertSort Result:\n";
        inp(i,0,SL.length){
            cout << "<" << SL.r[i].key << ", " << SL.r[i].next << "> ";
        }
        cout << endl;
    }
    cout << "Rearrange Records Result:\n";
    if(Arrange(SL)){
        inp(i,1,SL.length){
            cout << "<" << SL.r[i].key << ", " << SL.r[i].next << "> ";
        }
        cout << endl;
    }
    delete[] dlta;
    return 0;
}
Status InsertSort(SqList L)
{
    int i = 0, j = 0;
    // 对顺序表 L 进行直接插入排序
    inp(i, 2, L.length){
        if(LT(L.r[i].key, L.r[i-1].key)){
            L.r[0] = L.r[i];     // 复制为哨兵
            L.r[i] = L.r[i-1];
            for(j=i-2;LT(L.r[0].key, L.r[j].key);j--)
                L.r[j+1] = L.r[j];    // 记录后移
            L.r[j+1] = L.r[0];       // 插入正确位置j+1
        }
    }
    cout << "InsertSort Result:\n";
        inp(i,1,L.length)
            cout << L.r[i].key << " ";
        cout << endl;
    return true;
}
Status BInsertSort(SqList L)
{
    // 对顺序表L作折半插入排序
    int i = 0, j = 0;
    inp(i, 2, L.length){
        L.r[0] = L.r[i];    // 哨兵
        int low = 1, high = i - 1;   // 默认前i个位置已经排好序
        while(low <= high){
            int m = (low + high) / 2;
            if(LT(L.r[0].key, L.r[m].key)) high = m-1;
            else low = m + 1;
        }// 结束条件是high < low 退出时待插入位置即是high之后 low之前
        dep(j,i-1,high+1) L.r[j+1] = L.r[j];     // 记录后移
        L.r[high + 1] = L.r[0];     // high指向待插位置之前
        //等价于
        /* dep(j,i-1,low) L.r[j+1] = L.r[j];     // 记录后移
        L.r[low] = L.r[0];*/
    }
    cout << "Binary InsertSort Result:\n";
        inp(i,1,L.length)
            cout << L.r[i].key << " ";
        cout << endl;
    return true;
}
Status ListInsertSort(SLinkList &SL)
{
    // 初始化操作
    SL.r[0].next = 1;SL.r[1].next = 0;
    int i=0,j=0,k=0;
    inp(i, 2, SL.length){
        // j 指向前一节点
        j = 0; k = SL.r[j].next;
        while(k > 0 && LT(SL.r[k].key, SL.r[i].key)){
            j = k;k = SL.r[j].next;
        }
        SL.r[i].next = SL.r[j].next;   // 移动指针
        SL.r[j].next = i;
    }
    return true;
}
Status Arrange(SLinkList &SL)
{
    /*--------重排记录---------*/
    // 根据静态链表SL中各节点的指针值调整记录位置，使得SL中记录按关键字非递减有序顺序排列
    int i=0, j=0;
    int p = SL.r[0].next;      // p指示第一个记录的当前位置
    inp(i, 1, SL.length-1){
        // p指向的是当前待调整的位置，默认前i个位置已经排好序
        // 前i个位置已经定好顺序
        // 当p < i时，待调整元素已经被转移走了，因此需要往后寻找
        while(p < i) p = SL.r[p].next;
        int q = SL.r[p].next;    // 获取尚未调整的下一元素，以防后面处理造成链表中断
        if(p != i){   // 如果待调元素位置p不是i即第i个记录未到位
            SLNode temp = SL.r[p];
            SL.r[p] = SL.r[i];
            SL.r[i] = temp; 
            SL.r[i].next = p;
        }
        p = q;     // 获取下一待定位元素位置
    }
    return true;                            
}
Status ShellSort(SqList L, int* dlta, int t)
{
    // 按增量序列dlta[0..t-1]对顺序表L进行希尔排序
    int i = 0;
    inp(i,0,t-1){
        ShellInsert(L, dlta[i]);
    }
    cout << "Shell InsertSort Result:\n";
        inp(i,1,L.length)
            cout << L.r[i].key << " ";
        cout << endl;
    return true;
}
Status ShellInsert(SqList &L, int dk)
{
    int i = 0, j = 0;
    inp(i,dk+1,L.length){
        if(LT(L.r[i].key, L.r[i-dk].key)){
            // 在不同增量下存在按增量前溯时不能到0位置，因此不能设置哨兵
            L.r[0] = L.r[i];         // 暂存在r[0]位置
            for(j=i-dk;j>0 && LT(L.r[0].key, L.r[j].key); j-=dk)
                // 子序列插入排序时子序列前溯
                L.r[j+dk] = L.r[j];   // 记录后移
            L.r[j+dk] = L.r[0];
        }
    }
    return true;
}
