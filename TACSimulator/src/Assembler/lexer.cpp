#include "../Assembler/Lexer.h"
#include <string>
#include <utility>
#include <stdexcept>

using std::string;
using std::pair;

void Lexer::scanProgram(string& program) {
	while (program.length() > 0) {
		pair<MatchType, string> longestMatchWithType = findLongestMatch(program);
		MatchType type = longestMatchWithType.first;
		string longestMatch = longestMatchWithType.second;

		switch (type) {
			case MatchType::Identifier:
				break;
			case MatchType::OneSymbol:
				break;
			case MatchType::Integer:
				break;
			case MatchType::Whitespace:
				break;
			default:
				throw std::runtime_error("Unable to match type");
				break;
		}
	}
}

pair<MatchType, string> Lexer::findLongestMatch(string const& program) const {
	MatchType longestMatchType = MatchType::Identifier;
	string longestMatch = matchIdentifer(program);
	int longestMatchLength = static_cast<int>(longestMatch.size());

	string possibleOneSymbolMatch = matchOneSymbol(program);
	string possibleIntegerMatch = matchInteger(program);
	string possibleWhitespaceMatch = matchWhitespace(program);

	int oneSymbolMatchLength = static_cast<int>(possibleOneSymbolMatch.size());
	int integerMatchLength = static_cast<int>(possibleIntegerMatch.size());
	int whitespaceMatchLength = static_cast<int>(possibleWhitespaceMatch.size());

	if (oneSymbolMatchLength > longestMatchLength) {
		longestMatchType = MatchType::OneSymbol;
		longestMatchLength = oneSymbolMatchLength;
		longestMatch = possibleOneSymbolMatch;
	}

	if (integerMatchLength > longestMatchLength) {
		longestMatchType = MatchType::Integer;
		longestMatchLength = integerMatchLength;
		longestMatch = possibleIntegerMatch;
	}

	if (whitespaceMatchLength > longestMatchLength) {
		longestMatchType = MatchType::Whitespace;
		longestMatchLength = whitespaceMatchLength;
		longestMatch = possibleWhitespaceMatch;
	}

	pair<MatchType, string> longestMatchWithType;
	longestMatchWithType.first = longestMatchType;
	longestMatchWithType.second = longestMatch;

	return longestMatchWithType;
}

/*
 * Identifiers will be matched by "[a-zA-Z]_1[a-zA-Z0-9]*"
 */
string Lexer::matchIdentifer(string const& program) const {
	string identifier = "";
	int i = 0;
	if ((program[i] >= 'a' && program[i] <= 'z') || (program[i] >= 'A' && program[i] <= 'Z')) {
		identifier += program[i];
		i++;
	}
	else {
		return identifier;
	}

	while (
		(program[i] >= 'a' && program[i] <= 'z') || 
		(program[i] >= 'A' && program[i] <= 'Z') ||
		(program[i] >= '0' && program[i] <= '9')
	) {
		identifier += program[i];
		i++;
	}

	return identifier;
}

/*
 * Whitespace will be matched by "\r|\n|\t|\s"
 */
string Lexer::matchWhitespace(string const& program) const {
	string whitespace = "";

	if (
		program[0] == '\r' ||
		program[0] == '\n' ||
		program[0] == '\t' ||
		program[0] == ' '
	) {
		whitespace += program[0];
	}

	return whitespace;
}

/*
 * One symbols will be matched by ",|:|[|]"
 */
string Lexer::matchOneSymbol(string const& program) const {
	string oneSymbol = "";
	if (
		program[0] == ',' ||
		program[0] == ':' ||
		program[0] == '[' ||
		program[0] == ']'
	) {
		oneSymbol += program[0];
	}

	return oneSymbol;
}

/*
 * Integers will be matched by "-?[0-9]"
 */
string Lexer::matchInteger(string const& program) const {
	string integer = "";
	int i = 0;
	if (program[i] == '-') {
		integer += program[i];
		i++;
	}

	while (
		program[i] >= '0' && program[i] <= '9'
	) {
		integer += program[i];
		i++;
	}
	return integer;
}

Token Lexer::resolveIdentifier(string const& identifier) const {
	return Token("", TokenType::addI_Inst, 0, 0);
}

Token Lexer::resolveInteger(string const& integer) const {
	return Token("", TokenType::addI_Inst, 0, 0);
}

Token Lexer::resolveOneSymbol(string const& oneSymbol) const {
	return Token("", TokenType::addI_Inst, 0, 0);
}