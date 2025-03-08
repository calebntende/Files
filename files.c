#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

void process_line(char *line);
void handle_assignment(char *line);
void handle_list(char *line);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

        // Ignore blank lines and comments
        if (line[0] == '\0' || line[0] == '%') {
            continue;
        }

        // Ignore anything after a '%'
        char *comment_pos = strchr(line, '%');
        if (comment_pos) {
            *comment_pos = '\0';
        }

        // Process the line
        process_line(line);
    }

    fclose(file);
    return EXIT_SUCCESS;
}

void process_line(char *line) {
    if (strchr(line, '=')) {
        handle_assignment(line);
    } else if (strchr(line, ',')) {
        handle_list(line);
    } else {
        // Handle other types of lines if necessary
    }
}

void handle_assignment(char *line) {
    char *key = strtok(line, "=");
    char *value = strtok(NULL, "=");

    if (key && value) {
        // Trim whitespace
        while (isspace((unsigned char)*key)) key++;
        while (isspace((unsigned char)*value)) value++;
        char *end_key = key + strlen(key) - 1;
        char *end_value = value + strlen(value) - 1;
        while (end_key > key && isspace((unsigned char)*end_key)) *end_key-- = '\0';
        while (end_value > value && isspace((unsigned char)*end_value)) *end_value-- = '\0';

        // Process the key-value pair
        printf("Assignment: %s = %s\n", key, value);
    }
}

void handle_list(char *line) {
    char *token = strtok(line, ",");
    while (token) {
        // Trim whitespace
        while (isspace((unsigned char)*token)) token++;
        char *end_token = token + strlen(token) - 1;
        while (end_token > token && isspace((unsigned char)*end_token)) *end_token-- = '\0';

        // Process the list item
        printf("List item: %s\n", token);

        token = strtok(NULL, ",");
    }
}