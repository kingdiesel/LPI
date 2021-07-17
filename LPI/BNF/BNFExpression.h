#pragma once
#include <string>
#include <vector>

class BNFExpression
{
public:
	BNFExpression() = default;
	~BNFExpression() = default;
	
	BNFExpression(const std::vector<std::string>& expression);

	bool operator==(const BNFExpression& rhs);

	const std::vector<std::string>& GetExpression() const;
private:
	std::vector<std::string> m_expression;
	std::vector<bool> m_is_redirect;
};