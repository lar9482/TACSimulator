#pragma once

#include "../Inst.h"
#include "../../Token.h"

class LoadStore : public Inst {
private:
    Token opcode;
    Token reg1;
    Token offset;
    Token reg2;

public:
    LoadStore(Token opcode, Token reg1, Token offset, Token reg2);
    AssembledInst assembleInst() const override;

    std::unique_ptr<Inst> clone() const override {
        return std::make_unique<LoadStore>(*this);
    }
};