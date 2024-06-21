#pragma once

#include "../Inst.h"
#include "../../Token.h"

class ArithLogI : public Inst {
private:
    Token reg1;
    Token reg2;
    Token integer;

public:
    ArithLogI(Token& opcode, Token& reg1, Token& reg2, Token& integer);
    AssembledInst assembleInst() const override;

    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<ArithLogI>(*this);
    }
};