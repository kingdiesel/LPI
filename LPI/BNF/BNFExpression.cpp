#include "BNFExpression.h"

BNFExpression::BNFExpression(const std::vector<std::string>& expression)
{
	for (const std::string& expression_term : expression)
	{
		m_expression_terms.emplace_back(expression_term, expression_term.find("<") == 0);
	}
}

int BNFExpression::GetNumTerms() const
{
	return static_cast<int>(m_expression_terms.size());
}

const std::vector<BNFExpressionTerm>& BNFExpression::GetExpressionTerms() const
{
	return m_expression_terms;
}
