#include "LPIUtil.h"
#include "BNF/BNFSymbol.h"

bool LPIUtil::IsVerb(const BNFSymbol& symbol)
{
	return symbol.GetSymbol().find("verb") != std::string::npos;
}

bool LPIUtil::IsNoun(const BNFSymbol& symbol)
{
	return symbol.GetSymbol().find("noun") != std::string::npos;

}

bool LPIUtil::IsAdjective(const BNFSymbol& symbol)
{
	return symbol.GetSymbol().find("adjective") != std::string::npos;
}

bool LPIUtil::IsPreposition(const BNFSymbol& symbol)
{
	return symbol.GetSymbol().find("preposition") != std::string::npos;
}
