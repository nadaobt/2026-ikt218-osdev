#include "libc/stdint.h"
#include "gdt.h"
#include "terminal.h"
#include "idt.h"
#include "irq.h"
#include "keyboard.h"
#include "kernel/memory.h"
#include "kernel/pit.h"

extern uint32_t end;

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    void* first;
};

void main(uint32_t magic, struct multiboot_info* mb_info) {
    gdt_init();
    terminal_init();
    idt_init();
    irq_init();
    keyboard_init();
    
    init_kernel_memory(&end);
    init_paging();
    print_memory_layout();
    init_pit();
    
    terminal_write("\nTesting malloc...\n");
    void* mem1 = malloc(100);
    void* mem2 = malloc(200);
    terminal_write("Allocated memory\n");
    
    terminal_write("\nSleeping 2 seconds (busy)...\n");
    sleep_busy(2000);
    terminal_write("Done!\n");
    
    terminal_write("Sleeping 2 seconds (interrupt)...\n");
    sleep_interrupt(2000);
    terminal_write("Done!\n");
    
    uint32_t counter = 0;
    while (1) {
        terminal_write("Loop: ");
        char buf[12];
        // (kan utvides med tall-print)
        terminal_write("\n");
        
        sleep_busy(1000);
        counter++;
        
        asm volatile("hlt");
    }
}