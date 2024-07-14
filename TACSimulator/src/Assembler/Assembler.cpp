#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <memory>
#include <iomanip>
#include <iostream>

#include "../Assembler/Assembler.h"
#include "../Assembler/Lexer.h"
#include "../Assembler/Parser.h"
#include "../Assembler/Inst.h"

using std::string;
using std::queue;
using std::unique_ptr;

void Assembler::assembleFile(const std::string& inputFilePath, const std::string& outputFilePath) {
	string program = readProgramFromFile(inputFilePath);
	
	Lexer lexer;
	queue<Token> tokenQueue = lexer.scanProgram(program);
	Parser parser(tokenQueue);
	queue<unique_ptr<Inst>> allInsts = parser.parseProgram();
    findLabelAddresses(allInsts);

    queue<AssembledInst> assembledInsts;
	while (allInsts.size() > 0) {
		Inst* inst = allInsts.front().get();
   		assembledInsts.push(inst->assembleInst(*this));

        currentAddress += 4;
        allInsts.pop();
	}
    writeAssembledProgramToFile(outputFilePath, assembledInsts);
}

string Assembler::readProgramFromFile(const string& inputFilePath) {
	std::ifstream file(inputFilePath);

	if (!file) {
		throw UnableToReadFromFileException(inputFilePath);
	}

	std::ostringstream ss;
	ss << file.rdbuf();

    file.close();
	return ss.str();
}

void Assembler::writeAssembledProgramToFile(const std::string& outputFilePath, queue<AssembledInst>& assembledInsts) const {

    string programContent;
    while (assembledInsts.size() > 0) {
        AssembledInst inst = assembledInsts.front();

        programContent += uint8ToHexString(inst.byte1);
        programContent += uint8ToHexString(inst.byte2);
        programContent += uint8ToHexString(inst.byte3);
        programContent += uint8ToHexString(inst.byte4);
        programContent += "\n";

        assembledInsts.pop();
    }

    std::ofstream outFile(outputFilePath);
    if (!outFile) {
        std::cerr << "Failed to open the file:" << outputFilePath << std::endl;
    }

    outFile << programContent;
    outFile.close();
}

std::string Assembler::uint8ToHexString(uint8_t byte) const {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    return ss.str();
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
    case TokenType::jmpReg_Inst:   return 0b100001;
    case TokenType::lb_Inst:       return 0b100010;
    case TokenType::lw_Inst:       return 0b100011;
    case TokenType::sb_Inst:       return 0b100100;
    case TokenType::sw_Inst:       return 0b100101;
    case TokenType::trap_Inst:     return 0b100110;
    case TokenType::label_Inst:    return 0b100111;
    default:
        throw std::runtime_error("Unable to match the token type to an opcode");
    }
}

uint8_t Assembler::assembleRegister(const Token& reg) const {
    switch (reg.type) {
    case TokenType::r0_Reg:    return 0b00000;
    case TokenType::r1_Reg:    return 0b00001;
    case TokenType::r2_Reg:    return 0b00010;
    case TokenType::r3_Reg:    return 0b00011;
    case TokenType::r4_Reg:    return 0b00100;
    case TokenType::r5_Reg:    return 0b00101;
    case TokenType::r6_Reg:    return 0b00110;
    case TokenType::r7_Reg:    return 0b00111;
    case TokenType::r8_Reg:    return 0b01000;
    case TokenType::r9_Reg:    return 0b01001;
    case TokenType::r10_Reg:   return 0b01010;
    case TokenType::r11_Reg:   return 0b01011;
    case TokenType::r12_Reg:   return 0b01100;
    case TokenType::r13_Reg:   return 0b01101;
    case TokenType::r14_Reg:   return 0b01110;
    case TokenType::r15_Reg:   return 0b01111;
    case TokenType::r16_Reg:   return 0b10000;
    case TokenType::r17_Reg:   return 0b10001;
    case TokenType::r18_Reg:   return 0b10010;
    case TokenType::r19_Reg:   return 0b10011;
    case TokenType::r20_Reg:   return 0b10100;
    case TokenType::r21_Reg:   return 0b10101;
    case TokenType::r22_Reg:   return 0b10110;
    case TokenType::r23_Reg:   return 0b10111;
    case TokenType::r24_Reg:   return 0b11000;
    case TokenType::r25_Reg:   return 0b11001;
    case TokenType::r26_Reg:   return 0b11010;
    case TokenType::rT_Reg:    return 0b11011;
    case TokenType::rSP_Reg:   return 0b11100;
    case TokenType::rFP_Reg:   return 0b11101;
    case TokenType::rRET_Reg:  return 0b11110;
    case TokenType::rIP_Reg:   return 0b11111;
    default:
        throw std::runtime_error("Unable to match the token type as a register");
    }
}

