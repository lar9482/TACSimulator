#include "../Assembler/Inst/RInst.h"

RInst::RInst() {}

AssembledInst RInst::assembleInst() const {
	AssembledInst inst(0x01, 0x01, 0x01, 0x01);
	return inst;
}