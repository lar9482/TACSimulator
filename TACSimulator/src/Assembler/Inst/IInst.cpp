#include "../Assembler/Inst/IInst.h"

IInst::IInst() {}

AssembledInst IInst::assembleInst() const {
	AssembledInst inst(0x01, 0x01, 0x01, 0x01);
	return inst;
}