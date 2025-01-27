/*
 * temp_shell.c
 * temporary shell implementation for MomentumOS.
 */

#include "shell.h"
#include "keyboard_driver.h"
#include "stdio.h"  // For basic I/O functions
#include "string.h" // For string manipulation

#define MAX_COMMAND_LENGTH 256
#define MAX_ARGUMENTS 10

// Command handler typedef
typedef void (*command_handler_t)(int argc, char* argv[]);

// Command structure
typedef struct {
    const char* name;
    const char* description;
    command_handler_t handler;
} command_t;

// Forward declarations of built-in command handlers
void cmd_help(int argc, char* argv[]);
void cmd_clear(int argc, char* argv[]);
void cmd_echo(int argc, char* argv[]);

// Command table
command_t commands[] = {
    {"help", "Displays available commands.", cmd_help},
    {"clear", "Clears the shell screen.", cmd_clear},
    {"echo", "Prints text to the shell.", cmd_echo},
};

#define NUM_COMMANDS (sizeof(commands) / sizeof(command_t))

void parse_and_execute_command(const char* input) {
    char buffer[MAX_COMMAND_LENGTH];
    strncpy(buffer, input, MAX_COMMAND_LENGTH);

    // Tokenize input
    char* argv[MAX_ARGUMENTS];
    int argc = 0;
    char* token = strtok(buffer, " ");
    while (token != NULL && argc < MAX_ARGUMENTS) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc == 0) return; // No command entered

    // Search for the command
    for (size_t i = 0; i < NUM_COMMANDS; i++) {
        if (strcmp(argv[0], commands[i].name) == 0) {
            commands[i].handler(argc, argv);
            return;
        }
    }

    printf("Unknown command: %s\n", argv[0]);
}

void shell_main() {
    char input[MAX_COMMAND_LENGTH];

    printf("Welcome to MomentumOS Shell!\nType 'help' to see available commands.\n\n");

    while (1) {
        printf("MomentumOS> ");
        fgets(input, MAX_COMMAND_LENGTH, stdin);

        // Remove trailing newline character
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        parse_and_execute_command(input);
    }
}

// Command Handlers

void cmd_help(int argc, char* argv[]) {
    printf("Available commands:\n");
    for (size_t i = 0; i < NUM_COMMANDS; i++) {
        printf("  %s - %s\n", commands[i].name, commands[i].description);
    }
}

void cmd_clear(int argc, char* argv[]) {
    printf("\033[H\033[J"); // ANSI escape code to clear the screen
}

void cmd_echo(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}
