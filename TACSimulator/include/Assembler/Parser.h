#pragma once


#include <queue>
#include "Token.h"
#include "memory"

class Parser {
private:
	std::unique_ptr<std::queue<Token>> tokenQueue;
	void parseRInst();
	void parseJInst();
	void parseIInst();
	void parseLabel();
	Token parseReg();
	Token consume(TokenType const& type);
public:
	Parser(std::queue<Token>& tokenQueue);
	void parseProgram();
};