#pragma once

#include "Token.h"
#include "../Assembler/Inst.h"

#include <queue>

class Parser {
private:
	std::queue<Token> tokenQueue;

	ArithLog parseArithLog();
	Branch parseBranch();
	BranchZ parseBranchZ();
	ArithLogI parseArithLogI();
	LoadStore parseLoadStore();
	Jump parseJump();
	JumpR parseJumpR();
	Move parseMove();
	MoveI parseMoveI();
	Label parseLabel();
	Trap parseTrap();

	Token parseReg();
	Token consume(TokenType const& type);
public:
	Parser(std::queue<Token>& tokenQueue);
	std::queue<std::unique_ptr<Inst>> parseProgram();
};