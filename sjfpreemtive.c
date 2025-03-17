
#include <stdio.h>
#include <limits.h>

struct Process {
    int pid, bt, at, wt, tat, rt, ct, remaining_bt;
};

void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void sjfPreemptive(struct Process p[], int n) {
    sortByArrival(p, n);
    int completed = 0, currentTime = 0, shortest = -1;
    int totalWT = 0, totalTAT = 0, totalRT = 0;
    int isFirstResponse[n];

    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
        isFirstResponse[i] = 1;
    }

    while (completed < n) {
        int minBT = INT_MAX;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].remaining_bt > 0 && p[i].remaining_bt < minBT) {
                minBT = p[i].remaining_bt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        if (isFirstResponse[shortest]) {
            p[shortest].rt = currentTime - p[shortest].at;
            isFirstResponse[shortest] = 0;
        }

        p[shortest].remaining_bt--;
        currentTime++;

        if (p[shortest].remaining_bt == 0) {
            p[shortest].ct = currentTime;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            totalWT += p[shortest].wt;
            totalTAT += p[shortest].tat;
            totalRT += p[shortest].rt;
            completed++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat, p[i].rt);
    }
    printf("\nAverage WT: %.2f", (float)totalWT / n);
    printf("\nAverage TAT: %.2f", (float)totalTAT / n);
    printf("\nAverage RT: %.2f\n", (float)totalRT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter AT & BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        p[i].wt = p[i].tat = p[i].rt = p[i].ct = 0;
    }

    sjfPreemptive(p, n);
    return 0;
}
