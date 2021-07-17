#include "BNFExpression.h"

BNFExpression::BNFExpression(const std::string& expression, const bool is_redirect) :
	m_expression(expression),
	m_is_redirect(is_redirect)
{
}

bool BNFExpression::operator==(const BNFExpression& rhs)
{
	return m_expression == rhs.m_expression;
}

const std::string& BNFExpression::GetExpression() const
{
	return m_expression;
}

void BNFExpression::SetExpression(const std::string& expression)
{
	m_expression = expression;
}
