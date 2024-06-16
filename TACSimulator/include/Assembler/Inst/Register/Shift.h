#pragma once

#include "../Inst.h"
#include "../../Token.h"

class Shift : public Inst {
    Token opcode;
    Token reg1;
    Token reg2;
    Token integer;

public:
    Shift(Token opcode, Token reg1, Token reg2, Token integer);
    AssembledInst assembleInst() const override;
};