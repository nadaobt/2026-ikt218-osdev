#include "libc/stdint.h"
#include "gdt.h"
#include "terminal.h"
#include "idt.h"
#include "irq.h"
#include "keyboard.h"

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    void* first;
};

void main(uint32_t magic, struct multiboot_info* mb_info) {
    gdt_init();
    terminal_init();
    terminal_write("OSDev 2026 - Gruppe 12\n");

    idt_init();
    irq_init();
    keyboard_init();

    terminal_write("\nKeyboard ready. Type something:\n");
    
    asm volatile("sti");

    while (1) {
        asm volatile("hlt");
    }
}