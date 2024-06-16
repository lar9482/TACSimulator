#pragma once
#include "../Inst.h"
#include "../../Token.h"

class DivMult : public Inst {
private:
    Token opcode;
    Token reg1;
    Token reg2;

public:
    DivMult(Token opcode, Token reg1, Token reg2);
    AssembledInst assembleInst() const override;

    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<DivMult>(*this);
    }
};