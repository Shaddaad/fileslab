#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n];
    int pid[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("P%d (AT BT): ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                int temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }
        }
    }

    ct[0] = at[0] + bt[0];
    for (int i = 1; i < n; i++) {
        if (at[i] > ct[i - 1])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i - 1] + bt[i];
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nGantt Chart:\n");

    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i] - 1; j++) printf(" ");
        printf("P%d", pid[i]);
        for (int j = 0; j < bt[i] - 1; j++) printf(" ");
        printf("|");
    }

    printf("\n ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++) printf("--");
        printf(" ");
    }

    printf("\n%d", at[0] < 0 ? 0 : at[0]);
    for (int i = 0; i < n; i++) {
        if (ct[i] < 10) printf("   %d", ct[i]);
        else printf("  %d", ct[i]);
    }

    printf("\n");

    return 0;
}
