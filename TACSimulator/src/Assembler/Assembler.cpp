#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <memory>

#include "../Assembler/Assembler.h"
#include "../Assembler/Lexer.h"
#include "../Assembler/Parser.h"
#include "../Assembler/Inst.h"

using std::string;
using std::queue;
using std::unique_ptr;

void Assembler::assembleFile(const string& filePath) {
	string program = readProgramFromFile(filePath);
	
	Lexer lexer;
	queue<Token> tokenQueue = lexer.scanProgram(program);
	Parser parser(tokenQueue);
	queue<unique_ptr<Inst>> allInsts = parser.parseProgram();

    findLabelAddresses(allInsts);

	while (allInsts.size() > 0) {
		auto inst = allInsts.front().get();
		inst->assembleInst(*this);
		allInsts.pop();
	}
}

string Assembler::readProgramFromFile(const string& filePath) {
	std::ifstream file(filePath);

	if (!file) {
		throw UnableToReadFromFileException(filePath);
	}

	std::ostringstream ss;
	ss << file.rdbuf();

	string programContent = ss.str();

	return programContent;
}

uint8_t Assembler::assembleOpcode(const Token& opcode) const {
    switch (opcode.type) {
    case TokenType::mov_Inst:      return 0b000000;
    case TokenType::add_Inst:      return 0b000001;
    case TokenType::sub_Inst:      return 0b000010;
    case TokenType::mult_Inst:     return 0b000011;
    case TokenType::div_Inst:      return 0b000100;
    case TokenType::and_Inst:      return 0b000101;
    case TokenType::or_Inst:       return 0b000110;
    case TokenType::xor_Inst:      return 0b000111;
    case TokenType::not_Inst:      return 0b001000;
    case TokenType::nor_Inst:      return 0b001001;
    case TokenType::sllv_Inst:     return 0b001010;
    case TokenType::srav_Inst:     return 0b001011;
    case TokenType::movI_Inst:     return 0b001100;
    case TokenType::addI_Inst:     return 0b001101;
    case TokenType::subI_Inst:     return 0b001110;
    case TokenType::multI_Inst:    return 0b001111;
    case TokenType::divI_Inst:     return 0b010000;
    case TokenType::andI_Inst:     return 0b010001;
    case TokenType::orI_Inst:      return 0b010010;
    case TokenType::xorI_Inst:     return 0b010011;
    case TokenType::notI_Inst:     return 0b010100;
    case TokenType::norI_Inst:     return 0b010101;
    case TokenType::sll_Inst:      return 0b010110;
    case TokenType::sra_Inst:      return 0b010111;
    case TokenType::bEq_Inst:      return 0b011000;
    case TokenType::bNe_Inst:      return 0b011001;
    case TokenType::bLt_Inst:      return 0b011010;
    case TokenType::bGt_Inst:      return 0b011011;
    case TokenType::bLTz_Inst:     return 0b011100;
    case TokenType::bGTz_Inst:     return 0b011101;
    case TokenType::jmp_Inst:      return 0b011110;
    case TokenType::jmpL_Inst:     return 0b011111;
    case TokenType::jmpL_Reg_Inst: return 0b100000;
    case TokenType::jmpRet_Inst:   return 0b100001;
    case TokenType::lb_Inst:       return 0b100010;
    case TokenType::lw_Inst:       return 0b100011;
    case TokenType::sb_Inst:       return 0b100100;
    case TokenType::sw_Inst:       return 0b100101;
    case TokenType::halt_Inst:     return 0b100110;
    case TokenType::label_Inst:    return 0b100111;
    default:
        throw std::runtime_error("Unable to match the token type to an opcode");
    }
}

uint8_t Assembler::assembleRegister(const Token& reg) const {
    switch (reg.type) {
    case TokenType::r0_Reg:   return 0b00000;
    case TokenType::r1_Reg:   return 0b00001;
    case TokenType::r2_Reg:   return 0b00010;
    case TokenType::r3_Reg:   return 0b00011;
    case TokenType::r4_Reg:   return 0b00100;
    case TokenType::r5_Reg:   return 0b00101;
    case TokenType::r6_Reg:   return 0b00110;
    case TokenType::r7_Reg:   return 0b00111;
    case TokenType::r8_Reg:   return 0b01000;
    case TokenType::r9_Reg:   return 0b01001;
    case TokenType::r10_Reg:  return 0b01010;
    case TokenType::r11_Reg:  return 0b01011;
    case TokenType::r12_Reg:  return 0b01100;
    case TokenType::r13_Reg:  return 0b01101;
    case TokenType::r14_Reg:  return 0b01110;
    case TokenType::r15_Reg:  return 0b01111;
    case TokenType::r16_Reg:  return 0b10000;
    case TokenType::r17_Reg:  return 0b10001;
    case TokenType::r18_Reg:  return 0b10010;
    case TokenType::r19_Reg:  return 0b10011;
    case TokenType::r20_Reg:  return 0b10100;
    case TokenType::r21_Reg:  return 0b10101;
    case TokenType::r22_Reg:  return 0b10110;
    case TokenType::r23_Reg:  return 0b10111;
    case TokenType::r24_Reg:  return 0b11000;
    case TokenType::r25_Reg:  return 0b11001;
    case TokenType::rSP_Reg:  return 0b11010;
    case TokenType::rFP_Reg:  return 0b11011;
    case TokenType::rRET_Reg: return 0b11100;
    case TokenType::rHI_Reg:  return 0b11101;
    case TokenType::rLO_Reg:  return 0b11110;
    case TokenType::rIP_Reg:  return 0b11111;
    default:
        throw std::runtime_error("Unable to match the token type as a register");
    }
}

void Assembler::findLabelAddresses(std::queue<std::unique_ptr<Inst>>& allInsts) {
    size_t originalSize = allInsts.size();
    uint8_t addressCounter = 0;
    while (originalSize > 0) {
        unique_ptr<Inst> inst = std::move(allInsts.front());
        allInsts.pop();

        if (inst->getOpcode().type == TokenType::label_Inst) {
            Label* labelInst = static_cast<Label*>(inst.get());
            Token labelToken = labelInst->getLabel();

            labelAddresses[labelToken.lexeme] = addressCounter;
            addressCounter += 4;
        }

        allInsts.push(std::move(inst));
        originalSize--;
    }
}

AssembledInst Assembler::visit(const ArithLog& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const Shift& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const ShiftV& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const ArithLogI& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const Branch& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const BranchZ& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const LoadStore& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const Jump& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const JumpR& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const Move& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const MoveI& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}

AssembledInst Assembler::visit(const Label& inst) const {
	return AssembledInst(0x01, 0x01, 0x01, 0x01);
}