#include "BNFNode.h"

BNFNode::BNFNode(const std::string& symbol, const std::vector<std::vector<std::string>>& expressions)
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
