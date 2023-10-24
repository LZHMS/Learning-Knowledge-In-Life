#include<iostream>
#include<cstdlib>
using namespace std;
typedef struct Node {
    int data1;     //表示系数
    int data2;     //表示指数
    struct Node* next;
}node;
node* L1, * L2, * L3, * L4;

node* Linklist_read(node* L, int m, int n)
{
    // 对链表创建单个节点，读入多项式单项
    L->next = (node*)malloc(sizeof(node));
    L = L->next;
    L->next = NULL;
    L->data1 = m;
    L->data2 = n;
    return L;
}
node* Linklist_Func(node* L, node* p, node* q, int sign)
{
    int sumnum = 0;
    if (sign == 1) {
        sumnum = p->data1 + q->data1;
    }
    else {
        sumnum = p->data1 - q->data1;
    }
    if (sumnum == 0) return L;
    if (sign == 1) L3->data1 = L3->data1 + 1;
    else L4->data1 = L4->data1 + 1;
    L->next = (node*)malloc(sizeof(node));
    L = L->next;
    L->next = NULL;
    L->data1 = sumnum;
    L->data2 = p->data2;
    return L;
}
void Linklist_calculate()
{
    // 设定链表L1表示多项式加法的数据结果，L2表示减法的数据结果
    node* tempL1 = L1->next;
    node* tempL2 = L2->next;
    node* tempL3 = L3;
    node* tempL4 = L4;
    while (tempL1 && tempL2) {
        // 加法运算
        if (tempL1->data2 > tempL2->data2) {
            tempL3 = Linklist_read(tempL3, tempL1->data1, tempL1->data2);
            tempL4 = Linklist_read(tempL4, tempL1->data1, tempL1->data2);
            L3->data1 = L3->data1 + 1;
            L4->data1 = L4->data1 + 1;
            tempL1 = tempL1->next;
        }
        else if (tempL1->data2 < tempL2->data2) {
            tempL3 = Linklist_read(tempL3, tempL2->data1, tempL2->data2);
            tempL4 = Linklist_read(tempL4, -tempL2->data1, tempL2->data2);
            tempL2 = tempL2->next;
            L3->data1 = L3->data1 + 1;
            L4->data1 = L4->data1 + 1;
        }
        else {
            tempL3 = Linklist_Func(tempL3, tempL1, tempL2, 1);
            tempL4 = Linklist_Func(tempL4, tempL1, tempL2, 2);
            tempL1 = tempL1->next;
            tempL2 = tempL2->next;
        }
    }
    while (tempL1) {
        tempL3 = Linklist_read(tempL3, tempL1->data1, tempL1->data2);
        tempL4 = Linklist_read(tempL4, tempL1->data1, tempL1->data2);
        tempL1 = tempL1->next;
        L3->data1 = L3->data1 + 1;
        L4->data1 = L4->data1 + 1;
    }
    while (tempL2) {
        tempL3 = Linklist_read(tempL3, tempL2->data1, tempL2->data2);
        tempL4 = Linklist_read(tempL4, -tempL2->data1, tempL2->data2);
        tempL2 = tempL2->next;
        L3->data1 = L3->data1 + 1;
        L4->data1 = L4->data1 + 1;
    }
    return;
}
void Linklist_print_free(node* L)
{
    int num = L->data1;
    L = L->next;
    cout << num << " ";
    while (L != NULL) {
        cout << L->data1 << " " << L->data2 << " ";
        node* q = L;
        L = L->next;
        if (q != NULL) free(q); // 同时释放结点
    }
    cout << endl;
    return;
}
int main()
{
    int n = 0;
    cin >> n;
    L1 = (node*)malloc(sizeof(node));
    L2 = (node*)malloc(sizeof(node));
    L3 = (node*)malloc(sizeof(node));
    L4 = (node*)malloc(sizeof(node));
    L3->data1 = 0;
    L4->data1 = 0;
    node* tempL = L1;
    for (int i = 0; i < n; i++) {
        int temp1 = 0, temp2 = 0;
        cin >> temp1 >> temp2;
        tempL = Linklist_read(tempL, temp1, temp2);
    }
    L1->data1 = n;     //记录多项式非零项个数即链表长度
    L1->data2 = 0;
    tempL = L2;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp1 = 0, temp2 = 0;
        cin >> temp1 >> temp2;
        tempL = Linklist_read(tempL, temp1, temp2);
    }
    L2->data1 = n;
    L2->data2 = 0;
    Linklist_calculate();
    Linklist_print_free(L3);
    Linklist_print_free(L4);
    return 0;
}
