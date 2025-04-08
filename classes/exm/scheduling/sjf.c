#include <stdio.h>

void sortProcesses(int n, int arrival[], int burst[], int pid[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (burst[i] > burst[j]) {
                int temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = arrival[i];
                arrival[i] = arrival[j];
                arrival[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }
}

void sjfScheduling(int n, int arrival[], int burst[]) {
    int waiting[10], turnaround[10], pid[10];

    for (int i = 0; i < n; i++)
        pid[i] = i + 1;

    sortProcesses(n, arrival, burst, pid);

    waiting[0] = 0; 
    turnaround[0] = burst[0];

    for (int i = 1; i < n; i++) {
        waiting[i] = waiting[i - 1] + burst[i - 1]; 
        turnaround[i] = waiting[i] + burst[i];  
    }

    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", pid[i], arrival[i], burst[i], waiting[i], turnaround[i]);
}

int main() {
    int n, arrival[10], burst[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Process %d Arrival & Burst Time: ", i + 1);
        scanf("%d %d", &arrival[i], &burst[i]);
    }

    sjfScheduling(n, arrival, burst);

    return 0;
}