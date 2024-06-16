#pragma once

#include "../Inst.h"
#include "../../Token.h"

class ArithLog : public Inst {

public:
    Token opcode;
    Token reg1;
    Token reg2;
    Token reg3;

    ArithLog(Token opcode, Token reg1, Token reg2, Token reg3);
    AssembledInst assembleInst() const override;
};