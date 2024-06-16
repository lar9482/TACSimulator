#pragma once

#include "../Inst.h"
#include "../../Token.h"

class MoveI : public Inst {
    Token opcode;
    Token reg1;
    Token integer;

public:
    MoveI(Token opcode, Token reg1, Token integer);
    AssembledInst assembleInst() const override;
};