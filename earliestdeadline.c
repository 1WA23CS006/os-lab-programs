#include <stdio.h>

#define MAX 10

typedef struct {
    int pid;
    int burst;
    int period;
    int deadline;
    int remaining;
    int nextRelease;
    int absoluteDeadline;
} Task;

void sortByDeadline(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (tasks[i].absoluteDeadline > tasks[j].absoluteDeadline) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
}

int lcm(int a, int b) {
    int temp_a = a, temp_b = b;
    while (temp_b != 0) {
        int temp = temp_b;
        temp_b = temp_a % temp_b;
        temp_a = temp;
    }
    return (a * b) / temp_a;
}

int findLCM(int arr[], int n) {
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = lcm(result, arr[i]);
    }
    return result;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Task tasks[MAX];
    int periods[MAX];

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].burst);
        tasks[i].pid = i + 1;
        tasks[i].remaining = 0;
    }

    printf("Enter the deadlines:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].deadline);
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].period);
        tasks[i].nextRelease = 0;
        tasks[i].absoluteDeadline = tasks[i].deadline;
        periods[i] = tasks[i].period;
    }

    int hyperPeriod = findLCM(periods, n);
    printf("\nEarliest Deadline First Scheduling:\n");
    printf("Scheduling occurs for %d ms\n", hyperPeriod);
    printf("\nTime\tStatus\n");

    for (int time = 0; time < hyperPeriod; time++) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].nextRelease) {
                tasks[i].remaining = tasks[i].burst;
                tasks[i].absoluteDeadline = time + tasks[i].deadline;
                tasks[i].nextRelease += tasks[i].period;
            }
        }

        sortByDeadline(tasks, n);

        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                printf("%dms:\tTask %d is running.\n", time, tasks[i].pid);
                tasks[i].remaining--;
                executed = 1;

                if (time + 1 > tasks[i].absoluteDeadline && tasks[i].remaining > 0) {
                    printf("!!! Deadline MISS for Task %d at time %d\n", tasks[i].pid, time + 1);
                }
                break;
            }
        }

        if (!executed) {
            printf("%dms:\tIDLE\n", time);
        }
    }

    return 0;
}
