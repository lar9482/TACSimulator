#pragma once
#include "Inst.h"

class JInst : public Inst {
public:
	JInst();
	~JInst() override = default;
	AssembledInst assembleInst() const override;
};