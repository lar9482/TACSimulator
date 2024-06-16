#pragma once
#include <queue>

#include "Token.h"
#include "../Assembler/Inst/Register/ArithLog.h"
#include "../Assembler/Inst/Register/DivMult.h"
#include "../Assembler/Inst/Register/Shift.h"
#include "../Assembler/Inst/Register/ShiftV.h"
#include "../Assembler/Inst/Immediate/ArithLogI.h"
#include "../Assembler/Inst/Immediate/Branch.h"
#include "../Assembler/Inst/Immediate/BranchZ.h"
#include "../Assembler/Inst/Immediate/LoadStore.h"
#include "../Assembler/Inst/Jump/Jump.h"
#include "../Assembler/Inst/Jump/JumpR.h"
#include "../Assembler/Inst/Move/Move.h"
#include "../Assembler/Inst/Move/MoveI.h"

class Parser {
private:
	std::queue<Token> tokenQueue;

	ArithLog parseArithLog();
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