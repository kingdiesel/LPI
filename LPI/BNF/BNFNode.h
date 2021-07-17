#pragma once
#include "BNFSymbol.h"
#include "BNFExpression.h"
#include <vector>
class BNFNode
{
public:
	BNFNode() = default;
	BNFNode(const std::string& symbol, const std::vector<std::vector<std::string>>& expressions);

	~BNFNode() = default;
	const BNFSymbol& GetSymbol() const;
	BNFSymbol& GetSymbol();

private:
	BNFSymbol m_symbol;
	std::vector<BNFExpression> m_expressions;
};