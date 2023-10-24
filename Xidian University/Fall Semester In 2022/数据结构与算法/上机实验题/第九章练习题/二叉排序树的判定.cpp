#include<iostream>
#define Max_num 100003
int val[Max_num],lchild[Max_num],rchild[Max_num];

int BiTreeCheck(int root)
{
    int flag = 0;
    if(root){
        if(lchild[root]) flag = val[root] - val[lchild[root]] > 0 ? 0:1;
        if(rchild[root]) flag = val[rchild[root]] - val[root] > 0 ? 0:1;
        flag += BiTreeCheck(lchild[root]);
        flag += BiTreeCheck(rchild[root]);
    }
    return flag;
}
int main()
{
    int n = 0, root = 0;
    scanf("%d%d",&n,&root);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&val[i],&lchild[i],&rchild[i]);
    int flag = 0;
    flag = BiTreeCheck(root);
    if(flag) printf("false\n");
    else printf("true\n");
    return 0;
}