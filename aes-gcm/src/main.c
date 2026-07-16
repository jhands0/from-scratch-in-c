#include <stdio.h>

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
    int msg[4][4] = {
        {0, 4, 8, 12},
        {1, 5, 9, 13},
        {2, 6, 10, 14},
        {3, 7, 11, 15},
    };
    shift_rows(msg);
}