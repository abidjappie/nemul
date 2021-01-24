#include <iostream>
#include <cstdint>
#include <string>
#include <sstream>
#include <fstream>
#include "Opcodes.h"
#include "Registers.h"

class Emulator {
	int step;
	int trigger = false;

	int stepNext() {
		trigger = true;
		return (step++);
	}
};

class Processor {
public:
	uint8_t readData(uint16_t address){
		if (address < ADD_PPU) {
			int location = (int)&CPU + (address - ADD_CPU);
			int data = *(uint8_t*)location;

			std::cout << "Reading from memory location " << std::hex << location << std::endl;
			std::cout << " Read: " << std::hex << data << std::endl;

			return data;
		}
		if (ADD_PPU < address < ADD_APU) {
			int location = (int)&CPU + (address - ADD_PPU);
			int data = *(uint8_t*)location;

			std::cout << "Reading from memory location " << std::hex << location << std::endl;
			std::cout << " Read: " << std::hex << data << std::endl;

			return data;
		}
	}

	void writeData(uint16_t address, uint8_t data) {
		int data_ = data;
		if (address < ADD_PPU) {
			int location = (int)&CPU + (address - ADD_CPU);

			std::cout << "Write to memory location " << std::hex << location << std::endl;
			std::cout << " Write: " << std::hex << data_ << std::endl;

			std::memcpy((void *)location, &data, 8);
		}
		if (ADD_PPU < address < ADD_APU) {
			int location = (int)&CPU + (address - ADD_PPU);

			std::cout << "Write to memory location " << std::hex << location << std::endl;
			std::cout << " Write: " << std::hex << data_ << std::endl;

			std::memcpy((void *)location, &data, 8);
		}
	}

	void process(uint32_t command) {
		std::cout << "Processing: " << std::endl;
		std::cout << " Command: " << std::hex << command << std::endl;
		std::cout << " Op Code: " << std::hex << (command&(0xFF)) << std::endl;

		if ((command&(0xFF)) == LDA) {
			std::cout << " LDA" << std::endl;
			uint16_t address = (command&0xFFFF00) >> 8;

			std::cout << " Address: " << std::hex << address << std::endl;
			CPU.AC = readData(address);
		}

		if ((command&(0xFF)) == STA) {
			std::cout << " STA" << std::endl;
			uint16_t address = (command&0xFFFF00) >> 8;
			uint8_t data = CPU.AC;

			std::cout << " Address: " << std::hex << address << std::endl;
			writeData(address, data);
		}
	}

	void next() {
		//Increase program counter
		CPU.PC += 0b1;
	}
};

class Parser {

	void loadFile(char* &filename, std::string dest[]) {
		std::string line;
		std::ifstream file(filename);

		if (file.is_open()) {
			int i = 0;
			while (std::getline(file, line))
			{
				dest[i] = line;
				i++;
			}
		}
		else std::cout << "Could not open file." << std::endl;

	}

	void parse(char* line, uint8_t *dest, int &writeIndex)
	{
		std::string command;
		std::stringstream ss;

		command = line;

		//Immediate
		//"0123456789"
		//" CMD #$AA "
		if (command.substr(5, 2) == "#$") {
			uint8_t add;
			ss << command.substr(7, 2);
			ss >> add;
			
			if (command.substr(1,3) == "LDA")	dest[writeIndex + 1] = LDA;
			if (command.substr(1, 3) == "STA")	dest[writeIndex + 1] = STA;

			dest[writeIndex + 2] = add;
			writeIndex += 2;
		}
		else //Zero Page
			 //"0123456789"
			 //" CMD $LL"
			if (command.substr(5, 1) == "$") {
				uint8_t add;
				ss << command.substr(6, 4);
				ss >> add;

				if (command.substr(1, 3) == "LDA")	dest[writeIndex + 1] = LDA_ZP;

				dest[writeIndex + 2] = add;
				writeIndex += 2;
			}
		else //Absolute
			 //"0123456789"
			 //" CMD $HHLL"
		if (command.substr(5, 1) == "$") {
			uint8_t add;
			ss << command.substr(6, 4);
			ss >> add;

			if (command.substr(1, 3) == "LDA")	dest[writeIndex + 1] = LDA_AB;

			dest[writeIndex + 2] = (add && 0x00FF); //Address Low
			dest[writeIndex + 3] = (add&&0xFF00)>>2;  //Address High
			writeIndex += 3;
		}
	}

	void parseAsm(char* &filename, uint8_t *dest) 
	{
		int  writeIndex = -1;
		char line[32];
		//Read line
		//Parse all the lines into memory
		do {
			parse(line, dest, writeIndex);
		} while (true);
		
	}
};

int main() {
	//Define an empty rom in memory
	//8 bits	= 2 bytes
	//512 bytes = 1 kilobyte 
	uint8_t ROM[512];

	Processor proc;
	CPU.AC = 0;
	proc.writeData(ADD_PPU, 0xAE);
	proc.process(LDA + (ADD_PPU << 8));
	CPU.AC = 0xAF;
	proc.process(STA + (ADD_PPU << 8));
	proc.readData(ADD_PPU);

	int ac = CPU.AC;
	std::cout << "Accumulator: " << std::hex << ac << std::endl;

	std::cout << "Press Any Key to Continue.";
	int in;
	std::cin >> in;
}
