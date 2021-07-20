#include "BNFNode.h"
#include <cassert>

BNFNode::BNFNode(const std::string& symbol, const std::vector<std::string>& expressions):
m_symbol(symbol),
m_expression(expressions)
{
}

const BNFSymbol& BNFNode::GetSymbol() const
{
	return m_symbol;
}

BNFSymbol& BNFNode::GetSymbol()
{
	return m_symbol;
}

void BNFNode::AddChild(BNFNode* node)
{
	assert(std::find(m_children.begin(), m_children.end(), node) == m_children.end());
}
