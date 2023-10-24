#include<iostream>
#include<cstdlib>
using namespace std;
typedef struct Node{
    int data;
    struct Node* next;
}node;
node *L1,*L2;
node* Linklist_read(node* p)
{
    int num = 0;
    cin >> num;
    node *q = (node*)malloc(sizeof(node));
    p->next = q;
    q->data = num;
    q->next = NULL;
    return q;
}
void Linklist_Insert(node *p, node *q)
{
    node *temp = p->next;
    p->next = q->next;
    q->next = q->next->next;
    p->next->next = temp;
    return;
}
void Linklist_Delet(node* p)
{
    node *q = p->next;
    p->next = p->next->next;
    if(q) free(q);
    return ; 
}
void Linklist_Print(node *L)
{
    L = L->next;
    while(L != NULL){
        cout << L->data << ' ';
        node *q = L;
        L = L->next;
        if(q) free(q);
    }
    cout << endl;
    return ;
}
int main()
{
    L1 = (node*)malloc(sizeof(node));
    L2 = (node*)malloc(sizeof(node));
    node *tempL1 = L1,*tempL2 = L2;
    int m = 0, n = 0;
    cin >> m >> n;
    for(int i=0;i<m;i++){
        tempL1 = Linklist_read(tempL1);
    }
    for(int i=0;i<n;i++){
        tempL2 = Linklist_read(tempL2);
    }
    tempL1 = L1;tempL2 = L2;
    //对比查找
    while(tempL1->next!=NULL && tempL2->next!=NULL){
        if(tempL1->next->data < tempL2->next->data) tempL1 = tempL1->next;
        else if(tempL1->next->data > tempL2->next->data){
            Linklist_Insert(tempL1, tempL2);
            tempL1 = tempL1->next;
        }else Linklist_Delet(tempL2);
    }
    while(tempL2->next!=NULL){
        Linklist_Insert(tempL1, tempL2);
        tempL1 = tempL1->next;
    }
    Linklist_Print(L1);
    return 0;
}