#pragma once
#include "../Memory/Memory.h"
#include "Register.h"
#include "Interrupts.h"

class CPU {
	public:
		//General purpose registers
		unsigned char A, B, C, D, E, H, L;
		FlagRegister F;
		Interrupts interrupts;

		Register16 AF, BC, DE, HL;

		unsigned char IF;
		unsigned short sp, pc;
		int cycles;

		bool halt;

		CPU(Memory& memory);
		int step();
		void run(int iterations);
		void reset();

		//Stack operation
		void push(Register16& reg);
		void push(unsigned short val);
		void pop(Register16& reg);
		void pop(unsigned short& val);

	private:
		Memory& memory;

		void executeOpcode(unsigned char opcode);
		unsigned char fetchOpcode();

		void loadByteIntoReg(unsigned char& dest, const unsigned char& src);
		void loadByteIntoRegDecrement(unsigned char& src, Register16& dest);
		void loadByteIntoRegIncrement(unsigned char& src, Register16& dest);

		void loadByteIntoMemory(const unsigned short& dest, const unsigned char& src);
		void loadByteIntoMemoryDecrement(Register16& dest, unsigned char& src);
		void loadByteIntoMemoryIncrement(Register16& dest, unsigned char& src);

		void loadShortIntoReg(unsigned char& reg1, unsigned char& reg2);
		void loadShortIntoReg(Register16& reg, const unsigned short& val);

		void loadShortIntoMemory(const unsigned short& address, const unsigned short& val);

		void loadRegIntoSP(Register16& reg);
		void loadHL(unsigned char val);

		void add(unsigned char& reg, const unsigned char val);
		void add(Register16& reg, const unsigned short val);
		void addCarry(unsigned char& reg, const unsigned char val);

		void addSP(char val);

		void sub(unsigned char& reg, const unsigned char val);
		void subBorrow(unsigned char& reg, const unsigned char val);

		void AND(unsigned char& reg, const unsigned char val);
		void OR(unsigned char& reg, const unsigned val);
		void XOR(unsigned char& reg, const unsigned val);
		void CP(unsigned char& reg, const unsigned char val);

		void INC(unsigned char& reg);
		void INC(Register16& reg);
		void INC(const unsigned short address);
	

		void DEC(unsigned char& reg);
		void DEC(Register16& reg);
		void DEC(const unsigned short address);
		

		void DAA(unsigned char& reg);
		void CPL(unsigned char& reg);
		void CCF();
		void SCF();

		void RLC(unsigned char& reg);
		void RL(unsigned char& reg);

		void RRC(unsigned char& reg);
		void RR(unsigned char& reg);

		void jump(unsigned short address);
		void jump(unsigned short address, bool condition);

		void jump(char val);
		void jump(char val, bool condition);

		void call(unsigned short address);
		void call(unsigned short address, bool condition);

		void restart(unsigned char val);

		void ret();
		void ret(bool condition);
		void reti();
};
