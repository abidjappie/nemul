#pragma once

//Opcodes 
// IM - Imediate, ZP - Zero Page, ZX - Zero Page X
// AB - Absolute, AX - AbsoluteX, AY - Absolute Y, IX - Indirect X, IY - Indirect Y

#define NOP 0xEA //No Operation
#define CLC 0x18 //Clear Carry
#define SEC 0x38 //Set Carry
#define CLI 0x58 //Clear Interrupt
#define SEI 0x78 //Set Interrupt
#define CLV 0xB8 //Clear Overflow
#define CLD 0xD8 //Clear Decimal
#define SED 0xF8 //Set Decimal

//Immediate/ Accumulator
#define ASL 0x0A
#define AND 0x29
#define EOR 0x49
#define ADC 0x69 
#define ROR 0x6A
#define STA 0x8D
#define LDY 0xA0
#define LDX 0xA2
#define LDA 0xA9
#define CPY 0xC0
#define CMP 0xC9
#define CPX 0xE0

#define ASL_ZP 0x06
#define ADC_ZP 0x65
#define ROR_ZP 0x66
#define LDA_ZP 0xA5

#define ASL_ZX 0x16
#define ADC_ZX 0x75
#define ROR_ZX 0x76

#define ADC_AB 0x6D
#define ROR_AB 0x6E
#define LDA_AB 0xAD

#define ADC_AX 0x7D
#define ROR_AX 0x7E

#define ADC_AY 0x79
#define ADC_IX 0x61
#define ADC_IY 0x71
