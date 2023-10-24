#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct LNode{
	int  data;			    //数据域
	struct  LNode  *next;	//指针域
}LNode, *LinkList;

LinkList createList();             //创建含有头结点的单链表并返回头指针
void outputList(LinkList head);     //从表头开始依次输出单链表的元素
void reverseList(LinkList head);    //对单链表进行逆置处理

int main(){ 
	LinkList head = createList();
	outputList(head);
	reverseList(head);
	outputList(head);
	return 0;	 
}
void reverseList(LinkList head)
{
	LinkList ptr = head->next->next;
	head->next->next = NULL;
	while(ptr){
		LinkList pp = ptr->next;
		ptr->next = head->next;
		head->next = ptr;
		ptr = pp;
	}
	return ;
}