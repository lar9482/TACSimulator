#pragma once
#include "Inst.h"

class IInst : public Inst {
public:
	IInst();
	~IInst() override = default;
	AssembledInst assembleInst() const override;
};