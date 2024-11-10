#pragma once

#include "Assembler/Inst.h"

#include <string>
#include <exception>
#include <memory>
#include <queue>
#include <unordered_map>

class Assembler : public InstVisitor {
private:
	std::unordered_map<std::string, uint32_t> labelAddresses;
	uint32_t currentAddress = 0;

	std::string readProgramFromFile(const std::string& filePath);
	void writeAssembledProgramToFile(const std::string& filePath, std::queue<AssembledInst>& assembledInsts) const ;
	uint8_t assembleOpcode(const Token& opcode) const;
	uint8_t assembleRegister(const Token& reg) const;
	void findLabelAddresses(std::queue<std::unique_ptr<Inst>>& allInsts);
	std::string uint8ToHexString(uint8_t byte) const ;

public:
	void assembleFile(const std::string& inputFilePath, const std::string& outputFilePath);
	AssembledInst visit(const ArithLog& inst) const override;
	AssembledInst visit(const ArithLogI& inst) const override;
	AssembledInst visit(const Branch& inst) const override;
	AssembledInst visit(const BranchZ& inst) const override;
	AssembledInst visit(const LoadStore& inst) const override;
	AssembledInst visit(const Jump& inst) const override;
	AssembledInst visit(const JumpR& inst) const override;
	AssembledInst visit(const Move& inst) const override;
	AssembledInst visit(const MoveI& inst) const override;
	AssembledInst visit(const Label& inst) const override;
	AssembledInst visit(const Trap& inst) const override;
};

class UnableToReadFromFileException : public std::exception
{
private:
	std::string filePath;
public:
	UnableToReadFromFileException(std::string const& filePath) :
		filePath(filePath) {}

	virtual const char* what() const throw() {
		return filePath.c_str();
	}
};