#include "../Assembler/Inst.h"
#include "../Assembler/Token.h"

ArithLogI::ArithLogI(const Token& opcode, const Token& reg1, const Token& reg2, const Token& integer) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    integer(integer) {}

AssembledInst ArithLogI::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Branch::Branch(const Token& opcode, const Token& reg1, const Token& reg2, const Token& label) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    label(label) 
{}

AssembledInst Branch::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

BranchZ::BranchZ(const Token& opcode, const Token& reg, const Token& label) :
    Inst(opcode),
    reg(reg),
    label(label)
{}

AssembledInst BranchZ::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

LoadStore::LoadStore(const Token& opcode, const Token& reg1, const Token& offset, const Token& reg2) :
    Inst(opcode),
    reg1(reg1),
    offset(offset),
    reg2(reg2)
{}

AssembledInst LoadStore::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Jump::Jump(const Token& opcode, const Token& label) :
    Inst(opcode),
    label(label)
{}

AssembledInst Jump::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

JumpR::JumpR(const Token& opcode, const Token& reg) :
    Inst(opcode),
    reg(reg)
{}

AssembledInst JumpR::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Move::Move(const Token& opcode, const Token& reg1, const Token& reg2) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2)
{}

AssembledInst Move::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

MoveI::MoveI(const Token& opcode, const Token& reg, const Token& integer) :
    Inst(opcode),
    reg(reg),
    integer(integer)
{}

AssembledInst MoveI::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

ArithLog::ArithLog(const Token& opcode, const Token& reg1, const Token& reg2, const Token& reg3) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    reg3(reg3)
{}

AssembledInst ArithLog::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Shift::Shift(const Token& opcode, const Token& reg1, const Token& reg2, const Token& integer) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    integer(integer)
{}

AssembledInst Shift::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

ShiftV::ShiftV(const Token& opcode, const Token& reg1, const Token& reg2, const Token& reg3) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    reg3(reg3)
{}

AssembledInst ShiftV::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Label::Label(const Token& opcode, const Token& label) :
    Inst(opcode),
    label(label)
{}

AssembledInst Label::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Trap::Trap(const Token& opcode, const Token& trapCode) :
    Inst(opcode),
    trapCode(trapCode)
{}

AssembledInst Trap::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}