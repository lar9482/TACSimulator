#pragma once

#include <memory>
#include "../Assembler/Token.h"

/*
 * This will ultimately be assembled as follows:
 * 11111111 22222222 33333333 44444444
 *
 * where byte1 represents the most significant byte,
 * and byte4 represents the least significant byte.
 */
struct AssembledInst {
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;
	uint8_t byte4;

	AssembledInst(const uint8_t& byte1, const uint8_t& byte2,
		const uint8_t& byte3, const uint8_t& byte4
	) : byte1(byte1), byte2(byte2),
		byte3(byte3), byte4(byte4) {}
};

class ArithLog;
class Shift;
class ShiftV;
class ArithLogI;
class Branch;
class BranchZ;
class LoadStore;
class Jump;
class JumpR;
class Move;
class MoveI;
class Label;
class Trap;

class InstVisitor {
protected:
	InstVisitor() = default;
	InstVisitor(const InstVisitor&) = default;
	InstVisitor& operator=(const InstVisitor&) = default;
	InstVisitor(InstVisitor&&) = default;
	InstVisitor& operator=(InstVisitor&&) = default;

public:
	virtual AssembledInst visit(const ArithLog& inst) const = 0;
	virtual AssembledInst visit(const Shift& inst) const = 0;
	virtual AssembledInst visit(const ShiftV& inst) const = 0;
	virtual AssembledInst visit(const ArithLogI& inst) const = 0;
	virtual AssembledInst visit(const Branch& inst) const = 0;
	virtual AssembledInst visit(const BranchZ& inst) const = 0;
	virtual AssembledInst visit(const LoadStore& inst) const = 0;
	virtual AssembledInst visit(const Jump& inst) const = 0;
	virtual AssembledInst visit(const JumpR& inst) const = 0;
	virtual AssembledInst visit(const Move& inst) const = 0;
	virtual AssembledInst visit(const MoveI& inst) const = 0;
	virtual AssembledInst visit(const Label& inst) const = 0;
	virtual AssembledInst visit(const Trap& inst) const = 0;
	virtual ~InstVisitor() = default;
};

class Inst {
private:
	Token opcode;

protected:

	Inst(Token& opcode)
		: opcode(opcode)
	{}
	Inst(const Inst&) = default;
	Inst& operator=(const Inst&) = default;
	Inst(Inst&&) = default;
	Inst& operator=(Inst&&) = default;

public:
	virtual std::unique_ptr<Inst> clone() const = 0;
	virtual AssembledInst assembleInst(const InstVisitor& visitor) const = 0;
	virtual ~Inst() = default;

	Token getOpcode() const { return opcode; }
};

class ArithLogI : public Inst {

private:
	Token reg1;
	Token reg2;
	Token integer;

public:
	ArithLogI(Token& opcode, Token& reg1, Token& reg2, Token& integer);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<ArithLogI>(*this);
	}

	Token getReg1() const { return reg1; }
	Token getReg2() const { return reg2;}
	Token getInteger() const { return integer; }
};

class Branch : public Inst {
private:
	Token reg1;
	Token reg2;
	Token label;

public:
	Branch(Token& opcode, Token& reg1, Token& reg2, Token& label);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<Branch>(*this);
	}

	Token getReg1() const { return reg1; }
	Token getReg2() const { return reg2; }
	Token getLabel() const { return label; }
};

class BranchZ : public Inst {
private:
	Token reg;
	Token label;

public:
	BranchZ(Token& opcode, Token& reg, Token& label);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<BranchZ>(*this);
	}

	Token getReg() const { return reg; }
	Token getLabel() const { return label; }
};

class LoadStore : public Inst {
private:
	Token reg1;
	Token offset;
	Token reg2;

public:
	LoadStore(Token& opcode, Token& reg1, Token& offset, Token& reg2);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<LoadStore>(*this);
	}

	Token getReg1() const { return reg1; }
	Token getReg2() const { return reg2; }
	Token getOffset() const { return offset; }
};

class Jump : public Inst {
private:
	Token label;

public:
	Jump(Token& opcode, Token& label);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<Jump>(*this);
	}
	Token getLabel() const { return label; }
};

class JumpR : public Inst {
private:
	Token reg;

public:
	JumpR(Token& opcode, Token& reg);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<JumpR>(*this);
	}

	Token getReg() const { return reg; }
};

class Move : public Inst {
private:
	Token reg1;
	Token reg2;

public:
	Move(Token& opcode, Token& reg1, Token& reg2);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;
	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<Move>(*this);
	}

	Token getReg1() const { return reg1; }
	Token getReg2() const { return reg2; }
};

class MoveI : public Inst {
private:
	Token reg;
	Token integer;

public:
	MoveI(Token& opcode, Token& reg, Token& integer);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;
	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<MoveI>(*this);
	}
	Token getReg() const { return reg; }
	Token getInteger() const { return integer; }
};

class ArithLog : public Inst {

private:
	Token reg1;
	Token reg2;
	Token reg3;

public:
	ArithLog(Token& opcode, Token& reg1, Token& reg2, Token& reg3);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<ArithLog>(*this);
	}

	Token getReg1() const { return reg1; }
	Token getReg2() const { return reg2; }
	Token getReg3() const { return reg3; }
};

class Shift : public Inst {
private:
	Token reg1;
	Token reg2;
	Token integer;

public:
	Shift(Token& opcode, Token& reg1, Token& reg2, Token& integer);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<Shift>(*this);
	}

	Token getReg1() const { return reg1; }
	Token getReg2() const { return reg2; }
	Token getInteger() const { return integer; }
};

class ShiftV : public Inst {
private:
	Token reg1;
	Token reg2;
	Token reg3;

public:
	ShiftV(Token& opcode, Token& reg1, Token& reg2, Token& reg3);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<ShiftV>(*this);
	}

	Token getReg1() const { return reg1; }
	Token getReg2() const { return reg2; }
	Token getReg3() const { return reg3; }
};

class Label : public Inst {
private:
	Token label;

public:
	Label(Token& opcode, Token& label);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<Label>(*this);
	}

	Token getLabel() const { return label; }
};

class Trap : public Inst {
private:
	Token trapCode;
public:
	Trap(Token& opcode, Token& trapCode);
	AssembledInst assembleInst(const InstVisitor& visitor) const override;

	std::unique_ptr<Inst> clone() const override {
		return std::make_unique<Trap>(*this);
	}

	Token getTrapCode() const { return trapCode; }
};