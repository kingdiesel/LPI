#include "BNFNode.h"

BNFNode::BNFNode(const std::string& symbol, const std::vector<std::vector<std::string>>& expressions)
{
	m_symbol.SetSymbol(symbol);
	// TODO: emplace
	for (const std::vector<std::string>& expression : expressions)
	{
		BNFExpression bnf_expression(expression);
		m_expressions.push_back(bnf_expression);
	}
}

const BNFSymbol& BNFNode::GetSymbol() const
{
	return m_symbol;
}

BNFSymbol& BNFNode::GetSymbol()
{
	return m_symbol;
}
