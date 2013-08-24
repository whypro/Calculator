// Expression.h: interface for the CExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPRESSION_H__8CC8A9D0_880D_45A6_84BD_A5B9097EC599__INCLUDED_)
#define AFX_EXPRESSION_H__8CC8A9D0_880D_45A6_84BD_A5B9097EC599__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <stack>
using namespace std;

class CExpression  
{
public:
	CExpression();
	virtual ~CExpression();

        int fix(const string input, string &infix);
        void convert(const string infix, string &postfix);
        double calculate(const string postfix);

};

#endif // !defined(AFX_EXPRESSION_H__8CC8A9D0_880D_45A6_84BD_A5B9097EC599__INCLUDED_)
