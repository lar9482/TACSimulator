#pragma once
#include "../Inst.h"
#include "../../Token.h"

class DivMult : public Inst {
    Token opcode;
    Token reg1;
    Token reg2;

public:
    DivMult(Token opcode, Token reg1, Token reg2);
    AssembledInst assembleInst() const override;
};