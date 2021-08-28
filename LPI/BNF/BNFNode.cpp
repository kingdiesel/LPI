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

bool BNFNode::Match(const std::vector<std::string>& tokens, std::vector<BNFMatchResult>& out_result)
{
	if (IsLeafNode())
	{
		// if i got to a leaf node, i should only be matching single tokens
		assert(tokens.size() == 1);
		const bool matched = tokens[0] == m_expression.GetExpressionTerms()[0].value;
		if (matched)
		{
			out_result.emplace_back(m_symbol, m_expression.GetExpressionTerms()[0]);
			return true;
		}
	}
	else if (IsPlaceholder())
	{
		// placeholder is a node that split an expression
		for (BNFNode* child : m_children)
		{
			// this expression matches the number of terms, so we should attempt matching
			if (child->GetExpression().GetNumTerms() == tokens.size())
			{
				const bool matched = child->Match(tokens, out_result);
				if (matched)
				{
					return true;
				}
			}
		}
	}
	else
	{
		// try to match terms one by one
		bool all_matched = true;
		std::vector<BNFMatchResult> cached_results = out_result;
		for (unsigned int i = 0; i < tokens.size() && all_matched; ++i)
		{
			std::vector<std::string> token;
			token.push_back(tokens[i]);
			all_matched = all_matched && m_children[i]->Match(token, out_result);
		}

		if (all_matched)
		{
			return true;
		}
		else
		{
			out_result = cached_results;
		}
	}
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
