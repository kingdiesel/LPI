#pragma once
#include <string>
#include <vector>

struct BNFExpressionTerm
{
	BNFExpressionTerm() = delete;
	BNFExpressionTerm(const std::string& in_term, const bool in_is_redirect) :
		value(in_term),
		is_redirect(in_is_redirect)
	{}
	std::string value;
	bool is_redirect = false;
};

class BNFExpression
{
public:
	BNFExpression() = delete;
	BNFExpression(const std::vector<std::string>& expression);

	const std::vector<BNFExpressionTerm>& GetExpressionTerms() const;
private:
	std::vector<BNFExpressionTerm> m_expression_terms;
};