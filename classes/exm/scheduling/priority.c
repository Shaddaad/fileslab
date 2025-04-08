#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], bt[n], pr[n], ct[n], tat[n], wt[n];
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Burst Time and Priority for P%d: ", pid[i]);
        scanf("%d %d", &bt[i], &pr[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pr[i] > pr[j]) {
                int tmp;
                tmp = pr[i]; pr[i] = pr[j]; pr[j] = tmp;
                tmp = bt[i]; bt[i] = bt[j]; bt[j] = tmp;
                tmp = pid[i]; pid[i] = pid[j]; pid[j] = tmp;
            }
        }
    }

    ct[0] = bt[0];
    for (int i = 1; i < n; i++)
        ct[i] = ct[i - 1] + bt[i];

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i];
        wt[i] = tat[i] - bt[i];
    }

    printf("\nP\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], bt[i], pr[i], ct[i], tat[i], wt[i]);

    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++)
        printf(" P%d |", pid[i]);
    printf("\n0");
    for (int i = 0; i < n; i++)
        printf("   %d", ct[i]);
    printf("\n");

    return 0;
}
