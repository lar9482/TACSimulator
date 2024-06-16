#pragma once

#include "../Inst.h"
#include "../../Token.h"

class JumpR : public Inst {
private:
    Token opcode;
    Token reg;

public:
    JumpR(Token opcode, Token reg);
    AssembledInst assembleInst() const override;

    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<JumpR>(*this);
    }
};