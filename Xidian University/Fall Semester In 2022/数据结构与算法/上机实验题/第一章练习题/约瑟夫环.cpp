#include<iostream>
#include<cstdlib>
using namespace std;
typedef struct Node{
    int number;
    int code;
    struct Node* next;
}node;
node *L;
node* Linklist_read(node* p, int num, int sign)
{
    int temp = 0;
    cin >> temp;
    node *tempL;
    tempL = (node*)malloc(sizeof(node));
    p->next = tempL;
    tempL->number = num;
    tempL->code = temp;
    if(num == sign) tempL->next = L;
    else tempL->next = NULL;
    return p->next;
}
node* Linklist_Out(node* p)
{
    //只有一个节点时进行特判
    if(p == p->next) return NULL;
    node* q = p->next;
    p->next = p->next->next;
    if(q) free(q);
    return p;
}

int main()
{
    int m = 0, n = 0, temp = 0;
    cin >> n >> m >> temp;
    L = (node*)malloc(sizeof(node));
    L->number = 1;
    L->code = temp;
    if(n == 1) L->next = L;
    else L->next = NULL; 
    node* tempL = L;
    for(int i=1;i<n;i++){
        tempL = Linklist_read(tempL, i+1, n);
    }  // 执行完毕后tempL指向最后一个结点
    while(tempL){
        // 移动到出圈人的上一结点
        for(int i=1;i<m;i++){
            tempL = tempL->next;
        }
        m = tempL->next->code;
        cout << tempL->next->number << ' ';
        tempL = Linklist_Out(tempL);
    }
    return 0;
}