#include "BNFExpression.h"

BNFExpression::BNFExpression(const std::vector<std::string>& expression) :
	m_expression(expression)
{
	// TODO unique pointer to expression so we don't make copies
	m_is_redirect.resize(m_expression.size());
	for (int i = 0; i < m_expression.size(); ++i)
	{
		if (m_expression[i].find("<") == 0)
		{
			m_is_redirect[i] = true;
		}
	}
}

bool BNFExpression::operator==(const BNFExpression& rhs)
{
	return m_expression == rhs.m_expression;
}

const std::vector<std::string>& BNFExpression::GetExpression() const
{
	return m_expression;
}
