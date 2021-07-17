#pragma once
#include <string>
class LexerToken
{
public:
	LexerToken() = default;
	LexerToken(const std::string& token, const std::string symbol);

	void SetToken(const std::string& token);
	const std::string& GetToken() const;

	void SetSymbol(const std::string& symbol);
	const std::string& GetSymbol();
private:
	std::string m_token;
	std::string m_symbol;
};