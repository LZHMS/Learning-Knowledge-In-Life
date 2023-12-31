#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<stack>
using namespace std;
#define N_OPTR 9 //运算符总数
#define Opr 100  //表达式最大长度
typedef enum {ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE}Operator; //运算符集合
 //加、减、乘、除、乘方、阶乘、左括号、右括号、起始符不终止符

const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶]
/* |-------------- 当前运算符 --------------| */
/* -------- + - * / ^ ! ( ) \0     --------------------*/
/* -- + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* | - */  '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* 栈 * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* 顶 / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* 运 ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
/* 算 ! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
/* 符 ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
/* | ) */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/* -- \0*/ '<', '<', '<', '<', '<', '<', '<', ' ', '='
};
void readNumber(char* &p, stack<float> &stk);  // 操作数入栈
Operator optr2rank(char op);  //由运算符转译出编号
char orderBetween(char op1, char op2); //比较两个运算符之间的优先级
void append(char* &rpn, float opnd);    //将操作数接至RPN末尾
void append(char* &rpn, char optr); //将运算符接至RPN末尾
int calcu(char op, float data);    // 一元运算
float calcu(float opd1, char op, float opd2); // 二元运算
bool evaluate(char* S, char* &RPN, float &result);//对表达式S求值，并转换为逆波兰式RPN
int main()
{
    float ans = 0;
    char* RPN = NULL;
    char S[Opr] = {0};
    cout << "Input Arithmetic Expression:\n";
    cin >> S;
    
    if(evaluate(S, RPN, ans))
        cout << "Ans = " << ans << endl;
    else
        cout << "Error!" << endl;
    cout << "Reverse Polish Notation:\n";
    cout << RPN;
    return 0;
}
void readNumber(char* &p, stack<float> &stk){ 
    //将起始于p的子串解析为数值，并存入操作数栈
    stk.push((float)(*p - '0')); //当前数位对应的数值进栈
    // 处理多位整数情况
    while (isdigit(*(++p))){
        float temp = stk.top();
        stk.pop();
        stk.push(temp * 10 + (*p - '0'));   //弹出原操作数，转换新数值重新入栈
    }
    if ('.' != *p) return ; //此后非小数点，则意味着当前操作数解析完成

    //处理小数部分
    float fraction = 1; //否则，意味着还有小数部分 
    while (isdigit(*(++p))){ //逐位加入
        float temp = stk.top();
        stk.pop();
        stk.push(temp + (*p - '0')*(fraction /= 10)); //计算小数部分
    }
    return ;
}
Operator optr2rank(char op) { 
    //由运算符转译出编号
    switch (op) {
        case '+' : return ADD; //加
        case '-' : return SUB; //减
        case '*' : return MUL; //乘
        case '/' : return DIV; //除
        case '^' : return POW; //乘斱
        case '!' : return FAC; //阶乘
        case '(' : return L_P; //左括号
        case ')' : return R_P; //右括号
        case '\0': return EOE; //起始符与终止符
        default : exit(-1); //未知运算符
    }
}
char orderBetween(char op1, char op2) //比较两个运算符之间的优先级
{ 
    return pri[optr2rank(op1)][optr2rank(op2)]; 
}

void append(char* &rpn, float opnd) {    //将操作数接至RPN末尾
    char buf[64] = {0};
    //判断是否是整数进行压栈
    if (opnd != (float)(int)opnd) sprintf(buf, "%.2f \0", opnd); //浮点格式
    else sprintf(buf, "%d \0", (int)opnd); //整数格式

    if(rpn==NULL){
        rpn = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
        strcpy(rpn,buf);
    }
    else{
        int n = strlen(rpn); // RPN当前长度（以'\0'结尾，长度n + 1）
        rpn = (char*)realloc(rpn, sizeof(char) * (n + strlen(buf) + 1)); //扩展空间
        strcat(rpn, buf); //RPN加长
    }
    return ;
}

void append(char* &rpn, char optr) { //将运算符接至RPN末尾
    if(rpn == NULL){
        rpn = (char*)malloc(sizeof(char) * (3));
        sprintf(rpn, "%c ", optr); rpn[2] = '\0'; //接入指定的运算符
    }
    else{
        int n = strlen(rpn); //RPN当前长度（以'\0'结尾，长度n + 1）
        rpn = (char*) realloc(rpn, sizeof(char) * (n + 3)); //扩展空间
        sprintf(rpn + n, "%c ", optr); rpn[n + 2] = '\0'; //接入指定的运算符
    }
    return ;
}
int calcu(char op, float data)
{
    // 一元计算——阶乘
    if((int)data == 0) return 0;
    int sum_data = 1;
    for(int i=1;i<=(int)data;i++) sum_data *= i;
    return sum_data;
}
float calcu(float opd1, char op, float opd2)
{
    //函数重载进行二元运算
    switch(op){
        case '+': return opd1 + opd2;
                  break;
        case '-': return opd1 - opd2;
                  break;
        case '*': return opd1 * opd2;
                  break;
        case '/': return opd1 / opd2;
                  break;
        case '^': return pow(opd1, opd2);
                  break;
        default:  return 0;
                  break;
    }
}
bool evaluate(char* S, char* &RPN, float &result) { 
    //对表达式S求值，并转换为逆波兰式RPN
    stack<float> opnd; stack<char> optr; //设置运算数栈、运算符栈
    optr.push('\0'); //尾哨兵'\0'也作为头哨兵首先入栈，主要为了判断计算结束退出
    while (!optr.empty()) { //在运算符栈非空之前，逐个处理表达式中各字符
        if (isdigit(*S)) { //若当前字符为操作数，则
            readNumber(S, opnd);   // 读入操作数
            append(RPN, opnd.top()); //并将其接至RPN末尾
        } else //若当前字符为运算符，则
            switch(orderBetween(optr.top(), *S)) { 
                //视其与栈顶运算符之间优先级高低分别处理
                case '<': //栈顶运算符优先级更低时
                    optr.push(*S++); //计算推迟，当前运算符入栈
                    break;
                case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
                    optr.pop(); S++; //脱括号并接收下一个字符
                    break;
                case '>': { //栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
                    char op = optr.top(); optr.pop(); 
                    append(RPN, op); //栈顶运算符出栈并续接至RPN末尾
                    if ('!' == op) { //若属于一元运算符(阶乘)
                        float pOpnd = opnd.top(); opnd.pop();  // 取一个操作数
                        opnd.push(calcu(op, pOpnd)); //实施一元计算，结果入栈
                    } else { //对于其它（二元）运算符
                        float pOpnd2 = opnd.top(); opnd.pop();  // 栈中后运算数
                        float pOpnd1 = opnd.top(); opnd.pop();  // 栈中前运算数
                        opnd.push(calcu(pOpnd1, op, pOpnd2)); //实施二元计算，结果入栈
                    }
                    break;
                    }
                default:
                    return false; //语法错误，直接退出
            }//switch
    }//while
    result = opnd.top(); opnd.pop();
    return true; //弹出并返回最后的计算结果
}