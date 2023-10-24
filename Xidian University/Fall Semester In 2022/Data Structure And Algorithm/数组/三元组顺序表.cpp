#include<iostream>
using namespace std;
//---------------稀疏矩阵的三元组顺序表存储表示-------------
#define MAXSIZE 500
// 抽象数据类型定义
typedef int ElemType;
typedef bool Status;

typedef struct {
    int i, j;
    ElemType value;
}Triple;

typedef struct {
    Triple data[MAXSIZE + 1];
    int rows, cols, nums;  // 行列和非零元数 
}TSMatrix;


Status TransposeMatrix(TSMatrix M, TSMatrix& T);
Status FastTransposeMatrix(TSMatrix M, TSMatrix& FT);
Status TSMatrixRead(TSMatrix& M);
Status TSMatrixPrint(TSMatrix M);
int main()
{
    TSMatrix M, T, FT;
    TSMatrixRead(M);
    cout << "Before Transpose Matrix:\n";
    TSMatrixPrint(M);
    cout << "After Transpose Matrix:\n";
    TransposeMatrix(M, T);
    TSMatrixPrint(T);
    cout << "After FastTranspose Matrix:\n";
    FastTransposeMatrix(M, FT);
    TSMatrixPrint(FT);
    return 0;
}

Status TransposeMatrix(TSMatrix M, TSMatrix& T)
{
    // 采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
    T.rows = M.cols; T.cols = M.rows; T.nums = M.nums;
    if (T.nums) {    // 如果矩阵非空
        int q = 1;
        for (int col = 1; col <= M.cols; col++) {  // 指定循环M列序保证T矩阵的行主序
            for (int p = 1; p <= M.nums; p++) {  // 搜寻M中当前列元素
                // M又是按照行主序存储的，所以M每一列的列序即是T中每一行的行序
                if (M.data[p].j == col) {
                    T.data[q].i = M.data[p].j;
                    T.data[q].j = M.data[p].i;
                    T.data[q].value = M.data[p].value;
                    q++;
                }
            }
        }
    }
    return true;
}
Status FastTransposeMatrix(TSMatrix M, TSMatrix& FT)
{
    // 快速转置算法
    // 采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
    FT.rows = M.cols; FT.cols = M.rows; FT.nums = M.nums;
    if (FT.nums) {
        int* num = new int[M.cols + 1];
        int* cpot = new int[M.cols + 1];
        for (int col = 1; col <= M.cols; col++) num[col] = 0;
        for (int t = 1; t <= M.nums; ++t) ++num[M.data[t].j];
        cpot[1] = 1;
        for (int col = 2; col <= M.cols; col++) cpot[col] = cpot[col - 1] + num[col - 1];
        for (int p = 1; p <= M.nums; p++) {
            int col = M.data[p].j;
            int q = cpot[col];
            FT.data[q].i = M.data[p].j;
            FT.data[q].j = M.data[p].i;
            FT.data[q].value = M.data[p].value;
            cpot[col]++;
        }
        delete[] num;
    }
    return true;
}
Status TSMatrixRead(TSMatrix& M)
{
    cout << "Input Matrix rows, cols and nums:\n";
    cin >> M.rows >> M.cols >> M.nums;
    cout << "Input Matrix elements:\n";
    // 这里默认输入是行主序的
    for (int i = 1; i <= M.nums; i++) {
        cin >> M.data[i].i >> M.data[i].j >> M.data[i].value;
    }
    return true;
}
Status TSMatrixPrint(TSMatrix M)
{
    int cnt = 1;
    for (int i = 1; i <= M.rows; i++) {
        for (int j = 1; j <= M.cols; j++) {
            if (M.data[cnt].i == i && M.data[cnt].j == j)
                cout << M.data[cnt++].value << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
    return true;
}