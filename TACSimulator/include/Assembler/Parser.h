#pragma once
#include <queue>

#include "Token.h"
#include "../Assembler/Inst.h"

class Parser {
private:
	std::queue<Token> tokenQueue;

	ArithLog parseArithLog();
	Shift parseShift();
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