#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024
#define DELIMITER " "

void execute_command(char* command) {
    // This is where you would parse and execute the command.
    // For now, we'll just print it out.
    printf("Executing command: %s\n", command);
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("> ");
        if (!fgets(command, MAX_COMMAND_LENGTH, stdin)) {
            break;
        }

        // Remove trailing newline
        command[strcspn(command, "\n")] = 0;

        execute_command(command);
    }

    return 0;
}