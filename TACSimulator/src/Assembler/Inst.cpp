#include "../Assembler/Inst.h"
#include "../Assembler/Token.h"

ArithLogI::ArithLogI(Token& opcode, Token& reg1, Token& reg2, Token& integer) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    integer(integer) {}

AssembledInst ArithLogI::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Branch::Branch(Token& opcode, Token& reg1, Token& reg2, Token& label) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    label(label) 
{}

AssembledInst Branch::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

BranchZ::BranchZ(Token& opcode, Token& reg, Token& label) :
    Inst(opcode),
    reg(reg),
    label(label)
{}

AssembledInst BranchZ::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

LoadStore::LoadStore(Token& opcode, Token& reg1, Token& offset, Token& reg2) :
    Inst(opcode),
    reg1(reg1),
    offset(offset),
    reg2(reg2)
{}

AssembledInst LoadStore::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Jump::Jump(Token& opcode, Token& label) :
    Inst(opcode),
    label(label)
{}

AssembledInst Jump::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

JumpR::JumpR(Token& opcode, Token& reg) :
    Inst(opcode),
    reg(reg)
{}

AssembledInst JumpR::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Move::Move(Token& opcode, Token& reg1, Token& reg2) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2)
{}

AssembledInst Move::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

MoveI::MoveI(Token& opcode, Token& reg, Token& integer) :
    Inst(opcode),
    reg(reg),
    integer(integer)
{}

AssembledInst MoveI::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

ArithLog::ArithLog(Token& opcode, Token& reg1, Token& reg2, Token& reg3) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    reg3(reg3)
{}

AssembledInst ArithLog::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Shift::Shift(Token& opcode, Token& reg1, Token& reg2, Token& integer) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    integer(integer)
{}

AssembledInst Shift::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

ShiftV::ShiftV(Token& opcode, Token& reg1, Token& reg2, Token& reg3) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    reg3(reg3)
{}

AssembledInst ShiftV::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Label::Label(Token& opcode, Token& label) :
    Inst(opcode),
    label(label)
{}

AssembledInst Label::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}

Trap::Trap(Token& opcode, Token& trapCode) :
    Inst(opcode),
    trapCode(trapCode)
{}

AssembledInst Trap::assembleInst(const InstVisitor& visitor) const {
    return visitor.visit(*this);
}