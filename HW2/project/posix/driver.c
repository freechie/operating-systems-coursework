#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schedulers.h"

#define LINE_SIZE 256
#define NAME_SIZE 64

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <schedule.csv>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    char line[LINE_SIZE];
    unsigned int line_number = 0;

    while (fgets(line, sizeof(line), input) != NULL)
    {
        char name[NAME_SIZE];
        int priority;
        int burst;
        line_number++;

        if (sscanf(line, " %63[^,], %d, %d", name, &priority, &burst) != 3 ||
            priority < MIN_PRIORITY || priority > MAX_PRIORITY || burst <= 0)
        {
            fprintf(stderr, "Invalid task on line %u: %s", line_number, line);
            fclose(input);
            return EXIT_FAILURE;
        }

        size_t name_size = strlen(name) + 1;
        char *stored_name = malloc(name_size);
        if (stored_name == NULL)
        {
            perror("malloc");
            fclose(input);
            return EXIT_FAILURE;
        }
        memcpy(stored_name, name, name_size);
        add(stored_name, priority, burst);
    }

    if (ferror(input))
    {
        perror(argv[1]);
        fclose(input);
        return EXIT_FAILURE;
    }

    fclose(input);
    schedule();

    return EXIT_SUCCESS;
}
