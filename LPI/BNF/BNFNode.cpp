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

const BNFExpression& BNFNode::GetExpression() const
{
	return m_expression;
}

void BNFNode::AddChild(BNFNode* node)
{
	assert(std::find(m_children.begin(), m_children.end(), node) == m_children.end());
	assert(node != nullptr);
	m_children.push_back(node);
}

BNFNode* BNFNode::FindTreeNode(const std::string& symbol)
{
	for (BNFNode* child : m_children)
	{
		if (child->GetSymbol() == symbol)
		{
			return child;
		}
		else
		{
			return child->FindTreeNode(symbol);
		}
	}
	return nullptr;
}

bool BNFNode::Match(std::vector<std::string>& tokens, std::vector<BNFMatchResult>& out_result)
{
	return false;
}

bool BNFNode::IsPlaceholder() const
{
	return m_expression.GetExpressionTerms().size() == 0;
}

bool BNFNode::IsLeafNode() const
{
	return m_children.size() == 0;
}
