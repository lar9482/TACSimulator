#pragma once

#include "../Inst.h"
#include "../../Token.h"

class MoveI : public Inst {
private:
    Token reg;
    Token integer;

public:
    MoveI(Token& opcode, Token& reg, Token& integer);
    AssembledInst assembleInst() const override;
    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<MoveI>(*this);
    }
};