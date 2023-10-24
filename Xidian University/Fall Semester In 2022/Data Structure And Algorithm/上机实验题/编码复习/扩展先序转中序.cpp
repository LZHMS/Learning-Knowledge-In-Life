#include<iostream>
#include<cstring>
const int Max_num = 103;
char pre[Max_num], in[Max_num], post[Max_num];
void TraverBiTree(int &i,int &j, int &k)
{
    char ch;
    std::cin >> ch;
    if(ch=='#') return;
    else{
        pre[i++]=ch;
        TraverBiTree(i,j,k);
        in[j++] = ch;   // 确保没有左子树或左子树已经处理完毕
        TraverBiTree(i,j,k);
        post[k++] = ch;  // 确保左右子树均已处理完毕
    }
}

int main()
{
    int i=0,j=0,k=0;
    TraverBiTree(i,j,k);
    pre[i]=in[j]=post[k]='\n';
    std::cout << pre << in << post;
    return 0;
}