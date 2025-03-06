#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void fcfs(struct Process proc[], int n) {
    int completion_time[n];

    // First process
    completion_time[0] = proc[0].arrival_time + proc[0].burst_time;
    proc[0].turnaround_time = completion_time[0] - proc[0].arrival_time;
    proc[0].waiting_time = proc[0].turnaround_time - proc[0].burst_time;

    // Remaining processes
    for (int i = 1; i < n; i++) {
        completion_time[i] = (completion_time[i - 1] > proc[i].arrival_time ? completion_time[i - 1] : proc[i].arrival_time) + proc[i].burst_time;
        proc[i].turnaround_time = completion_time[i] - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
}

void display(struct Process proc[], int n) {
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }

    // Calculate average waiting time and turnaround time
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }

    double avg_waiting_time = (double)total_waiting_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    // Display average waiting and turnaround times
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
    }

    fcfs(proc, n);
    display(proc, n);

    return 0;
}
