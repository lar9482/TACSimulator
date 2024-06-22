#pragma once

#include <string>
#include <exception>
#include <memory>
#include <queue>
#include <unordered_map>
#include "../Assembler/Inst.h"

class Assembler : public InstVisitor {
private:
	std::unordered_map<std::string, uint8_t> labelAddresses;

	std::string readProgramFromFile(const std::string& filePath);
	uint8_t assembleOpcode(const Token& opcode) const;
	uint8_t assembleRegister(const Token& reg) const;
	void findLabelAddresses(std::queue<std::unique_ptr<Inst>>& allInsts);
public:
	void assembleFile(const std::string& filePath);
	AssembledInst visit(const ArithLog& inst) const override;
	AssembledInst visit(const Shift& inst) const override;
	AssembledInst visit(const ShiftV& inst) const override;
	AssembledInst visit(const ArithLogI& inst) const override;
	AssembledInst visit(const Branch& inst) const override;
	AssembledInst visit(const BranchZ& inst) const override;
	AssembledInst visit(const LoadStore& inst) const override;
	AssembledInst visit(const Jump& inst) const override;
	AssembledInst visit(const JumpR& inst) const override;
	AssembledInst visit(const Move& inst) const override;
	AssembledInst visit(const MoveI& inst) const override;
	AssembledInst visit(const Label& inst) const override;
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