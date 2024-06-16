#pragma once

#include "../Inst.h"
#include "../../Token.h"

class Branch : public Inst {
private:
    Token opcode;
    Token reg1;
    Token reg2;
    Token label;

public:
    Branch(Token opcode, Token reg1, Token reg2, Token label);
    AssembledInst assembleInst() const override;

    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<Branch>(*this);
    }
};