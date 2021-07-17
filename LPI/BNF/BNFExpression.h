#pragma once
#include <string>

class BNFExpression
{
public:
	BNFExpression() = default;
	~BNFExpression() = default;
	
	BNFExpression(const std::string& expression, const bool is_redirect);

	bool operator==(const BNFExpression& rhs);

	const std::string& GetExpression() const;
	void SetExpression(const std::string& expression);
private:
	std::string m_expression;
	bool m_is_redirect = false;
};