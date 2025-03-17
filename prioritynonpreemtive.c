#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id, AT, BT, CT, TAT, WT, RT, priority, completed;
};

void sortByPriority(struct Process p[], int n, int currentTime) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!p[i].completed && !p[j].completed) {
                if ((p[i].AT <= currentTime && p[j].AT <= currentTime && p[i].priority > p[j].priority) ||
                    (p[i].AT > currentTime && p[j].AT <= currentTime)) {
                    struct Process temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
    }
}

void calculatePriorityNonPreemptive(struct Process p[], int n) {
    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed < n) {
        sortByPriority(p, n, currentTime);
        int index = -1;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].AT <= currentTime) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            currentTime++;
        } else {
            p[index].CT = currentTime + p[index].BT;
            p[index].TAT = p[index].CT - p[index].AT;
            p[index].WT = p[index].TAT - p[index].BT;
            p[index].RT = currentTime - p[index].AT;
            p[index].completed = 1;
            totalWT += p[index].WT;
            totalTAT += p[index].TAT;
            currentTime = p[index].CT;
            completed++;
        }
    }

    printf("\nProcess\tAT\tBT\tPT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (p[j].id == i + 1) {
                printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                       p[j].id, p[j].AT, p[j].BT, p[j].priority, p[j].CT, p[j].TAT, p[j].WT, p[j].RT);
                break;
            }
        }
    }

    printf("\nAverage WT: %.2f", totalWT / n);
    printf("\nAverage TAT: %.2f\n", totalTAT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time (AT), Burst Time (BT) & Priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].AT, &p[i].BT, &p[i].priority);
        p[i].completed = 0;
    }

    calculatePriorityNonPreemptive(p, n);
    return 0;
}
