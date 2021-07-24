#pragma once
#include <string>

class BNFSymbol
{
public:
	BNFSymbol() = delete;
	BNFSymbol(const std::string& symbol);

	bool operator==(const BNFSymbol& rhs) const;
	bool operator==(const std::string& rhs) const;
	
	bool operator!=(const BNFSymbol& rhs) const;
	bool operator!=(const std::string& rhs) const;

	const std::string& GetSymbol() const;
	void SetSymbol(const std::string& symbol);
private:
	std::string m_symbol;
};