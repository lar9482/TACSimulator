#include "../Assembler/Inst/JInst.h"

JInst::JInst() {}

AssembledInst JInst::assembleInst() const {
	AssembledInst inst(0x01, 0x01, 0x01, 0x01);
	return inst;
}