#pragma once

#include "../Inst.h"
#include "../../Token.h"

class Move : public Inst {
    Token opcode;
    Token reg1;
    Token reg2;

public:
    Move(Token opcode, Token reg1, Token reg2);
    AssembledInst assembleInst() const override;
};