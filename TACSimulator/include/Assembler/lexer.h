#pragma once

#include <string>

class Lexer {;
private:
	int lineCounter;
	int columnCounter;

	std::string matchIdentifer(std::string& program);
	std::string matchWhitespace(std::string& program);
	std::string matchOneSymbol(std::string& program);
	std::string matchInteger(std::string& program);

public:
	void scanProgram(std::string& program);
};