void Assembler::findLabelAddresses(std::queue<std::unique_ptr<Inst>>& allInsts) {
    size_t originalSize = allInsts.size();
    uint32_t addressCounter = 0;
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

/*
 * Form: ooooooss sssttttt ddddd000 00000000
 * o: opcode
 * s: first register,
 * t: second register,
 * d: third register
 */
AssembledInst Assembler::visit(const ArithLog& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    uint8_t reg1 = assembleRegister(inst.getReg1());
    uint8_t reg2 = assembleRegister(inst.getReg2());
    uint8_t reg3 = assembleRegister(inst.getReg3());

	return AssembledInst(
        (opcode << 2) + ((reg1 & 0b11000) >> 3),
        ((reg1 & 0b00111) << 5) + reg2,
        reg3 << 3, 
        0b00000000
    );
}

/*
 * Form: ooooooss sssttttt Maaaaaaa aaaaaaaa
 * o: opcode
 * s: first register,
 * t: second register
 * M: Sign of a. 0 is positive, 1 is negative
 * a: Shift amount
 */
AssembledInst Assembler::visit(const Shift& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    uint8_t reg1 = assembleRegister(inst.getReg1());
    uint8_t reg2 = assembleRegister(inst.getReg2());
    int rawShift = std::stoi(inst.getInteger().lexeme);

    if (rawShift < -32768 || rawShift > 32768) {
        throw std::runtime_error(rawShift + " can't be assembled using 15 bits.");
    }
    
    uint8_t sign = (rawShift > 0) ? 0 : 1;
    uint32_t shift = (rawShift > 0) ? rawShift : -rawShift;

	return AssembledInst(
        (opcode << 2) + ((reg1 & 0b11000) >> 3),
        ((reg1 & 0b00111) << 5) + reg2,
        (sign << 7) + ((shift & 0b1111111'00000000) >> 8),
        shift & 0b0000000'11111111
    );
}

 /*
  * Form: ooooooss sssttttt ddddd000 00000000
  * o: opcode
  * s: first register,
  * t: second register,
  * d: third register
  */
AssembledInst Assembler::visit(const ShiftV& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    uint8_t reg1 = assembleRegister(inst.getReg1());
    uint8_t reg2 = assembleRegister(inst.getReg2());
    uint8_t reg3 = assembleRegister(inst.getReg3());

    return AssembledInst(
        (opcode << 2) + ((reg1 & 0b11000) >> 3),
        ((reg1 & 0b00111) << 5) + reg2,
        reg3 << 3,
        0b00000000
    );
}

/*
 * Form: ooooooss sssttttt Miiiiiii iiiiiiii
 * o: opcode
 * s: first register,
 * t: second register
 * M: Sign of i. 0 is positive, 1 is negative
 * i: Immediate amount
 */
AssembledInst Assembler::visit(const ArithLogI& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    uint8_t reg1 = assembleRegister(inst.getReg1());
    uint8_t reg2 = assembleRegister(inst.getReg2());
    int rawInteger = std::stoi(inst.getInteger().lexeme);

    if (rawInteger < -32768 || rawInteger > 32768) {
        throw std::runtime_error(rawInteger + " can't be assembled using 15 bits.");
    }

    uint8_t sign = (rawInteger > 0) ? 0 : 1;
    uint32_t integer = (rawInteger > 0) ? rawInteger : -rawInteger;

    return AssembledInst(
        (opcode << 2) + ((reg1 & 0b11000) >> 3),
        ((reg1 & 0b00111) << 5) + reg2,
        (sign << 7) + ((integer & 0b1111111'00000000) >> 8),
        integer & 0b0000000'11111111
    );
}

/*
 * Form: ooooooss sssttttt Miiiiiii iiiiiiii
 * o: opcode
 * s: first register,
 * t: second register,
 * M: sign of i
 * i: (label - (current + 4)) >> 2
 */
AssembledInst Assembler::visit(const Branch& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    uint8_t reg1 = assembleRegister(inst.getReg1());
    uint8_t reg2 = assembleRegister(inst.getReg2());

    uint32_t label;
    auto it = labelAddresses.find(inst.getLabel().lexeme);
    if (it != labelAddresses.end()) {
        label = it->second;
    } else {
        throw std::runtime_error(inst.getLabel().lexeme + " doesn't exist as a label");
    }

    int rawJumpOffset = (label - (currentAddress + 4)) >> 2;
    uint8_t sign = rawJumpOffset > 0 ? 0 : 1;
    uint32_t jumpOffset = rawJumpOffset > 0 ? rawJumpOffset : -rawJumpOffset;

	return AssembledInst(
        (opcode << 2) + ((reg1 & 0b11000) >> 3),
        ((reg1 & 0b00111) << 5) + reg2,
        (sign << 7) + ((jumpOffset & 0b1111111'00000000) >> 8),
        jumpOffset & 0b0000000'11111111
    );
}

/*
 * Form: ooooooss sss00000 Miiiiiii iiiiiiii
 * o: opcode
 * s: first register
 * M: sign of i
 * i: (label - (current + 4)) >> 2
 */
AssembledInst Assembler::visit(const BranchZ& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    uint8_t reg = assembleRegister(inst.getReg());

    uint32_t label;
    auto it = labelAddresses.find(inst.getLabel().lexeme);
    if (it != labelAddresses.end()) {
        label = it->second;
    }
    else {
        throw std::runtime_error(inst.getLabel().lexeme + " doesn't exist as a label");
    }

    int rawJumpOffset = (label - (currentAddress + 4)) >> 2;
    uint8_t sign = rawJumpOffset > 0 ? 0 : 1;
    uint32_t jumpOffset = rawJumpOffset > 0 ? rawJumpOffset : -rawJumpOffset;

    return AssembledInst(
        (opcode << 2) + ((reg & 0b11000) >> 3),
        ((reg & 0b00111) << 5),
        (sign << 7) + ((jumpOffset & 0b1111111'00000000) >> 8),
        jumpOffset & 0b0000000'11111111
    );
}

/*
 * Form: ooooooss sssttttt Miiiiiii iiiiiiii
 * o: opcode
 * s: first register,
 * t: second register,
 * M: sign of i
 * i: Memory offset
 */
AssembledInst Assembler::visit(const LoadStore& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    uint8_t reg1 = assembleRegister(inst.getReg1());
    uint8_t reg2 = assembleRegister(inst.getReg2());
    int rawOffset = std::stoi(inst.getOffset().lexeme);

    if (rawOffset < -32768 || rawOffset > 32768) {
        throw std::runtime_error(rawOffset + " can't be assembled using 15 bits.");
    }

    uint8_t sign = (rawOffset > 0) ? 0 : 1;
    uint32_t offset = (rawOffset > 0) ? rawOffset : -rawOffset;

    return AssembledInst(
        (opcode << 2) + ((reg1 & 0b11000) >> 3),
        ((reg1 & 0b00111) << 5) + reg2,
        (sign << 7) + ((offset & 0b1111111'00000000) >> 8),
        offset & 0b0000000'11111111
    );
}

/*
 * Form: oooooo00 00000000 Miiiiiii iiiiiiii
 * o: opcode
 * M: sign of i
 * i: (label - (current + 4)) >> 2 
 */
AssembledInst Assembler::visit(const Jump& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());

    uint32_t label;
    auto it = labelAddresses.find(inst.getLabel().lexeme);
    if (it != labelAddresses.end()) {
        label = it->second;
    }
    else {
        throw std::runtime_error(inst.getLabel().lexeme + " doesn't exist as a label");
    }

    int rawJumpOffset = (label - (currentAddress + 4)) >> 2;
    uint8_t sign = rawJumpOffset > 0 ? 0 : 1;
    uint32_t jumpOffset = rawJumpOffset > 0 ? rawJumpOffset : -rawJumpOffset;

    return AssembledInst(
        (opcode << 2),
        0b00000000,
        (sign << 7) + ((jumpOffset & 0b1111111'00000000) >> 8),
        jumpOffset & 0b0000000'11111111
    );
}

/*
 * Form: ooooooss sss00000 00000000 00000000
 * o: opcode
 * s: register
 */
AssembledInst Assembler::visit(const JumpR& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    uint8_t reg1 = assembleRegister(inst.getReg());

    return AssembledInst(
        (opcode << 2) + ((reg1 & 0b11000) >> 3),
        ((reg1 & 0b00111) << 5),
        0b00000000,
        0b00000000
    );
}

/*
 * Form: ooooooss sssttttt 00000000 00000000
 * o: opcode
 * s: register 1
 * t: register 2
 */
AssembledInst Assembler::visit(const Move& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    uint8_t reg1 = assembleRegister(inst.getReg1());
    uint8_t reg2 = assembleRegister(inst.getReg2());

	return AssembledInst(
        (opcode << 2) + ((reg1 & 0b11000) >> 3),
        ((reg1 & 0b00111) << 5) + reg2,
        0b00000000, 
        0b00000000
    );
}

/*
 * Form: ooooooss sss00000 Miiiiiii iiiiiiii
 * o: opcode
 * s: register
 * M: sign of M. 0 is positive, 1 is negative.
 * i: immediate
 */
AssembledInst Assembler::visit(const MoveI& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    uint8_t reg = assembleRegister(inst.getReg());
    int rawInteger = std::stoi(inst.getInteger().lexeme);

    //Testing if rawInteger is larger than 15 bits.
    if (rawInteger < -32768 || rawInteger > 32768) {
        throw std::runtime_error(rawInteger + " can't be assembled");
    }

    uint8_t sign = rawInteger > 0 ? 0 : 1;
    uint32_t integer = rawInteger > 0 ? rawInteger : -rawInteger;

	return AssembledInst(
        (opcode << 2) + ((reg & 0b11000) >> 3),
        ((reg & 0b00111) << 5),
        (sign << 7) + ((integer & 0b1111111'00000000) >> 8),
        integer & 0b0000000'11111111
    );
}

/*
 * Form: oooooo00 00000000 00000000 00000000
 * o: opcode
 */
AssembledInst Assembler::visit(const Label& inst) const {
    uint8_t labelOpcode = assembleOpcode(inst.getOpcode());
	return AssembledInst(labelOpcode << 2, 0b00000000, 0b00000000, 0b00000000);
}

/*
 * Form: oooooo00 00000000 00000000 iiiiiiii
 * o: opcode
 * i: Trapcode
 * 
 * i   Name               Input                            Output                         Description:
 * 0:  print_int          rT has int to print              -                              Print an int value to standard output in decimal.    
 * 1:  print_string       rT has ASCIIZ address to print   -                              Print an ASCIIZ string to standard output.
 * 2:  println_string     rT has ASCIIZ address to print   -                              Print an ASCIIZ string to standard output with a newline
 * 3:  read_int           -                                rT has int that has read       Reads an int value into rT
 * 4:  read_string        -                                rT has the starting address    Reads an ASCIIZ value, then placing the starting address into rT
 * 5:  malloc             -                                rT has the starting address    Allocates rT bytes on the heap
 * 6:  free               rT has the starting address      -                              Frees the bytes starting at rT
 * 7:  exit               -                                -                              Terminate the program
 */
AssembledInst Assembler::visit(const Trap& inst) const {
    uint8_t opcode = assembleOpcode(inst.getOpcode());
    int rawTrapcode = std::stoi(inst.getTrapCode().lexeme);

    if (rawTrapcode < 0|| rawTrapcode > 7) {
        throw std::runtime_error(rawTrapcode + " can't be assembled");
    }

    uint8_t trapcode = static_cast<uint8_t>(rawTrapcode);

    return AssembledInst(
        opcode << 2,
        0b0000'0000,
        0b0000'0000,
        trapcode
    );
}