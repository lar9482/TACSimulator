#include <stdexcept>
#include "../Assembler/Parser.h"

using std::queue;
using std::unique_ptr;
using std::make_unique;

Parser::Parser(std::queue<Token>& tokenQueue)
	: tokenQueue(std::move(tokenQueue))
{}

void Parser::parseProgram() {
    queue<unique_ptr<Inst>> allInsts;
	while (tokenQueue.size() > 0) {
		switch (tokenQueue.front().type) {
            case TokenType::mov_Inst:
                allInsts.push(make_unique<Move>(parseMove()));
                break;
            case TokenType::add_Inst:
            case TokenType::sub_Inst:
            case TokenType::and_Inst:
            case TokenType::or_Inst:
            case TokenType::xor_Inst:
            case TokenType::not_Inst:
            case TokenType::nor_Inst:
            case TokenType::sllv_Inst:
            case TokenType::srav_Inst:
                allInsts.push(make_unique<ArithLog>(parseArithLog()));
                break;
            case TokenType::mult_Inst:
            case TokenType::div_Inst:
                allInsts.push(make_unique<DivMult>(parseDivMult()));
                break;
            case TokenType::movI_Inst:
                allInsts.push(make_unique<MoveI>(parseMoveI()));
                break;
            case TokenType::identifier:
                break;
            default:
                throw std::runtime_error("Unable to match an opcode");
		}
	}
}

/*
 * Parsing instructions in the form:
 * opcode reg1, reg2, reg3
 */
ArithLog Parser::parseArithLog() {
    Token opcode = consume(tokenQueue.front().type);

    Token reg1 = parseReg();
    consume(TokenType::comma);
    Token reg2 = parseReg();
    consume(TokenType::comma);
    Token reg3 = parseReg();

    return ArithLog(opcode, reg1, reg2, reg3);
}

/*
 * Parsing instructions in the form:
 * opcode reg1, reg2
 */
DivMult Parser::parseDivMult() {
    Token opcode = consume(tokenQueue.front().type);

    Token reg1 = parseReg();
    consume(TokenType::comma);
    Token reg2 = parseReg();

    return DivMult(opcode, reg1, reg2);
}

/*
 * Parsing instructions in the form:
 * opcode reg1, reg2, integer
 */
Shift Parser::parseShift() {
    Token opcode = consume(tokenQueue.front().type);

    Token reg1 = parseReg();
    consume(TokenType::comma);
    Token reg2 = parseReg();
    consume(TokenType::comma);
    Token integer = consume(TokenType::integer);

    return Shift(opcode, reg1, reg2, integer);
}

/*
 * Parsing instructions in the form:
 * opcode reg1, reg2, reg3
 */
ShiftV Parser::parseShiftV() {
    Token opcode = consume(tokenQueue.front().type);

    Token reg1 = parseReg();
    consume(TokenType::comma);
    Token reg2 = parseReg();
    consume(TokenType::comma);
    Token reg3 = parseReg();

    return ShiftV(opcode, reg1, reg2, reg3);
}

/*
 * Parsing instructions in the form:
 * opcode reg1, reg2, label
 */
Branch Parser::parseBranch() {
    Token opcode = consume(tokenQueue.front().type);

    Token reg1 = parseReg();
    consume(TokenType::comma);
    Token reg2 = parseReg();
    consume(TokenType::comma);
    Token label = consume(TokenType::identifier);

    return Branch(opcode, reg1, reg2, label);
}

/*
 * Parsing instructions in the form:
 * opcode reg, label
 */
BranchZ Parser::parseBranchZ() {
    Token opcode = consume(tokenQueue.front().type);
    Token reg = parseReg();
    consume(TokenType::comma);
    Token label = consume(TokenType::identifier);

    return BranchZ(opcode, reg, label);
}

/*
 * Parsing instructions in the form:
 * opcode reg1, reg2, integer
 */
ArithLogI Parser::parseArithLogI() {
    Token opcode = consume(tokenQueue.front().type);

    Token reg1 = parseReg();
    consume(TokenType::comma);
    Token reg2 = parseReg();
    consume(TokenType::comma);
    Token integer = consume(TokenType::integer);

    return ArithLogI(opcode, reg1, reg2, integer);
}

/*
 * Parsing instructions in the form:
 * opcode reg1, integer[reg2]
 */
LoadStore Parser::parseLoadStore() {
    Token opcode = consume(tokenQueue.front().type);

    Token reg1 = parseReg();
    consume(TokenType::comma);
    Token offset = consume(TokenType::integer);
    consume(TokenType::startBracket);
    Token reg2 = parseReg();
    consume(TokenType::endBracket);

    return LoadStore(opcode, reg1, offset, reg2);
}

/*
 * Parsing instructions in the form:
 * opcode label
 */
Jump Parser::parseJump() {
    Token opcode = consume(tokenQueue.front().type);
    Token label = consume(TokenType::identifier);

    return Jump(opcode, label);
}

/*
 * Parsing instructions in the form:
 * opcode reg
 */
JumpR Parser::parseJumpR() {
    Token opcode = consume(tokenQueue.front().type);
    Token reg = parseReg();

    return JumpR(opcode, reg);
}

/*
 * Parsing instructions in the form:
 * opcode reg1, reg2
 */
Move Parser::parseMove() {
    Token opcode = consume(tokenQueue.front().type);
    Token reg1 = parseReg();
    consume(TokenType::comma);
    Token reg2 = parseReg();

    return Move(opcode, reg1, reg2);
}

/*
 * Parsing instructions in the form:
 * opcode reg, integer
 */
MoveI Parser::parseMoveI() {
    Token opcode = consume(tokenQueue.front().type);
    Token reg = parseReg();
    consume(TokenType::comma);
    Token integer = consume(TokenType::integer);

    return MoveI(opcode, reg, integer);
}

//Register instructions(opcode reg, reg, reg)
Token Parser::parseReg() {
    switch (tokenQueue.front().type) {
        case TokenType::r0_Reg:
        case TokenType::r1_Reg:
        case TokenType::r2_Reg:
        case TokenType::r3_Reg:
        case TokenType::r4_Reg:
        case TokenType::r5_Reg:
        case TokenType::r6_Reg:
        case TokenType::r7_Reg:
        case TokenType::r8_Reg:
        case TokenType::r9_Reg:
        case TokenType::r10_Reg:
        case TokenType::r11_Reg:
        case TokenType::r12_Reg:
        case TokenType::r13_Reg:
        case TokenType::r14_Reg:
        case TokenType::r15_Reg:
        case TokenType::r16_Reg:
        case TokenType::r17_Reg:
        case TokenType::r18_Reg:
        case TokenType::r19_Reg:
        case TokenType::r20_Reg:
        case TokenType::r21_Reg:
        case TokenType::r22_Reg:
        case TokenType::r23_Reg:
        case TokenType::r24_Reg:
        case TokenType::r25_Reg:
        case TokenType::rSP_Reg:
        case TokenType::rFP_Reg:
        case TokenType::rRET_Reg:
        case TokenType::rHI_Reg:
        case TokenType::rLO_Reg:
        case TokenType::rIP_Reg:
            return consume(tokenQueue.front().type);
        default:
            throw std::runtime_error("Unable to match the register.");
    }
}

Token Parser::consume(const TokenType& type) {
    if (tokenQueue.front().type == type) {
        Token currToken = tokenQueue.front();
        tokenQueue.pop();

        return currToken;
    }
    else {
        throw std::runtime_error("Token type doesn't match up");
    }
}