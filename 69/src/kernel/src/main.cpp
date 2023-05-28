
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "descriptor_tables.h"
#include "interrupts.h"
#include "drivers/keyboard/keyboard.h"
#include "common.h"
#include "drivers/keyboard/timer.h"
#include <cstdlib>


#define BUFSIZE 2200
// #define VGA_ADDRESS 0xB8000

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}


#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif







enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static uint32_t next_line_index = 1;
uint8_t g_fore_color = VGA_COLOR_WHITE, g_back_color = VGA_COLOR_BLUE;
uint8_t vga_index;

uint16_t vga_entry_3(unsigned char ch, uint8_t fore_color, uint8_t back_color)
{
    uint16_t ax = 0;
    uint8_t ah = 0, al = 0;

    ah = back_color;
    ah <<= 4;
    ah |= fore_color;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_GREEN);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}
void printf(const char* data){

}
void print_int(int data){
	char str[10];
	int i = 0;
	while(data > 0){
		str[i] = data % 10 + '0';
		data /= 10;
		i++;
	}
	str[i] = '\0';
	for(int j = i - 1; j >= 0; j--){
		terminal_putchar(str[j]);
	}
}

void print_new_line(){

	terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
}


void convert_unint8_to_str(uint8_t data, char* str){
	int i = 0;
	while(data > 0){
		str[i] = data % 10 + '0';
		data /= 10;
		i++;
	}
	str[i] = '\0';
	for(int j = i - 1; j >= 0; j--){
		terminal_putchar(str[j]);
	}
}


void clear_vga_buffer(uint16_t **buffer, uint8_t fore_color, uint8_t back_color)
{
    uint32_t i;
    for(i = 0; i < BUFSIZE; i++){
        (*buffer)[i] = vga_entry_3(0, fore_color, back_color);
    }
    next_line_index = 1;
    vga_index = 0;
}

class OperatingSystem {
    int tick = 0;

public:
    OperatingSystem(vga_color color) {


    }

    void init() {

        terminal_writestring("Initializing UiA Operating System....");
		print_new_line();
    }

    void debug_print(char *str) {
        terminal_writestring(str);
		print_new_line();
	}

	// void interrupt_handler_0(registers_t regs) {
	// 	terminal_writestring("Called Interrupt Handler 0!");
	// 	print_new_line();
	// }
    // void interrupt_handler_1(registers_t regs) {
    //     terminal_writestring("Called Interrupt Handler 1!");
	// 	print_new_line();
		 
    // }

    void interrupt_handler_3(registers_t regs) {
        terminal_writestring("Called Interrupt Handler 3!");
		print_new_line();
		 
    }

    void interrupt_handler_4(registers_t regs) {
        terminal_writestring("Called Interrupt Handler 4!");
		print_new_line();
		 
    }

    void timer() {
        tick++;
        if (tick % 100 == 0) {
            terminal_writestring("(Every Second) Tick: ");
			print_new_line();
            print_int(tick);
			terminal_writestring(" yoooo ");
             
        }

    }
};











void kernel_main(void)
{
    terminal_initialize();

	
 
	/* Newline support is left as an exercise. */
	init_gdt();
	init_idt();
	init_interrupts();
	idt_load();
	
	
	

	terminal_writestring("Hello, you have now a GDT!");
	print_new_line();
	// Create operating system object
    auto os = OperatingSystem(VGA_COLOR_RED);
    os.init();

    // Do some printing!
    os.debug_print("Hello World!");
	print_new_line();


	// register_interrupt_handler(1,[](registers_t* regs, void* context){
    //     auto* os = (OperatingSystem*)context;
    //     os->interrupt_handler_1(*regs);
    // }, (void*)&os);

    // Create some interrupt handlers for 3
    register_interrupt_handler(3,[](registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_3(*regs);
    }, (void*)&os);

    // Create some interrupt handler for 4
	terminal_writestring("mmmmhh");
    register_interrupt_handler(4,[](registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_4(*regs);
    }, (void*)&os);
	terminal_writestring("hmmmm");


    // Fire interrupts! Should trigger callback above
	// asm volatile ("int $0x1");
    // asm volatile ("int $0x3");
    // asm volatile ("int $0x4");

    // Disable interrutps
    asm volatile("sti");
	
    // Create a timer on IRQ0 - System Timer
    UiAOS::CPU::PIT::init_timer(1, [](registers_t*regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->timer();
		terminal_writestring("timer");
    }, &os);


	
    // Hook Keyboard
	terminal_writestring("kommer inn");
	print_new_line();
    UiAOS::IO::Keyboard::hook_keyboard([](uint8_t scancode, void* context){
        auto* os = (OperatingSystem*)context;
        terminal_writestring("Keyboard Event: ");
		terminal_putchar(UiAOS::IO::Keyboard::scancode_to_ascii(scancode));
        terminal_writestring(" (");
        print_int(scancode);
        terminal_writestring(")");
		print_new_line();
        
    }, &os);
	terminal_writestring("kommer ut");
	// Enable interrupts
	asm volatile("sti");


	
	
	while(1){}
	
}
