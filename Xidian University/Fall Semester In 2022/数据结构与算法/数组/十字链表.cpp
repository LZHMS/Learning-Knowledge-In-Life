#include<iostream>
#include<cstdlib>
using namespace std;
//-----------稀疏矩阵的十字链表表示法-----
/*------One Example:
Input Matrix rows, cols and nums:
4 3 12
Input Matrix elements:(x, y, value)
1 1 -1
1 3 2
2 3 -1
3 1 2
0 0 0           // End_Input_Sign
Input Matrix rows, cols and nums:
4 3 12
Input Matrix elements:(x, y, value)
2 1 3
2 3 1
3 2 4
4 1 2
0 0 0           // End_Input_Sign
After addiction:
Output Matrix:
-1 0 2
3 0 0
2 4 0
2 0 0
*/
// 抽象数据类型定义
typedef int ElemType;
typedef bool Status;

// 非零元结点结构
typedef struct OLNode {
    int i, j;      // 非零元的行列下标
    ElemType value;
    struct OLNode* right, * down;   // 非零元所在的行表和列表的后继元
}OLNode, * OLink;
// 十字链表结构
typedef struct {
    OLink* rhead, * chead; // row_head and column_head 头节点指针向量
    int cols, rows, nums;
}CrossList;

Status CreateCrossList(CrossList& M);
Status CrossListPrint(CrossList M);
Status MatrixAdd(CrossList& A, CrossList B);
Status DestroyCrossList(CrossList B);
int main()
{
    CrossList A, B;
    if (!CreateCrossList(A) || !CreateCrossList(B)) {
        cout << "Space allocate error!\n";
        return 0;
    }
    cout << "After addiction:\n";
    MatrixAdd(A, B);
    DestroyCrossList(B);
    CrossListPrint(A);
    return 0;
}

Status CreateCrossList(CrossList& M)
{
    cout << "Input Matrix rows, cols and nums:\n";
    cin >> M.rows >> M.cols >> M.nums;
    cout << "Input Matrix elements:(x, y, value)\n";

    // 为行表和列表指针申请空间，注意rhead,chead为指向指针的指针
    if (!(M.rhead = (OLink*)malloc(M.rows * sizeof(OLink))))
        return false;
    if (!(M.chead = (OLink*)malloc(M.cols * sizeof(OLink))))
        return false;

    // 初始化行列头指针向量
    for (int i = 0; i < M.rows; i++) M.rhead[i] = NULL;
    for (int i = 0; i < M.cols; i++) M.chead[i] = NULL;

    int temp_i, temp_j, temp_value;
    for (cin >> temp_i >> temp_j >> temp_value; temp_i != 0; cin >> temp_i >> temp_j >> temp_value) {
        // 假定输入以“0 0 0”结束
        OLink p;
        if (!(p = (OLink)malloc(sizeof(OLNode)))) return false; // 生成结点
        p->i = temp_i; p->j = temp_j;
        p->value = temp_value;

        /*-----------处理行插入情况------------*/
        if (M.rhead[temp_i - 1] == NULL || M.rhead[temp_i - 1]->j > temp_j) {  // 判断是否在首节点插入
            p->right = M.rhead[temp_i - 1];  // 这个地方一定保证了下面搜寻情况时最后一个结点的right域始终是NULL
            M.rhead[temp_i - 1] = p;
        }
        else {  // 否则需要遍历在行表中的插入位置
            // 最先就比较当前行的第二个元素q->right，这种情况无法探查首结点，也是为何需要特判首结点
            // 试探性的比较主要由单向链表结构决定的，只能巡查next，不能回溯
            OLink q = NULL;
            for (q = M.rhead[temp_i - 1]; (q->right) && q->right->j < temp_j; q = q->right);
            // 最终停在待插入节点位置的前一个位置上
            p->right = q->right; q->right = p;
        }

        /*-----------处理列插入情况------------*/
        // 列插入情况与行插入类似
        if (M.chead[temp_j - 1] == NULL || M.chead[temp_j - 1]->i > temp_i) {
            p->down = M.chead[temp_j - 1];
            M.chead[temp_j - 1] = p;
        }
        else {
            OLink q = NULL;
            for (q = M.chead[temp_j - 1]; (q->down) && q->down->i < temp_i; q = q->down);
            p->down = q->down; q->down = p;
        }
    }
    return true;
}

