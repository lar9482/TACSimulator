#pragma once


#include <string>
#include <utility>
#include <queue>
#include "Token.h"

enum class MatchType {
	Identifier,
	OneSymbol,
	Integer,
	Whitespace
};

class Lexer {;
private:

	int lineCounter;
	int columnCounter;

	std::string matchIdentifer(std::string const& program) const;
	std::string matchWhitespace(std::string const& program) const;
	std::string matchOneSymbol(std::string const& program) const;
	std::string matchInteger(std::string const& program) const;
	std::pair<MatchType, std::string> findLongestMatch(std::string const& program) const;
	Token resolveIdentifier(std::string const& identifier) const;
	Token resolveOneSymbol(std::string const& oneSymbol) const;

public:
	Lexer() : lineCounter(1), columnCounter(1) {}
	std::queue<Token> scanProgram(std::string& program);
};