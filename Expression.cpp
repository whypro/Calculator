// Expression.cpp: implementation of the CExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Calculator.h"
#include "Expression.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExpression::CExpression()
{

}

CExpression::~CExpression()
{

}

// 修正原始表达式以及合法性判断
int CExpression::fix(const string input, string &infix) {
        int i;
        int braket = 0;
        
        // 过滤空格
        for (i = 0; i < input.length(); i++) {
                if (input[i] != ' ') {
                        infix += input[i];
                }
        }

        // 判断是否为空
        if (infix == "") {
                return 1;               // 1: 输入为空
        }

        // 判断是否包含非法字符
        for (i = 0; i < infix.length(); i++) {
                if ((infix[i] > '9' || infix[i] < '0') && 
                    infix[i] != '+' && infix[i] != '-' &&
                    infix[i] != '*' && infix[i] != '/' &&
                    infix[i] != '(' && infix[i] != ')' &&
                    infix[i] != '.') {
                        return 2;       // 2: 包含非法字符
                }
        }

        // 括号计数
        for (i = 0; i <infix.length(); i++) {
                if (infix[i] == '(') {
                        braket ++;
                }
                if (infix[i] == ')') {
                        braket --;
                }
        }
        // 判断括号是否配对
        if (braket) {
                return 3;               // 3: 括号不配对
        }

        // 判断操作符是否合法
        // 此处逻辑需要优化
        // 表达式首字符不能是'+' '*' '/'
        if (infix[0] == '+' || 
            infix[0] == '*' || infix[0] == '/') {
                return 4;
        }
        for (i = 0; i <infix.length(); i++) {
                // 1. '+' '-' '*' '/' 后必须是'(' '.' '-' 或者数字
                if ((infix[i] == '+' || infix[i] == '-' ||
                    infix[i] == '*' || infix[i] == '/') &&
                    (infix[i + 1] != '(' && infix[i + 1] != '.' && infix[i + 1] != '-' &&
                    (infix[i + 1] > '9' || infix[i + 1] < '0'))) {
                        return 4;       // 4: 操作符不合法
                }
                // 2. '(' 后必须是 '('或 '.' '-' 或数字
                else if (infix[i] == '(' && 
                         infix[i + 1] != '(' && infix[i + 1] != '.' && infix[i + 1] != '-' &&
                         (infix[i + 1] > '9' || infix[i + 1] < '0' ) ) {
                        return 4;       // 4: 操作符不合法
                }
                // 3. ')' 后必须是 ')' '+' '-' '*' '/' '\0'
                else if (infix[i] == ')' && 
                    infix[i + 1] != '+' && infix[i + 1] != '-' && 
                    infix[i + 1] != '*' && infix[i + 1] != '/' &&
                    infix[i + 1] != ')' && infix[i + 1] != '\0') {
                        return 4;       // 4: 操作符不合法
                }
                // 4. '.' 后必须是数字
                else if (infix[i] == '.' && 
                    (infix[i + 1] > '9' || infix[i + 1] < '0')) {
                        return 4;       // 4: 操作符不合法
                }
                // 5. 数字后不能是 '('
                else if ((infix[i] <= '9' && infix[i] >= '0') &&
                          infix[i + 1] == '(') {
                        return 4;       // 4: 操作符不合法
                }
        }

        // 判断小数点的正确性，保证数字只有一个小数点
        bool hasDot = false;
        for (i = 0; i <infix.length(); i++) {
                if (infix[i] == '.') {
                        if (hasDot == true) {
                                return 4;        // 4: 操作符不合法
                        }
                        else {
                                hasDot = true;
                        }
                }
                else if (infix[i] > '9' || infix[i] < '0') {
                        hasDot = false;
                }
        }

        // 处理负数，例如将 -2 转化成 (0-1)*2
        for (i = 0; i <infix.length(); i++) {
                if ((i == 0 && infix[i] == '-') || 
                    ((infix[i] == '+' || infix[i] == '-' || 
                     infix[i] == '*' || infix[i] == '/' ||
                     infix[i] == '(') && infix[i + 1] == '-')) {
                        // 负号在表达式首部
                        if (i == 0 && infix[i] == '-') {   
                                infix.replace(i, 1, "(0-1)*");
                                i += 4;
                        }
                        // 负号在表达式中间
                        else {
                                infix.replace(i + 1, 1, "(0-1)*");
                                i += 5;
                        }
                }
        }

        return 0;                       // 0: 合法
}