Status MatrixAdd(CrossList &A, CrossList B)
{
    // 实现十字链表表示的矩阵加法
    // 判断矩阵同型
    if (A.rows != B.rows || A.cols != B.cols) return false;

    // 构造矩阵A每一列的游标
    OLink colptr[100];
    for (int i = 0; i < A.cols; i++) colptr[i] = A.chead[i];
    for (int k = 0; k < A.rows; k++) {
        // pre指向矩阵A中pa前一节点
        OLink pa = A.rhead[k], pb = B.rhead[k], pre = NULL;

        while (pb) {    // 处理B矩阵每一行元素
            // A+B情况分类处理
            // <1> 直接复制B结点到A矩阵中(可以直接移动但考虑最后释放B矩阵的开销，不如直接复制再释放)
            if (pa == NULL || pa->j > pb->j) {
                // 复制结点
                OLink p = (OLink)malloc(sizeof(OLNode));
                if (!p) return false;
                p->i = pb->i; p->j = pb->j; p->value = pb->value;  //新节点值域更新

                // 行表更改——归属于哪一行
                if (pre == NULL) A.rhead[pb->i - 1] = p;
                else pre->right = p;
                p->right = pa;       // 新节点right域更新
                pre = p;

                //列表更改——归属于哪一列
                if (!A.chead[p->j - 1] || A.chead[p->j - 1]->i > p->i)
                {
                    p->down = A.chead[p->j - 1];  //新节点down域更新
                    A.chead[p->j - 1] = p;
                }
                else {
                    p->down = colptr[p->j - 1]->down;
                    colptr[p->j - 1]->down = p;
                }
                colptr[p->j - 1] = p;
                pb = pb->right;
            }
            else if (pa != NULL && pa->j < pb->j) {
                // <2> A矩阵同行元素位置在前时直接指针后移
                pre = pa;
                pa = pa->right;
            }
            else if (pa->j == pb->j) {
                // <3> 执行加法运算
                pa->value += pb->value;
                if (pa->value == 0) {   // 特判和为零时从矩阵A中删除节点
                    // 行表
                    if (pre == NULL) A.rhead[pa->i - 1] = pa->right;
                    else pre->right = pa->right;
                    OLink p = pa;
                    pa = pa->right;   // 后移继续下一运算
                    // 列表
                    if (A.chead[p->j - 1] == p) A.chead[p->j - 1] = colptr[p->j - 1] = p->down;
                    else colptr[p->j - 1]->down = p->down;
                    free(p);
                }
                pb = pb->right;
            }
        }
        for (int i = 0; i < A.cols; i++)
            if (colptr[i] && colptr[i]->down && colptr[i]->down->j < k + 2) colptr[i] = colptr[i]->down;
    }
    return true;
}

Status CrossListPrint(CrossList M)
{
    cout << "Output Matrix:\n";
    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            if (M.rhead[i] && M.rhead[i]->j == (j + 1)) {
                cout << M.rhead[i]->value << " ";
                M.rhead[i] = M.rhead[i]->right;
            }
            else cout << "0 ";
        }
        cout << "\n";
    }
    return true;
}
Status DestroyCrossList(CrossList B)
{
    for (int i = 0; i < B.rows; i++) {
        OLink p = B.rhead[i];
        while (p) {
            OLink q = p;
            p = p->right;
            free(q);
        }
    }
    free(B.rhead); free(B.chead);
    return true;
}