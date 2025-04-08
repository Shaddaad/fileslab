#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
    int service_time[n];
    service_time[0] = at[0];
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i-1] + bt[i-1];
        if (service_time[i] < at[i])
            service_time[i] = at[i];
        wt[i] = service_time[i] - at[i];
        if (wt[i] < 0)
            wt[i] = 0;
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int at[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    findWaitingTime(processes, n, bt, wt, at);
    findTurnAroundTime(processes, n, bt, wt, at, tat);
    printf("\n+----------+-------------+-----------+-------------+----------------+\n");
    printf("| Process  | Arrival Time| Burst Time| Waiting Time| Turnaround Time|\n");
    printf("+----------+-------------+-----------+-------------+----------------+\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("| P%-7d | %-11d | %-9d | %-11d | %-14d |\n", processes[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("+----------+-------------+-----------+-------------+----------------+\n");
    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);
    printf("\nGantt Chart:\n");
    printf("+");
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < at[i]) {
            for (int j = 0; j < 7; j++) printf("-");
            printf("+");
            current_time = at[i];
        }
        for (int j = 0; j < 7; j++) printf("-");
        printf("+");
    }
    printf("\n|");
    current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < at[i]) {
            printf(" IDLE  |");
            current_time = at[i];
        }
        printf("  P%-3d |", processes[i]);
        current_time += bt[i];
    }
    printf("\n+");
    current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < at[i]) {
            for (int j = 0; j < 7; j++) printf("-");
            printf("+");
            current_time = at[i];
        }
        for (int j = 0; j < 7; j++) printf("-");
        printf("+");
    }
    printf("\n");
    current_time = 0;
    printf("%-7d", current_time);
    for (int i = 0; i < n; i++) {
        if (current_time < at[i]) {
            current_time = at[i];
            printf("%-7d", current_time);
        }
        current_time += bt[i];
        printf("%-7d", current_time);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n], burst_time[n], arrival_time[n];
    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        processes[i] = i + 1;
        printf("Enter arrival time: ");
        scanf("%d", &arrival_time[i]);
        printf("Enter burst time: ");
        scanf("%d", &burst_time[i]);
    }
    printf("\nFCFS Scheduling Algorithm\n");
    printf("=========================\n");
    findAvgTime(processes, n, burst_time, arrival_time);
    return 0;
}
