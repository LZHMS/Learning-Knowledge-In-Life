#include<iostream>
#include<cstdlib>

using namespace std;
//-----------------------自定义链表模板类--------------
typedef bool Status;
typedef int TElemType;


// 抽象数据类型定义
template<class TElemType>
struct SqNode {
    TElemType data;
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
        head->data = 0;   // 记录链表中元素数
        ptr = head;
        head->next = NULL;
        head->pre = NULL;
        return true;
    }
    Status Addelems(TElemType e)
    {
        struct SqNode<TElemType>* stemp;
        if (!(stemp = (struct SqNode<TElemType>*)malloc(sizeof(struct SqNode<TElemType>)))) return false;
        ptr->next = stemp;
        stemp->data = e;
        stemp->pre = ptr;
        stemp->next = NULL;
        ptr = ptr->next;

        head->data++;      // 栈元素计数
        return true;
    }
    Status Remove(struct SqNode<TElemType>*& ptemp)
    {
        // 删除temp指向节点
        struct SqNode<TElemType>* temp = ptemp;
        ptemp = ptemp->next;
        if (!temp) return false;
        temp->pre->next = temp->next;
        if (temp->next != NULL) temp->next->pre = temp->pre;
        free(temp);

        head->data--;
        return true;
    }
    Status Free()
    {
        while (head) {
            ptr = head;
            head = head->next;
            free(ptr);
        }
        head = NULL;
        ptr = NULL;
        return true;
    }
    Status Print()
    {
        struct SqNode<TElemType>* temp = head->next;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        return true;
    }
    int Size()
    {
        return head->data;
    }
};

int main()
{
    Link_list<int> lst; lst.Init();
    TElemType num = 0;

    cin >> num;
    for (int i = 1; i <= num; i++) {
        if (i % 2 == 1||num <= 3) lst.Addelems(i);
    }
    
    struct SqNode<TElemType>* ptemp = lst.head;
    while (lst.Size() > 3) {
        int tempsize = lst.Size();
        ptemp = lst.head->next->next->next;
        for (int i = 3; i <= tempsize; i += 3) {
            if (i % 3 == 0) {
                lst.Remove(ptemp);
                if(ptemp && ptemp->next) ptemp = ptemp->next->next;
            }
        }
        if (lst.Size() <= 3) break;
        tempsize = lst.Size();
        ptemp = lst.head->next->next;
        for (int i = 2; i <= tempsize; i += 2) {
            if (i % 2 == 0) {
                lst.Remove(ptemp);
                if(ptemp) ptemp = ptemp->next;
            }
        }
    }
    lst.Print();
    lst.Free();
    return 0;
}
