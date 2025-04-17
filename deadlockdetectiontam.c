#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int main() {
    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int avail[R] = {3, 3, 2};

    int finish[P] = {0};
    int need[P][R];


    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;
    bool deadlock = false;

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > avail[j])
                        break;
                }

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        avail[k] += alloc[i][k];

                    finish[i] = 1;
                    found = true;
                    count++;

                    printf("Process %d can finish.\n", i);
                }
            }
        }

        if (!found) {
            deadlock = true;
            break;
        }
    }

    if (!deadlock)
        printf("System is not in a deadlock state.\n");
    else
        printf("System is in a deadlock state.\n");

    return 0;
}
