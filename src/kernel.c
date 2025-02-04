#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/memory.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "string/string.h"
#include "fs/file.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "disk/streamer.h"
#include "gdt/gdt.h"
#include "config.h"

uint16_t *video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_write_char(char c, char colour)
{
    if (c == '\n')
    {
        terminal_row++;
        terminal_col = 0;
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col++;

    if (terminal_col == 20)
    {
        terminal_col = 0;
        terminal_row++;
    }
}

void terminal_initialize()
{
    video_mem = (uint16_t *)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;

    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

void print(const char *string)
{
    size_t len = strlen(string);

    for (int i = 0; i < len; i++)
    {
        terminal_write_char(string[i], 15);
    }
}

static struct paging_4gb_chunk *kernel_chunk;

void panic(const char *message)
{
    print(message);
    while (1)
    {
    }
}

struct gdt gdt_real[ACTARUS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[ACTARUS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},       // NULL Segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a}, // Kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92}, // Kernel Data segment
};

void kernel_main()
{
    terminal_initialize();
    print("Hello Actarus !\n");

    memset(gdt_real, 0x00, sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real, gdt_structured, ACTARUS_TOTAL_GDT_SEGMENTS);

    // Loads gdt
    gdt_load(gdt_real, sizeof(gdt_real));

    // Init heap
    kheap_init();

    // Init fs
    fs_init();

    // Search and init diks
    disk_search_and_init();

    // Init Interrupt descriptor table
    idt_init();

    // Setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

    // Switch to kernel paging chunk
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    // Enable paging
    enable_paging();

    // Enable sys interrupts
    enable_interrupts();

    int fd = fopen("0:/hello.txt", "r");

    if (fd)
    {
        struct file_stat s;
        fstat(fd, &s);

        fclose(fd);

        print("Testing\n");
    }

    while (1)
    {
    }
}