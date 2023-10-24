#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;
typedef struct student {
    int num;
    char name[12];
    char axs;
    struct student* next;
}Stu;
Stu* head;
bool Stu_read(Stu* &p)
{
    Stu* temp = (Stu*)malloc(sizeof(Stu));
    if (!temp) return false;
    cin >> temp->name;
    if (temp->name[0] == '#') {
        free(temp);
        return false;
    }
    cin >> temp->num >> temp->axs;
    p->next = temp;
    temp->next = NULL;
    p = p->next;
    head->num++;
    return true;
}
bool Search_stu(int m)
{
    Stu* p = head;
    while (p->next) {
        if (p->next->num == m) {
            Stu* q = p->next;
            p->next = p->next->next;
            free(q);
            return true;
        }
        p = p->next;
    }
    return false;
}
void Stu_print()
{
    Stu* p = head->next;
    while (p) {
        cout << p->name << " " << p->num << " " << p->axs << endl;
        p = p->next;
    }
    return;
}
int main()
{
    head = (Stu*)malloc(sizeof(Stu));
    head->next = NULL;
    head->num = 0;
    Stu* temp = head;
    while (Stu_read(temp) == true);
    int Out_stu = 0;
    cin >> Out_stu;
    if (Search_stu(Out_stu)) Stu_print();
    else cout << "No" << endl;
    return 0;
}
