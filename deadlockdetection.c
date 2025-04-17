#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
    int P, R;

    printf("Enter the number of processes: ");
    scanf("%d", &P);

    printf("Enter the number of resources: ");
    scanf("%d", &R);


    int alloc[P][R], max[P][R], need[P][R], finish[P];
    int avail[R];


    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < P; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }


    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < P; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for (int i = 0; i < R; i++) {
        scanf("%d", &avail[i]);
    }


    for (int i = 0; i < P; i++) {
        finish[i] = 0;
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
