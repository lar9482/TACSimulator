#pragma once
#include <memory>
struct AssembledInst {
public:
	unsigned char byte1;
	unsigned char byte2;
	unsigned char byte3;
	unsigned char byte4;

	AssembledInst(unsigned char& byte1, unsigned char& byte2,
		unsigned char& byte3, unsigned char& byte4
	) : byte1(byte1), byte2(byte2),
		byte3(byte3), byte4(byte4) {}

	AssembledInst(unsigned char &&byte1, unsigned char &&byte2, 
		unsigned char &&byte3, unsigned char &&byte4
	) : byte1(byte1), byte2(byte2), 
		byte3(byte3), byte4(byte4) {}
};

class Inst {
public:
	virtual AssembledInst assembleInst() const = 0;
	virtual ~Inst() = default;
};