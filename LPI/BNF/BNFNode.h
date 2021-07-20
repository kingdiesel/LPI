#pragma once
#include "BNFSymbol.h"
#include "BNFExpression.h"
#include <vector>
class BNFNode
{
public:
	BNFNode() = default;
	BNFNode(const std::string& symbol, const std::vector<std::string>& expressions);

	~BNFNode() = default;
	const BNFSymbol& GetSymbol() const;
	BNFSymbol& GetSymbol();

	void AddChild(BNFNode* node);

private:
	BNFSymbol m_symbol;
	BNFExpression m_expression;
	std::vector<BNFNode*> m_children;
};