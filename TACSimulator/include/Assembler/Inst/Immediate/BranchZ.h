#pragma once

#include "../Inst.h"
#include "../../Token.h"

class BranchZ : public Inst {
private:
    Token opcode;
    Token reg;
    Token label;

public:
    BranchZ(Token opcode, Token reg, Token label);
    AssembledInst assembleInst() const override;

    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<BranchZ>(*this);
    }
};