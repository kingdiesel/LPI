#include "LexerToken.h"

LexerToken::LexerToken(const std::string& token, const std::string symbol):
	m_token(token),
	m_symbol(symbol)
{
}

void LexerToken::SetToken(const std::string& token)
{
	m_token = token;
}

const std::string& LexerToken::GetToken() const
{
	return m_token;
}

void LexerToken::SetSymbol(const std::string& symbol)
{
	m_symbol = symbol;
}

const std::string& LexerToken::GetSymbol()
{
	return m_symbol;
}
