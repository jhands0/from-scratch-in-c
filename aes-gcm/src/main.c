#include <stdio.h>
#include <stddef.h>
#include <string.h>

void shift_rows(int msg[4][4]) {
    for (int i = 1; i < 4; i++) {
        int temp[] = {0, 0, 0, 0};
        for (int j = 0; j < 4; j++) {
            int new_j = ((((j - i) % 4) + 4) % 4);
            temp[new_j] = msg[i][j];
        }
        for (int j = 0; j < 4; j++) {
            msg[i][j] = temp[j];
        }
    }
}

void mix_columns(int msg[4][4]) {
    int matrix[4][4] = {
        {2, 3, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 2, 3},
        {3, 1, 1, 2},
    };

    for (int i = 0; i < 4; i++) {
        int temp[] = {0, 0, 0, 0};
        for (int j = 0; j < 4; j++) {
            msg[j][i] = temp[j];
        }
    }
}

int main(int argc, char **argv) {
    FILE *stream;
    char *path;
    size_t len;
    stream = open_memstream(&path, &len);
    fprintf(stream, "example/");

    if (argc != 2) {
        fprintf(stderr, "Usage: ./out <filecode>\n");
        fprintf(stderr, "filecode: [e | p][1 | 2 | 3]\n");
        fclose(stream);
        return -1;
    }
    
    const char *filecode = argv[1];
    if (filecode[0] == 'e') {
        fprintf(stream, "encrypt_");
    } else if (filecode[0] == 'p') {
        fprintf(stream, "plain_");
    } else {
        fprintf(stderr, "Usage: ./out <filecode>\n");
        fprintf(stderr, "filecode: [e | p][1 | 2 | 3]\n");
        fclose(stream);
        return -1;
    }
    fprintf(stream, "%c", filecode[1]);
    fprintf(stream, ".txt");
    fclose(stream);

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        return -1;
    }
    char c;
    int i = 1;
    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (i % 16 == 0) {
            printf("\n");
        }
        putchar(c);
        i++;
    }

    fclose(file);
    
    int msg[4][4] = {
        {0, 4, 8, 12},
        {1, 5, 9, 13},
        {2, 6, 10, 14},
        {3, 7, 11, 15},
    };
    shift_rows(msg);
}