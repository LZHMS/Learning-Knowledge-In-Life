#include<iostream>
#define Max_num 200
int AM[Max_num][Max_num],BM[Max_num][Max_num];
int main()
{
    int m = 0, n = 0;
    scanf("%d%d",&m,&n);
    int Anum = 0, Bnum = 0;
    int A[10*Max_num],B[10*Max_num],C[10*Max_num];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&AM[i][j]);
            if(AM[i][j]) Anum++;
        }
    }
    for(int i=0;i<Anum;i++)
        scanf("%d",&A[i]);
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&BM[i][j]);
            if(BM[i][j]) Bnum++;
        }
    }
    for(int i=0;i<Bnum;i++)
        scanf("%d",&B[i]);
    int a = 0, b = 0, c = 0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int temp = AM[i][j]*A[a]+BM[i][j]*B[b];
            if(AM[i][j]) a++;
            AM[i][j] = temp == 0?0:1;
            if(temp) C[c++] = temp;
            if(BM[i][j]) b++;
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%d ",AM[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<c;i++){
        printf("%d ",C[i]);
    }
    return 0;
}
