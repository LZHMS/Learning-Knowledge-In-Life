#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<set>
using namespace std;
//-----------------------自定义链表模板类--------------
typedef bool Status;
typedef int TElemType;

set<int> myset;
// 抽象数据类型定义
template<class TElemType>
struct SqNode {
    TElemType data[3];  // 数据域(Address Key Next)
    struct SqNode* next, * pre;  // 双向链表
};

template<class TElemType>
class Link_list
{
public:
    struct SqNode<TElemType>* head, * ptr;   // 头指针与游标指针
    Status Init()
    {
        if (!(head = (struct SqNode<TElemType>*)malloc(sizeof(struct SqNode<TElemType>)))) return false;
        head->data[0] = 0;   // 记录链表中元素数
        ptr = head;
        head->next = NULL;
        head->pre = NULL;
        return true;
    }
    Status Addelems(TElemType e[])
    {
        struct SqNode<TElemType>* stemp;
        if (!(stemp = (struct SqNode<TElemType>*)malloc(sizeof(struct SqNode<TElemType>)))) return false;
        ptr->next = stemp;
        stemp->data[0] = e[0], stemp->data[1] = e[1], stemp->data[2] = e[2];
        stemp->pre = ptr;
        stemp->next = NULL;
        ptr = ptr->next; // 移动top指针始终位于栈顶

        head->data[0]++;      // 栈元素计数
        return true;
    }
    Status Remove(struct SqNode<TElemType>* temp)
    {
        if (!temp) return false;
        temp->pre->next = temp->next;
        if(temp->next != NULL) temp->next->pre = temp->pre;
        free(temp);

        head->data[0]--;
        return true;
    }

    Status Insert(struct SqNode<TElemType>* temp1, struct SqNode<TElemType>* temp2)
    {
        // 将temp2节点插入到temp1节点后
        temp2->next = temp1->next;
        if(temp1->next != NULL) temp1->next->pre = temp2;
        temp2->pre = temp1;
        temp1->next = temp2;
        return true;
    }
    Status Subnode(struct SqNode<TElemType>* temp)
    {
        // 提取temp指向的节点
        if (temp->next != NULL) {
            temp->next->pre = temp->pre;
        }
        temp->pre->next = temp->next;
        return true;
    }
    Status Print()
    {
        // 元素个数
        cout << head->data[0] << endl;
        struct SqNode<TElemType>* temp = head->next;
        while (temp) {
            cout << setw(5) << setfill('0') << temp->data[0] << " ";
            cout << temp->data[1] << " ";
            if (temp->data[2] == -1) cout << "-1" << endl;
            else  cout << setw(5) << setfill('0') << temp->data[2] << endl;
            temp = temp->next;
        }
        return true;
    }
    Status Free()
    {
        while (head) {
            ptr = head;
            head = head->next;
            free(ptr);
        }
        return true;
    }
};

Status LinkSort(TElemType sp, Link_list<int>& lst);
int main()
{
    Link_list<int> lst; lst.Init();
    TElemType sp = 0, num = 0;

    cin >> sp >> num;
    for (int i = 0; i < num; i++) {
        TElemType t[3];
        cin >> t[0] >> t[1] >> t[2];
        lst.Addelems(t);
    }
    LinkSort(sp, lst);
    lst.Print();
    lst.Free();
    return 0;
}

Status LinkSort(TElemType sp, Link_list<int>& lst)
{
    struct SqNode<TElemType>* stemp = lst.head->next, * curptr = lst.head;
    while (curptr->next) {
        if (curptr->data[2] == -1) break;
        while (stemp && stemp->data[0] != sp) {
            stemp = stemp->next;
        }
        if (!stemp) return false;
        else {
            lst.Subnode(stemp);
            if (myset.find(abs(stemp->data[1])) == myset.end()) {
                lst.Insert(curptr, stemp);    // 插入节点函数
                // 更新控制变量
                curptr = curptr->next;
                myset.insert(abs(curptr->data[1]));
            }
            else {
                curptr->data[2] = stemp->data[2];
                lst.Remove(stemp);
            }
            sp = curptr->data[2];
            stemp = curptr->next;
        }
    }
    return true;
}