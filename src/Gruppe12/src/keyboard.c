#include "keyboard.h"
#include "terminal.h"
#include "libc/stdint.h"

static uint8_t last_scancode = 0;
static uint32_t debounce_count = 0;

void keyboard_init() {
    terminal_write("[KB] Norwegian OK\n");
}

static void vga_write_cp437(uint8_t cp437_code) {
    volatile uint16_t* vga = (volatile uint16_t*)0xB8000;
    extern uint8_t terminal_row;
    extern uint8_t terminal_col;

    uint16_t pos = terminal_row * 80 + terminal_col;
    vga[pos] = 0x0F00 | cp437_code;

    terminal_col++;
    if (terminal_col >= 80) {
        terminal_col = 0;
        terminal_row++;
    }
    if (terminal_row >= 25) {
        terminal_row = 0;
    }
}

void keyboard_handler(uint32_t scancode) {
    if (scancode == last_scancode) {
        debounce_count++;
        if (debounce_count > 3) return;
    } else {
        debounce_count = 0;
        last_scancode = scancode;
    }

    if (scancode & 0x80) return;

    uint8_t code = scancode & 0x7F;

    switch(code) {
        // Tall
        case 0x02: terminal_write("1"); break;
        case 0x03: terminal_write("2"); break;
        case 0x04: terminal_write("3"); break;
        case 0x05: terminal_write("4"); break;
        case 0x06: terminal_write("5"); break;
        case 0x07: terminal_write("6"); break;
        case 0x08: terminal_write("7"); break;
        case 0x09: terminal_write("8"); break;
        case 0x0A: terminal_write("9"); break;
        case 0x0B: terminal_write("0"); break;

        // Bokstaver
        case 0x10: terminal_write("q"); break;
        case 0x11: terminal_write("w"); break;
        case 0x12: terminal_write("e"); break;
        case 0x13: terminal_write("r"); break;
        case 0x14: terminal_write("t"); break;
        case 0x15: terminal_write("y"); break;
        case 0x16: terminal_write("u"); break;
        case 0x17: terminal_write("i"); break;
        case 0x18: terminal_write("o"); break;
        case 0x19: terminal_write("p"); break;

        case 0x1E: terminal_write("a"); break;
        case 0x1F: terminal_write("s"); break;
        case 0x20: terminal_write("d"); break;
        case 0x21: terminal_write("f"); break;
        case 0x22: terminal_write("g"); break;
        case 0x23: terminal_write("h"); break;
        case 0x24: terminal_write("j"); break;
        case 0x25: terminal_write("k"); break;
        case 0x26: terminal_write("l"); break;

        case 0x2C: terminal_write("z"); break;
        case 0x2D: terminal_write("x"); break;
        case 0x2E: terminal_write("c"); break;
        case 0x2F: terminal_write("v"); break;
        case 0x30: terminal_write("b"); break;
        case 0x31: terminal_write("n"); break;
        case 0x32: terminal_write("m"); break;

        // Spesielle
        case 0x39: terminal_write(" "); break;
        case 0x0E: terminal_write("\b \b"); break;
        case 0x1C: terminal_write("\n"); break;

        // Norske tegn (CP437 korrigert)
        case 0x1A:  // å
            vga_write_cp437(134);
            break;

        case 0x27:  // ø
            vga_write_cp437(237);
            break;

        case 0x28:  // æ
            vga_write_cp437(145);
            break;

        default:
            break;
    }
}

char scancode_to_ascii(uint8_t scancode) {
    return 0;
}