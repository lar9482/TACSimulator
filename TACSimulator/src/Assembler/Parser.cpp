#include <stdexcept>
#include "../Assembler/Parser.h"

Parser::Parser(std::queue<Token>& tokenQueue)
	: tokenQueue(
		std::make_unique<std::queue<Token>>(std::move(tokenQueue))
	)
{}

void Parser::parseProgram() {
	while (tokenQueue->size() > 0) {
		switch (tokenQueue->front().type) {
            case TokenType::mov_Inst:
            case TokenType::add_Inst:
            case TokenType::sub_Inst:
            case TokenType::mult_Inst:
            case TokenType::div_Inst:
            case TokenType::and_Inst:
            case TokenType::or_Inst:
            case TokenType::xor_Inst:
            case TokenType::not_Inst:
            case TokenType::nor_Inst:
            case TokenType::sllv_Inst:
            case TokenType::srav_Inst:
                parseRInst();
                break;
            case TokenType::identifier:
                parseLabel();
                break;
		}
	}
}

void Parser::parseRInst() {
    Token opToken = consume(tokenQueue->front().type);
    Token reg1Token = parseReg();
    consume(TokenType::comma);
    Token reg2Token = parseReg();
    consume(TokenType::comma);
    Token reg3Token = parseReg();
}

void Parser::parseJInst() {

}

//Immediate instructions(opcode reg, reg, integer)
void Parser::parseIInst() {

}

void Parser::parseLabel() {
    Token labelToken = consume(TokenType::identifier);
    consume(TokenType::colon);
}

//Register instructions(opcode reg, reg, reg)
Token Parser::parseReg() {
    switch (tokenQueue->front().type) {
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
            return consume(tokenQueue->front().type);
        default:
            throw std::runtime_error("Unable to match the register.");
    }
}

Token Parser::consume(const TokenType& type) {
    if (tokenQueue->front().type == type) {
        Token currToken = tokenQueue->front();
        tokenQueue->pop();

        return currToken;
    }
    else {
        throw std::runtime_error("Token type doesn't match up");
    }
}