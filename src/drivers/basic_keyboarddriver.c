/*
 * keyboard_driver.c
 * Basic keyboard input driver for MomentumOS.
 */

#include "keyboard_driver.h"
#include "io.h"  // For low-level port I/O functions

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_BUFFER_SIZE 256

static char key_buffer[KEYBOARD_BUFFER_SIZE];
static int buffer_index = 0;

// Key mapping (simplified for demonstration purposes)
static const char key_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0,
    // The rest can be extended as needed
};

void keyboard_interrupt_handler() {
    // Check if a key is available
    if (inb(KEYBOARD_STATUS_PORT) & 0x01) {
        // Read the keycode from the data port
        unsigned char keycode = inb(KEYBOARD_DATA_PORT);

        if (keycode < 128) {  // Ignore key releases
            char key = key_map[keycode];

            if (buffer_index < KEYBOARD_BUFFER_SIZE - 1) {
                key_buffer[buffer_index++] = key;
                key_buffer[buffer_index] = '\0';  // Null-terminate the string
            }
        }
    }
}

void init_keyboard_driver() {
    buffer_index = 0;

    // Set up the interrupt handler (IRQ1 for keyboard input)
    register_interrupt_handler(33, keyboard_interrupt_handler);
}

const char* get_key_buffer() {
    return key_buffer;
}

void clear_key_buffer() {
    buffer_index = 0;
    key_buffer[0] = '\0';
}
