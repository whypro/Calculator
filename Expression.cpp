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

// ����ԭʼ���ʽ�Լ��Ϸ����ж�
int CExpression::fix(const string input, string &infix) {
        int i;
        int braket = 0;
        
        // ���˿ո�
        for (i = 0; i < input.length(); i++) {
                if (input[i] != ' ') {
                        infix += input[i];
                }
        }

        // �ж��Ƿ�Ϊ��
        if (infix == "") {
                return 1;               // 1: ����Ϊ��
        }

        // �ж��Ƿ�����Ƿ��ַ�
        for (i = 0; i < infix.length(); i++) {
                if ((infix[i] > '9' || infix[i] < '0') && 
                    infix[i] != '+' && infix[i] != '-' &&
                    infix[i] != '*' && infix[i] != '/' &&
                    infix[i] != '(' && infix[i] != ')' &&
                    infix[i] != '.') {
                        return 2;       // 2: �����Ƿ��ַ�
                }
        }

        // ���ż���
        for (i = 0; i <infix.length(); i++) {
                if (infix[i] == '(') {
                        braket ++;
                }
                if (infix[i] == ')') {
                        braket --;
                }
        }
        // �ж������Ƿ����
        if (braket) {
                return 3;               // 3: ���Ų����
        }

        // �жϲ������Ƿ�Ϸ�
        // �˴��߼���Ҫ�Ż�
        // ���ʽ���ַ�������'+' '*' '/'
        if (infix[0] == '+' || 
            infix[0] == '*' || infix[0] == '/') {
                return 4;
        }
        for (i = 0; i <infix.length(); i++) {
                // 1. '+' '-' '*' '/' �������'(' '.' '-' ��������
                if ((infix[i] == '+' || infix[i] == '-' ||
                    infix[i] == '*' || infix[i] == '/') &&
                    (infix[i + 1] != '(' && infix[i + 1] != '.' && infix[i + 1] != '-' &&
                    (infix[i + 1] > '9' || infix[i + 1] < '0'))) {
                        return 4;       // 4: ���������Ϸ�
                }
                // 2. '(' ������� '('�� '.' '-' ������
                else if (infix[i] == '(' && 
                         infix[i + 1] != '(' && infix[i + 1] != '.' && infix[i + 1] != '-' &&
                         (infix[i + 1] > '9' || infix[i + 1] < '0' ) ) {
                        return 4;       // 4: ���������Ϸ�
                }
                // 3. ')' ������� ')' '+' '-' '*' '/' '\0'
                else if (infix[i] == ')' && 
                    infix[i + 1] != '+' && infix[i + 1] != '-' && 
                    infix[i + 1] != '*' && infix[i + 1] != '/' &&
                    infix[i + 1] != ')' && infix[i + 1] != '\0') {
                        return 4;       // 4: ���������Ϸ�
                }
                // 4. '.' �����������
                else if (infix[i] == '.' && 
                    (infix[i + 1] > '9' || infix[i + 1] < '0')) {
                        return 4;       // 4: ���������Ϸ�
                }
                // 5. ���ֺ����� '('
                else if ((infix[i] <= '9' && infix[i] >= '0') &&
                          infix[i + 1] == '(') {
                        return 4;       // 4: ���������Ϸ�
                }
        }

        // �ж�С�������ȷ�ԣ���֤����ֻ��һ��С����
        bool hasDot = false;
        for (i = 0; i <infix.length(); i++) {
                if (infix[i] == '.') {
                        if (hasDot == true) {
                                return 4;        // 4: ���������Ϸ�
                        }
                        else {
                                hasDot = true;
                        }
                }
                else if (infix[i] > '9' || infix[i] < '0') {
                        hasDot = false;
                }
        }

        // �����������罫 -2 ת���� (0-1)*2
        for (i = 0; i <infix.length(); i++) {
                if ((i == 0 && infix[i] == '-') || 
                    ((infix[i] == '+' || infix[i] == '-' || 
                     infix[i] == '*' || infix[i] == '/' ||
                     infix[i] == '(') && infix[i + 1] == '-')) {
                        // �����ڱ��ʽ�ײ�
                        if (i == 0 && infix[i] == '-') {   
                                infix.replace(i, 1, "(0-1)*");
                                i += 4;
                        }
                        // �����ڱ��ʽ�м�
                        else {
                                infix.replace(i + 1, 1, "(0-1)*");
                                i += 5;
                        }
                }
        }

        return 0;                       // 0: �Ϸ�
}

// ת�����ʽ
void CExpression::convert(const string infix, string &postfix) {
        char ch;
        int i;
        stack<char> stk;
        for (i = 0; i < infix.length(); ) {
                ch = infix[i];
                switch(ch) {

                // ������ֱ����ջ
                case '(' :
                        stk.push(ch);
                        i++;
                        break;
                // ����������ջ��ֱ������һ��������
                case ')' :
                        while (stk.top() != '(') {
                                postfix += stk.top();
                                stk.pop();
                                
                        }
                        stk.pop();
                        i++;
                        break;
                // �����һ�����������������Ҳ����ջ����������ջ����ջ
                case '+' :
                case '-' :
                        while (!stk.empty() && stk.top() != '(') {
                                postfix += stk.top();
                                stk.pop();
                        }
                        stk.push(ch);
                        i++;
                        break;

                // ���ǰһ�������Ϊ*��/��������ջ,����ջ,����ֱ����ջ
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
                // �����������ֱ�ӽ����׺���ʽ��
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

// ������ʽ
double CExpression::calculate(const string postfix) {
        char ch;
        double num_a, num_b, num_c;
        int i;
        stack<double> stk;
        for (i = 0; i < postfix.length(); i++) {
                ch = postfix[i];
                switch (ch) {
                // �������
                case '+' :
                        num_a = stk.top();
                        stk.pop();
                        num_b = stk.top();
                        stk.pop();
                        num_c = num_b + num_a;
                        stk.push(num_c); 
                        break;
                // �������
                case '-' :
                        num_a = stk.top();
                        stk.pop();
                        num_b = stk.top();
                        stk.pop();
                        num_c = num_b - num_a;
                        stk.push(num_c); 
                        break;
                // �������
                case '*' :
                        num_a = stk.top();
                        stk.pop();
                        num_b = stk.top();
                        stk.pop();
                        num_c = num_b * num_a;
                        stk.push(num_c);  
                        break;
                // �������
                case '/' :
                        num_a = stk.top();
                        stk.pop();
                        num_b = stk.top();
                        stk.pop();
                        // �жϳ����Ƿ�Ϊ��
                        if (num_a) {
                                num_c = num_b / num_a;
                                stk.push(num_c); 
                                break;
                        }
                        else {
                                // ����Ϊ 0 
                                return 0;
                        }
                default:
                        num_a = 0;
                        num_b = 0;
                        int j;
                        // ����
                        // �˴��㷨��Ҫ�Ż�
                        while ((postfix[i] >= '0' && postfix[i] <= '9') || postfix[i] == '.') {
                                j = 10;
                                if (postfix[i] != '.') {        // ��������
                                        num_a = 10 * num_a + (postfix[i] - '0');
                                        
                                }
                                else {                          // С������
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
                        num_c = num_a + num_b;                  // ��� = �������� + С������
                        stk.push(num_c);
                        break;
                }
        }
        return stk.top();
}


