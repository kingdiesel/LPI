#include "BNF.h"
#include "BNFTree.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <cassert>

bool BNF::ParseString(const std::string& bnf_string)
{
	std::stringstream string_stream;
	string_stream << bnf_string;
	return ParseStream(string_stream);
}

BNF::BNF()
{
	m_tree = new BNFTree();
}

BNF::~BNF()
{
	if (m_tree != nullptr)
	{
		delete m_tree;
	}
	m_tree = nullptr;
}

bool BNF::ParseFile(const std::string& filename)
{
	assert(m_tree != nullptr);
	std::ifstream grammar_file;
	grammar_file.open(filename);
	if (grammar_file.is_open()) 
	{
		const bool parsed = ParseStream(grammar_file);
		grammar_file.close();
		return parsed;
	}
	return false;
}

bool BNF::ParseStream(std::istream& stream)
{
	assert(m_tree != nullptr);
	std::string grammar_line;
	while (stream.good())
	{
		std::getline(stream, grammar_line);
		// TODO: determine valid bnf entry via regex

		// skip comments
		if (grammar_line.find(";") == 0 || grammar_line.length() == 0)
		{
			continue;
		}

		// split by defined as token ::=
		std::regex regex_split_defined_as("::=");
		std::vector<std::string> split_by_defined_as
		(
			std::sregex_token_iterator(grammar_line.begin(), grammar_line.end(), regex_split_defined_as, -1),
			std::sregex_token_iterator()
		);

		// make sure we split properly
		if (split_by_defined_as.size() != 2)
		{
			std::cerr << "Poorly formatted line:" + grammar_line << std::endl;
			return false;
		}

		// remove any trailing or leading spaces from symbol
		split_by_defined_as[0].erase(std::remove_if(split_by_defined_as[0].begin(), split_by_defined_as[0].end(), isspace), split_by_defined_as[0].end());
		const std::string symbol = split_by_defined_as[0];

		// get symbol
		std::regex regex_split_expression("\\|");
		std::vector<std::string> split_by_expression
		(
			std::sregex_token_iterator(split_by_defined_as[1].begin(), split_by_defined_as[1].end(), regex_split_expression, -1),
			std::sregex_token_iterator()
		);

		// remove spaces
		// TODO: we're making an assumption here on the adventure game language that expression entries are always
		// separated by spaces
		for (std::string& expression : split_by_expression)
		{
			expression.erase(std::remove_if(expression.begin(), expression.end(), isspace), expression.end());
		}

		// subdivide expressions if needed
		std::regex regex_subdivide_expressions("<[a-z_]+>|[A-Z]+");
		for (const std::string& expression : split_by_expression)
		{
			std::vector<std::string> subdivided_expressions;
			std::regex_token_iterator<std::string::const_iterator> first(expression.begin(), expression.end(), regex_subdivide_expressions), last;
			while (first != last)
			{
				subdivided_expressions.push_back(first->str());
				++first;
			}

			// TODO: emplace
			BNFNode node(symbol, subdivided_expressions);
			m_tree->AddNode(node);
		}
	}
	m_tree->Populate();
	return true;
}

bool BNF::Match(const std::vector<std::string>& tokens, std::vector<BNFMatchResult>& out_result)
{
	assert(m_tree != nullptr);
	return m_tree->Match(tokens, out_result);
}
