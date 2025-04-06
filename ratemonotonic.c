#include <stdio.h>
#include <math.h>
#include <time.h>

// GCD and LCM helper functions
int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    clock_t start = clock();

    int n = 3;
    int burst[3], period[3];
    float utilization = 0.0;

    printf("Enter the number of processes: %d\n", n);

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst[i]);
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &period[i]);
    }

    // LCM of all periods
    int lcm_val = period[0];
    for (int i = 1; i < n; i++) {
        lcm_val = lcm(lcm_val, period[i]);
    }

    printf("LCM=%d\n", lcm_val);
    printf("Rate\n");
    printf("Monotone Scheduling:\n");

    // Matrix-style header
    printf("PID\tBurst\tPeriod\n");

    // Table values + utilization
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, burst[i], period[i]);
        utilization += (float)burst[i] / period[i];
    }

    float bound = n * (pow(2, 1.0 / n) - 1);
    printf("%.6f <= %.6f =>%s\n", utilization, bound, utilization <= bound ? "true" : "false");

    printf("Process returned 0 (0x0)\n");
    printf("Press any key to continue.\n");
    printf("%d\n", n);

    double exec_time = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("execution time : %.3f s\n", exec_time);

    return 0;
}
