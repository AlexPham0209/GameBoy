#include "Memory.h"

Memory::Memory(Cartridge& cartridge) : cartridge(cartridge) {
	clear();
}


void Memory::loadProgram(std::vector<unsigned char> rom) {
	for (int i = 0; i < rom.size(); ++i) {
		this->writeByte(0x100 + i, rom[i]);
		std::cout << std::hex << (int)readByte(0x100 + i) << std::endl;
	}
}

//Reads byte value at address
unsigned char Memory::readByte(unsigned short address) {
	if (address <= 0x7FFF)
		return cartridge.readByte(address);

	if (address >= 0xA000 && address <= 0xBFFF)
		return cartridge.readByte(address);

	//Invalid region 
	if (address >= 0x7EA0 && address <= 0x7EFF)
		return NULL;

	//Echo RAM region
	if (address >= 0xE000 && address <= 0xFDFF)
		return this->ram[address - 0x2000];

	return this->ram[address];
}

//Reads byte values inside address i and address i + 1 then merges them into a short (little endian)
unsigned short Memory::readShort(unsigned short address) {
	return readByte(address) | (readByte(address + 1) << 8);
}

//Writes byte value into memory address
unsigned char Memory::writeByte(unsigned short address, unsigned char val) {
	if (address == 0xFF02 && val == 0x81)
		std::cout << readByte(0xFF01);


	if (address <= 0x7FFF)
		return NULL;

	//Invalid region 
	if (address >= 0x7EA0 && address <= 0x7EFF)
		return NULL;

	//Echo RAM region
	if (address >= 0xE000 && address <= 0xFDFF) {
		unsigned char temp = this->ram[address - 0x2000];
		this->ram[address - 0x2000] = val;
		return temp;
	}

	//External RAM
	if (address >= 0xA000 && address <= 0xBFFF)
		return cartridge.writeShort(address, val);

	unsigned char temp = this->ram[address];
	this->ram[address] = val;
	return temp;
}

//Writes short value into memory address i and i + 1 (little endian)
unsigned short Memory::writeShort(unsigned short address, unsigned short val) {
	unsigned short temp = readByte(address) | readByte(address + 1) << 8;
	this->ram[address] = val & 0x00FF;
	this->ram[address + 1] = (val & 0xFF00) >> 8;
	return temp;
}

//Clears all memory
void Memory::clear() {
	memset(&ram, 0x0000, sizeof(ram));
}