#pragma once

#include "../Inst.h"
#include "../../Token.h"

class ArithLogI : public Inst {
    Token opcode;
    Token reg1;
    Token reg2;
    Token integer;

public:
    ArithLogI(Token opcode, Token reg1, Token reg2, Token integer);
    AssembledInst assembleInst() const override;
};