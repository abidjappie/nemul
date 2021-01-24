#pragma once
#include <cstdint>

//Register Addresses
#define ADD_CPU 0x0 //NOT SURE YET
#define ADD_PPU 0x2000
#define ADD_APU 0x4000

struct CPUR {
	uint8_t AC;
	uint8_t IX;
	uint8_t IY;
	uint8_t PC;
	uint8_t SP;
	uint8_t SR;
} CPU;

struct PPUR {
	uint8_t PPUCTRL;
	uint8_t PPUMASK;
	uint8_t PPUSTATUS;
	uint8_t OAMADDR;
	uint8_t OAMDATA;
	uint8_t PPUSCROLL;
	uint8_t PPUDATA;
	uint8_t OAMDMA;
} PPU;

struct APUR {
	struct {
		uint8_t DLCN;
		uint8_t EPNS;
		uint8_t TIM_L;
		uint8_t TIM_H;
	} PULSE1;

	struct {
		uint8_t DLCN;
		uint8_t EPNS;
		uint8_t TIM_L;
		uint8_t TIM_H;
	} PULSE2;

	struct {
		uint8_t CRRR;
		uint8_t TIM_L;
		uint8_t TIM_H;
	} TRIANGLE;

	struct {
		uint8_t LCNN;
		uint8_t LPPP;
		uint8_t LCL;
	} NOISE;

	struct {
		uint8_t ILFF;
		uint8_t DL;
		uint8_t ADDRESS;
		uint8_t LENGTH;
	} DMC;

	uint8_t CONTROL;
	uint8_t STATUS;
	uint8_t FCOUNT;

} APU;