// 转换表达式
void CExpression::convert(const string infix, string &postfix) {
        char ch;
        int i;
        stack<char> stk;
        for (i = 0; i < infix.length(); ) {
                ch = infix[i];
                switch(ch) {

                // 左括号直接入栈
                case '(' :
                        stk.push(ch);
                        i++;
                        break;
                // 右括号先退栈，直到遇见一个左括号
                case ')' :
                        while (stk.top() != '(') {
                                postfix += stk.top();
                                stk.pop();
                                
                        }
                        stk.pop();
                        i++;
                        break;
                // 如果上一个运算符不是左括号也不是栈顶，则先退栈再入栈
                case '+' :
                case '-' :
                        while (!stk.empty() && stk.top() != '(') {
                                postfix += stk.top();
                                stk.pop();
                        }
                        stk.push(ch);
                        i++;
                        break;

                // 如果前一个运算符为*或/，则先退栈,再入栈,否则直接入栈
                case '*' :
                case '/' :
                        while (!stk.empty() && 
                               (stk.top() == '*' || 
                                stk.top() == '/')) {
                                postfix += stk.top();
                                stk.pop();
                        }
                        stk.push(ch);
                        i++;
                        break;
                // 如果是数字则直接进入后缀表达式串
                default :
                        while ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.') {
                                postfix += infix[i];
                                i++;
                        }
                        postfix += '#';
                        break;
                }
        }
        while (!stk.empty()) {
                postfix += stk.top();
                stk.pop();
        }
}

// 计算表达式
double CExpression::calculate(const string postfix) {
        char ch;
        double num_a, num_b, num_c;
        int i;
        stack<double> stk;
        for (i = 0; i < postfix.length(); i++) {
                ch = postfix[i];
                switch (ch) {
                // 两数相加
                case '+' :
                        num_a = stk.top();
                        stk.pop();
                        num_b = stk.top();
                        stk.pop();
                        num_c = num_b + num_a;
                        stk.push(num_c); 
                        break;
                // 两数相减
                case '-' :
                        num_a = stk.top();
                        stk.pop();
                        num_b = stk.top();
                        stk.pop();
                        num_c = num_b - num_a;
                        stk.push(num_c); 
                        break;
                // 两数相乘
                case '*' :
                        num_a = stk.top();
                        stk.pop();
                        num_b = stk.top();
                        stk.pop();
                        num_c = num_b * num_a;
                        stk.push(num_c);  
                        break;
                // 两数相除
                case '/' :
                        num_a = stk.top();
                        stk.pop();
                        num_b = stk.top();
                        stk.pop();
                        // 判断除数是否为零
                        if (num_a) {
                                num_c = num_b / num_a;
                                stk.push(num_c); 
                                break;
                        }
                        else {
                                // 除数为 0 
                                return 0;
                        }
                default:
                        num_a = 0;
                        num_b = 0;
                        int j;
                        // 数字
                        // 此处算法需要优化
                        while ((postfix[i] >= '0' && postfix[i] <= '9') || postfix[i] == '.') {
                                j = 10;
                                if (postfix[i] != '.') {        // 整数部分
                                        num_a = 10 * num_a + (postfix[i] - '0');
                                        
                                }
                                else {                          // 小数部分
                                        i++;
                                        while (postfix[i] != '#') {
                                                num_b += double (postfix[i] - '0') / j;
                                                i++;
                                                j *= 10;
                                        }
                                        break;
                                }
                                i++;        
                        }
                        num_c = num_a + num_b;                  // 结果 = 整数部分 + 小数部分
                        stk.push(num_c);
                        break;
                }
        }
        return stk.top();
}


