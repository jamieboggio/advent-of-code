#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256

void remove_newline(char line[])
{
    if (line == nullptr) {
        return;
    }

    size_t len = strlen(line);
    if (isspace(line[len - 1])) {
        line[len - 1] = '\0';
    }
}

int new_direction_from_line(const char* line)
{
    int direction_mult = line[0] == 'R' ? 1 : -1;
    int direction_mag = 0;
    const int base = 10;
    for (size_t i = 1; line[i] != '\0'; i++) {
        direction_mag += (line[i] - '0');
        direction_mag *= base;
    }
    direction_mag /= 10;
    direction_mag = (direction_mag % 100);
    return direction_mag * direction_mult;
}

int main(int argc, char* argv[])
{
    // explicitly reject (argc > 2) to hint to user potential mistake
    if (argc > 2) {
        fprintf(stderr, "usage: %s <PATH_TO_INPUT>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char* fpath = argc == 2 ? argv[1] : "input.txt";
    FILE* in_file = fopen(fpath, "r");
    if (in_file == nullptr) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    int password = 0;
    char buffer[BUF_SIZE];
    int cur_direction = 50;
    while (fgets(buffer, sizeof(buffer), in_file) != NULL) {
        remove_newline(buffer);
        int amount = new_direction_from_line(buffer);
        cur_direction += amount;
        if(cur_direction < 0)
        {
            cur_direction += 100;
        }else if(cur_direction >= 100)
        {
            cur_direction -= 100;
        }
        if(cur_direction == 0)
        {
            password++;
        }
    }

    printf("password = %d\n", password);

    fclose(in_file);
    return EXIT_SUCCESS;
}
