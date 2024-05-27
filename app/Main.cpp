#include <iostream>
#include "../src/GameBoy.h"
#include "../src/Cartridge/CartridgeFactory.h"

int main() {
	const char* tetris = "C:/Users/RedAP/Desktop/Tetris.gb";
	const char* specialTest = "C:/Users/RedAP/Desktop/01-special.gb";
	const char* opSPTest = "C:/Users/RedAP/Downloads/03-op sp,hl.gb";
	const char* opRTest = "C:/Users/RedAP/Downloads/04-op r,imm.gb";
	const char* op5Test = "C:/Users/RedAP/Downloads/05-op rp.gb";
	const char* loadTest = "C:/Users/RedAP/Downloads/06-ld r,r.gb";
	const char* jumpTest = "C:/Users/RedAP/Downloads/07-jr,jp,call,ret,rst.gb";
	const char* miscTest = "C:/Users/RedAP/Downloads/08-misc instrs.gb";
	const char* opRRTest = "C:/Users/RedAP/Downloads/09-op r,r.gb";

	//Creates Cartridge
	CartridgeFactory* cartridgeFactory = CartridgeFactory::getInstance();
	Cartridge* cartridge = cartridgeFactory->createCartridge(opRRTest);

	Memory* memory = new Memory(*cartridge);
	CPU* mCPU = new CPU(*memory);
	mCPU->run();

	delete cartridge;
	delete memory;
	delete mCPU;
	return 0;
}