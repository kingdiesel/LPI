#pragma once
#include "BNFSymbol.h"
#include "BNFExpression.h"
#include <vector>
class BNFNode
{
public:
	BNFNode() = delete;
	BNFNode(const std::string& symbol, const std::vector<std::string>& expressions);
	
	const BNFSymbol& GetSymbol() const;
	const BNFExpression& GetExpression() const;
	
	void AddChild(BNFNode* node);
	BNFNode* FindTreeNode(const std::string& symbol);
private:
	BNFSymbol m_symbol;
	BNFExpression m_expression;
	std::vector<BNFNode*> m_children;
	// TODO: track placeholder nodes
};