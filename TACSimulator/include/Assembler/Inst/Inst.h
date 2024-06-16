#pragma once

#include <memory>

struct AssembledInst {
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
protected:
	Inst() = default;
	Inst(const Inst&) = default;
	Inst& operator=(const Inst&) = default;
	Inst(Inst&&) = default;
	Inst& operator=(Inst&&) = default;
public:
	virtual std::unique_ptr<Inst> clone() const = 0;
	virtual AssembledInst assembleInst() const = 0;
	virtual ~Inst() = default;
};