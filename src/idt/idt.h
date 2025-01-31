#ifndef IDT_H
#define IDT_H
#include <stdint.h>

struct idt_desc
{
    uint16_t offset_1; // offset bits 0 - 15
    uint16_t selector; // Selector in our GDT
    uint8_t zero;      // Does nothing
    uint8_t type_attr; // Descriptor type & attributes
    uint16_t offset_2; // Offset bits 16-31
} __attribute__((packed));

struct idtr_desc
{
    uint16_t limit; // size of the descriptor table -1
    uint32_t base;  // Base addr of he start of the interrupt descriptor table
} __attribute__((packed));

void idt_init();

void enable_interrupts();
void disable_interrupts();

#endif