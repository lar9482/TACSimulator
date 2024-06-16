#pragma once

#include "../Inst.h"
#include "../../Token.h"

class Jump : public Inst {
private:
    Token opcode;
    Token label;

public:
    Jump(Token opcode, Token label);
    AssembledInst assembleInst() const override;

    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<Jump>(*this);
    }
};