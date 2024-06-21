#pragma once

#include "Inst.h"
#include "../Assembler/Token.h"

class Label : public Inst {
private:
    Token label;

public:
    Label(Token& opcode, Token& label);
    AssembledInst assembleInst() const override;

    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<Label>(*this);
    }
};