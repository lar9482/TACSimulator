#pragma once

#include "../Inst.h"
#include "../../Token.h"

class Shift : public Inst {
private:
    Token opcode;
    Token reg1;
    Token reg2;
    Token integer;

public:
    Shift(Token opcode, Token reg1, Token reg2, Token integer);
    AssembledInst assembleInst() const override;

    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<Shift>(*this);
    }
};