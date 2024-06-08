#include "../Assembler/Lexer.h"
#include <string>

using std::string;

void Lexer::scanProgram(string& program) {
	while (program.length() > 0) {
		string possibleIdentifer = matchIdentifer(program);
		string possibleInteger = matchInteger(program);
		string possibleOneSymbol = matchOneSymbol(program);
		string possibleWhiteSpace = matchWhitespace(program);
	}
}

/*
 * Identifiers will be matched by "[a-zA-Z]_1[a-zA-Z0-9]*"
 */
string Lexer::matchIdentifer(string& program) {
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
string Lexer::matchWhitespace(string& program) {
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
string Lexer::matchOneSymbol(string& program) {
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
string Lexer::matchInteger(string& program) {
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
