#pragma once


#include <queue>
#include "Token.h"
#include "memory"

class Parser {
private:
	std::queue<Token> tokenQueue;

	void parseArithLog();
	void parseDivMult();
	void parseShift();
	void parseShiftV();
	void parseBranch();
	void parseBranchZ();
	void parseArithLogI();
	void parseLoadStore();
	void parseJump();
	void parseJumpR();
	void parseMove();
	void parseMoveI();

	Token parseReg();
	Token consume(TokenType const& type);
public:
	Parser(std::queue<Token>& tokenQueue);
	void parseProgram();
};