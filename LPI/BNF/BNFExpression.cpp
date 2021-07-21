#include "BNFExpression.h"

BNFExpression::BNFExpression(const std::vector<std::string>& expression)
{
	for (const std::string& expression_term : expression)
	{
		m_expression.emplace_back(expression_term, expression_term.find("<") == 0);
	}
}

const std::vector<BNFExpressionTerm>& BNFExpression::GetExpressionTerms() const
{
	return m_expression;
}
