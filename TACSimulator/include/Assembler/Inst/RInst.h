#pragma once
#include "Inst.h"

class RInst : public Inst {
public:
	RInst();
	~RInst() override = default;
	AssembledInst assembleInst() const override;
};