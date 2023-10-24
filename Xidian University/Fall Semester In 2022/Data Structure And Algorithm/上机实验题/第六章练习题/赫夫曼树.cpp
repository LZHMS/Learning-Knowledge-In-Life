//-----------赫夫曼树的带权路径长度--------------//

#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
//------------赫夫曼树和赫夫曼编码的存储表示-----------//
typedef struct {  // 赫夫曼树节点
    char sign;   // 待编码字符
    int  weight;     //节点值
    unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;
typedef struct{    // 动态分配数组存储赫夫曼编码表
    char **NodesCode;  // 字符对应编码
    int *sign;    // 字符带权路径长度
}HuffmanCode;


void Select(HuffmanTree HT, int p, int& s1, int& s2);
void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int* w, char *s, int n);
void HuffmanCodePrint(HuffmanCode HC, int n);
int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int n;
    cin >> n;
    int *w = new int[n]{};
    char *s = new char[n]{};
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    HuffmanCoding(HT, HC, w, s, n);
    HuffmanCodePrint(HC, n);
    return 0;
}
void Select(HuffmanTree HT, int p, int& s1, int& s2)
{
    s1 = s2 = 0;
    for (int i = 1; i <= p; i++) {
        if (HT[i].parent) continue;
        else {
            if (!s1) s1 = i;     // 保证先有节点
            else if (!s2) {
                if (HT[s1].weight > HT[i].weight) {
                    s2 = s1;
                    s1 = i;
                }
                else s2 = i;
            }
            else {
                if (HT[i].weight < HT[s1].weight) {
                    s2 = s1;
                    s1 = i;
                }
                else if (HT[i].weight < HT[s2].weight) {
                    s2 = i;
                }
            }
        }
    }
    return;
}

void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int* w, char *s, int n)
{
    // w存放n个字符的权值，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC

    if (n <= 1) return;
    int m = 2 * n - 1;   // 赫夫曼树的节点数
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); // 0号单元未用
    HuffmanTree p = HT;
    int i = 1;
    for (p=HT+1; i <= n; ++i, ++p, ++w, ++s) *p = {*s,*w,0,0,0 };   // 对赫夫曼树叶子节点进行赋值
    for (; i <= m; i++, p++) *p = {0,0,0,0,0 };    // 其他节点初始化操作
    for (i = n + 1; i <= m; i++) {       // 建赫夫曼树
        //在HT[1..i-1]选择parent为0且weight最小的两个节点，其序号分别为s1和s2
        int s1 = 0, s2 = 0;
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = i; HT[s2].parent = i;   // 更新构造
        HT[i].lchild = s1; HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    //--------从叶子到根逆向求每个字符的赫夫曼编码-------------//
    HC.NodesCode = (char**)malloc((n + 1) * sizeof(char*)); // 分配n个字符编码的头指针向量
    HC.sign = (int*)malloc((n+1) * sizeof(int));
    char* cd = (char*)malloc(n * sizeof(char));    // 分配n个字符求编码的工作空间，最长编码是n-1
    cd[n - 1] = '\0';     // 编码结束符
    for (i = 1; i <= n; ++i) {   // 遍历叶子节点（前n个位置）
        int start = n - 1;  // 编码结束符位置
        for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)   // 从叶子到根逆向求编码
            if (HT[f].lchild == c) cd[--start] = '0';   // 左孩子定义为0
            else cd[--start] = '1';    // 右孩子定义为1
        HC.NodesCode[i] = (char*)malloc((n - start) * sizeof(char));    // 为第i个字符编码分配空间
        strcpy(HC.NodesCode[i], &cd[start]);
        HC.sign[i] = HT[i].weight * strlen(HC.NodesCode[i]);
    }
    free(cd);
    return;
}
void HuffmanCodePrint(HuffmanCode HC, int n)
{
    int mysum = 0;
    for (int i = 1; i <= n; i++) {
        mysum += HC.sign[i];
    }
    cout << mysum << endl;
    return;
}