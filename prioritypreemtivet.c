#include <stdio.h>

struct Process {
int pid, arrival_time, burst_time, priority, remaining_time, completion_time, waiting_time, turnaround_time;
};

void priorityPreemptive(struct Process p[], int n) {
int time = 0, completed = 0, min_priority, shortest;
float total_waiting = 0, total_turnaround = 0;

for (int i = 0; i < n; i++)
p[i].remaining_time = p[i].burst_time;

while (completed < n) {
min_priority = 9999;
shortest = -1;

for (int i = 0; i < n; i++) {
if (p[i].arrival_time <= time && p[i].remaining_time > 0 && p[i].priority < min_priority) {
min_priority = p[i].priority;
shortest = i;
}
}

if (shortest == -1) {
time++;
continue;
}

p[shortest].remaining_time--;

if (p[shortest].remaining_time == 0) {
completed++;
p[shortest].completion_time = time + 1;
p[shortest].turnaround_time = p[shortest].completion_time - p[shortest].arrival_time;
p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;
total_waiting += p[shortest].waiting_time;
total_turnaround += p[shortest].turnaround_time;
}

time++;
}

printf("\nPreemptive Priority Scheduling:\n");
printf("PID\tAT\tBT\tP\tCT\tTAT\tWT\n");
for (int i = 0; i < n; i++)
printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

printf("Average Waiting Time: %.2f\n", total_waiting / n);
printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

int main() {
int n;
printf("Enter number of processes: ");
scanf("%d", &n);

struct Process p[n];

for (int i = 0; i < n; i++) {
printf("Enter Process ID, Arrival Time, Burst Time, Priority: ");
scanf("%d %d %d %d", &p[i].pid, &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
}

priorityPreemptive(p, n);
return 0;
}
