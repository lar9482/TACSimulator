#pragma once

#include "../Inst.h"
#include "../../Token.h"

class ShiftV : public Inst {
private:
    Token reg1;
    Token reg2;
    Token reg3;

public:
    ShiftV(Token& opcode, Token& reg1, Token& reg2, Token& reg3);
    AssembledInst assembleInst() const override;

    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<ShiftV>(*this);
    }
};