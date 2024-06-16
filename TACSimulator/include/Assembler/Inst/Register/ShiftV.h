#pragma once

#include "../Inst.h"
#include "../../Token.h"

class ShiftV : public Inst {
    Token opcode;
    Token reg1;
    Token reg2;
    Token reg3;

public:
    ShiftV(Token opcode, Token reg1, Token reg2, Token reg3);
    AssembledInst assembleInst() const override;
};