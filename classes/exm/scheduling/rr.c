#include <stdio.h>

struct Process {
    int id, at, bt, rt, ct, tat, wt;
};

struct Gantt {
    int pid;
    int start;
    int end;
};

int main() {
    int n, tq, time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &p[i].at);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int completed = 0, queue[100], front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    struct Gantt gantt[100]; // to store chart
    int g = 0;

    // Enqueue first arrivals
    for (int i = 0; i < n; i++) {
        if (p[i].at == time) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].at <= time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        int slice = (p[idx].rt > tq) ? tq : p[idx].rt;

        gantt[g].pid = p[idx].id;
        gantt[g].start = time;
        gantt[g].end = time + slice;
        g++;

        time += slice;
        p[idx].rt -= slice;

        // Enqueue new arrivals
        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].at <= time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        } else {
            queue[rear++] = idx;
        }
    }

    // 📋 Print Table
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // 🖨️ Print Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < g; i++) {
        printf("| P%d ", gantt[i].pid);
    }
    printf("|\n");

    // Print time line below
    printf("%d", gantt[0].start);
    for (int i = 0; i < g; i++) {
        printf("   %d", gantt[i].end);
    }
    printf("\n");

    return 0;
}