
#include <stdio.h>

struct Process {
    int pid, bt, at, wt, tat, rt, ct;
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

void sjfScheduling(struct Process p[], int n) {
    sortByArrival(p, n);
    int completed = 0, currentTime = 0;
    int totalWT = 0, totalTAT = 0, totalRT = 0;

    while (completed < n) {
        int minIndex = -1, minBT = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].bt < minBT && p[i].tat == 0) {
                minBT = p[i].bt;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            currentTime++;
            continue;
        }

        p[minIndex].wt = currentTime - p[minIndex].at;
        p[minIndex].tat = p[minIndex].wt + p[minIndex].bt;
        p[minIndex].rt = p[minIndex].wt;
        p[minIndex].ct = currentTime + p[minIndex].bt;
        currentTime += p[minIndex].bt;
        completed++;

        totalWT += p[minIndex].wt;
        totalTAT += p[minIndex].tat;
        totalRT += p[minIndex].rt;
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

    sjfScheduling(p, n);
    return 0;
}

