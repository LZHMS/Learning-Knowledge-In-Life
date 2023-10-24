#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

typedef struct StackNode {
    int x; int y; int dre;   //坐标和方向
    struct StackNode* next;
    struct StackNode* pre;
}SN;
class stack {
public:
    int Cur_x; int Cur_y; int Cur_dre;   // 栈顶决策
    void push(int x_elem, int y_elem, int dre_elem)
    {
        if (head == NULL) {
            base = head = (SN*)malloc(sizeof(SN));
            head->pre = NULL;
        }
        else {
            head->next = (SN*)malloc(sizeof(SN));
            head->next->pre = head;
            head = head->next;
        }
        head->x = Cur_x = x_elem;
        head->y = Cur_y = y_elem;
        head->dre = Cur_dre = dre_elem;
        head->next = NULL;
        Stack_Length++;
        return;
    }
    void pop()
    {
        if (head == NULL) exit(-1);
        else {
            SN* temp = head;
            head = head->pre;
            if (head) head->next = NULL;
            free(temp);
        }
        if (head == NULL) {
            base = NULL;
            Stack_Length--;
            return;
        }
        Cur_x = head->x;
        Cur_y = head->y;
        Cur_dre = head->dre;
        Stack_Length--;
        return;
    }
    bool empty()
    {
        if (head == NULL) return true;
        else return false;
    }
    int size()
    {
        return Stack_Length;
    }
    void print()
    {
        SN* mp = base;
        while (mp != head) {
            printf("(%d,%d,%d),", mp->x, mp->y, mp->dre);
            mp = mp->next;
        }
        printf("(%d,%d,%d)\n", mp->x, mp->y, mp->dre);
        return;
    }
private:
    SN* head = NULL, * base = NULL;
    int Stack_Length;
};

class Maze
{
public:
    int curstep = 1;
    int pos[3] = { 0 };   //当前位置
    int init(int row, int col)
    {
        cin >> Sp[0] >> Sp[1];
        cin >> Ep[0] >> Ep[1];
        pos[0] = Sp[0];
        pos[1] = Sp[1];
        pos[2] = 1;
        for (int i = 0; i <= row + 1; i++) {
            for (int j = 0; j <= col + 1; j++) {
                if (i == 0 || j == 0 || i == row + 1 || j == col + 1) Map[i][j] = 1;
                else cin >> Map[i][j];
            }
        }
        if (Map[Sp[0]][Sp[1]] == 1) return 2;
        Map[pos[0]][pos[1]] = curstep;
        if (Sp[0] == Ep[0] && Sp[1] == Ep[1]) return 1;
        else return 3;
    }
    bool premove()   //预判断即试探
    {
        if (Map[pos[0] + dx[pos[2] - 1]][pos[1] + dy[pos[2] - 1]] == 0) return true;
        else return false;
    }
    bool move()   //前进
    {
        pos[0] = pos[0] + dx[pos[2]-1];
        pos[1] = pos[1] + dy[pos[2] - 1];
        pos[2] = 1;
        Map[pos[0]][pos[1]] = ++curstep;
        if (pos[0] == Ep[0] && pos[1] == Ep[1]) return true;
        else return false;
    }
    void upgrade(int x, int y,int dre)   //后退一步
    {
        Map[pos[0]][pos[1]] = 1;   //死胡同标记
        pos[0] = x;
        pos[1] = y;
        pos[2] = dre + 1;
        curstep--;
        return;
    }
    void print(int row, int col)
    {
        for (int i = 0; i <= row+1; i++) {
            for (int j = 0; j <= col+1; j++) {
                cout << Map[i][j] << " ";
            }
            cout << endl;
        }
        return;
    }
private:
    int Map[102][102];  //迷宫地图
    int dx[4] = { 0,1,0,-1 };
    int dy[4] = { 1,0,-1,0 };
    int Sp[2];   //起点
    int Ep[2];   //终点
};
int main()
{
    int row = 0, col = 0;
    cin >> row >> col;
    class Maze maze;
    class stack path;
    int sign = maze.init(row, col);
    if ( sign == 1){   //初始化生成地图
        path.push(maze.pos[0], maze.pos[1], maze.pos[2]);   // 入栈
    }
    else if(sign == 3){
        int first = 1;
        do {
            if (maze.pos[2] <= 4 && maze.premove()) {    // 判断是否能走
                path.push(maze.pos[0], maze.pos[1], maze.pos[2]);   // 入栈
                if (maze.move()) {
                    path.push(maze.pos[0], maze.pos[1], maze.pos[2]);   // 入栈
                    break;     // 能走
                }
                first = 0;
            }
            else {
                if (maze.pos[2] < 4) {
                    maze.pos[2]++;
                }
                else {
                    if (!path.empty()) {
                        maze.upgrade(path.Cur_x, path.Cur_y, path.Cur_dre);
                        path.pop();
                    }
                }
            }
        } while (!path.empty() || first);
    }
    if (path.empty()) cout << "no\n";
    else {
        path.print();
        //maze.print(row, col);
    }
    return 0;
}
