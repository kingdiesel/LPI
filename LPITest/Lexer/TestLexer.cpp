#include "pch.h"
#include <gtest/gtest.h>
#include "BNF/BNF.cpp"
#include "BNF/BNFTree.cpp"
#include "Lexer/Lexer.cpp"

namespace TestLexerStrings
{
	const std::string basic_grammar = "; basic adventure game grammar, <command> must always be present, it's the expected root\n"
		"<command> ::= LOOK | HELP\n";

	const std::string intermediate_grammar = "; basic adventure game grammar, <command> must always be present, it's the expected root\n"
		"<command> ::= <unary_verb> | <verb> <noun>\n"
		"<unary_verb> ::= LOOK | HELP\n"
		"<verb> ::= PICKUP | INSERT | GIVE | WALK | ASK\n"
		"<noun> ::= NORTH | SOUTH | EAST | WEST | FROG | LLAMA | GOAT | KEY | LOCK | WATERFLASK\n";

	const std::string advanced_grammar = "; basic adventure game grammar, <command> must always be present, it's the expected root\n"
		"<command> ::= <unary_verb> | <verb> <noun> | <verb> <adjective> <noun> | <verb> <adjective> <noun> <preposition> <adjective> <noun>\n"
		"<unary_verb> ::= LOOK | HELP\n"
		"<verb> ::= PICKUP | INSERT | GIVE | WALK | ASK\n"
		"<adjective> ::= BLUE | RUSTY | THIRSTY | EMPTY | OLD\n"
		"<preposition> ::= INTO | TO | ABOUT\n"
		"<noun> ::= <noun_direction> | <noun_animal> | <noun_object>\n"
		"<noun_direction> ::= NORTH | SOUTH | EAST | WEST\n"
		"<noun_animal> ::= FROG | LLAMA | GOAT\n"
		"<noun_object> ::= KEY | LOCK | WATERFLASK\n";
}

TEST(TestLexer, TestBasicGrammarParsing)
{
	BNF grammar;
	const bool parsed_grammar = grammar.ParseString(TestLexerStrings::basic_grammar);
	EXPECT_TRUE(parsed_grammar);
}

TEST(TestLexer, TestIntermediateGrammarParsing)
{
	BNF grammar;
	const bool parsed_grammar = grammar.ParseString(TestLexerStrings::intermediate_grammar);
	EXPECT_TRUE(parsed_grammar);
}

TEST(TestLexer, TestAdvancedGrammarParsing)
{
	BNF grammar;
	const bool parsed_grammar = grammar.ParseString(TestLexerStrings::advanced_grammar);
	EXPECT_TRUE(parsed_grammar);
}

TEST(TestLexer, TestBasicTokenMatch)
{
	BNF grammar;
	const bool parsed_grammar = grammar.ParseString(TestLexerStrings::basic_grammar);
	EXPECT_TRUE(parsed_grammar);

	Lexer lexer;
	{
		std::vector<BNFMatchResult> result;
		const bool match = lexer.MatchString("LOOK", result, grammar);
		EXPECT_TRUE(match);
		ASSERT_TRUE(result.size() == 1);
		EXPECT_TRUE(result[0].m_symbol == "<command>");
		EXPECT_TRUE(result[0].m_expression_term.value == "LOOK");
	}
	
	{
		std::vector<BNFMatchResult> result;
		const bool match = lexer.MatchString("HELP", result, grammar);
		EXPECT_TRUE(match);
		ASSERT_TRUE(result.size() == 1);
		EXPECT_TRUE(result[0].m_symbol == "<command>");
		EXPECT_TRUE(result[0].m_expression_term.value == "HELP");
	}
	
	{
		std::vector<BNFMatchResult> result;
		const bool match = lexer.MatchString("INVALID", result, grammar);
		EXPECT_FALSE(match);
	}
	
}

TEST(TestLexer, TestIntermediateTokenMatch)
{
	BNF grammar;
	const bool parsed_grammar = grammar.ParseString(TestLexerStrings::intermediate_grammar);
	EXPECT_TRUE(parsed_grammar);

	Lexer lexer;
	{
		std::vector<BNFMatchResult> result;
		const bool match = lexer.MatchString("LOOK", result, grammar);
		EXPECT_TRUE(match);
		ASSERT_TRUE(result.size() == 1);
		EXPECT_TRUE(result[0].m_symbol == "<unary_verb>");
		EXPECT_TRUE(result[0].m_expression_term.value == "LOOK");
	}
}