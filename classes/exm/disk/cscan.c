#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main() {
    int requests[100], n, head;
    int size = 200; // total cylinders (0 to 199)

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    requests[n++] = head;
    sort(requests, n);

    int pos;
    for (int i = 0; i < n; i++)
        if (requests[i] == head)
            pos = i;

    int total_movement = 0;
    printf("\nC-SCAN Order: ");

    // Move right first (toward higher cylinders)
    for (int i = pos; i < n; i++) {
        printf("%d ", requests[i]);
        total_movement += abs(head - requests[i]);
        head = requests[i];
    }

    // Go to the end if not already there
    if (head != size - 1) {
        total_movement += abs(head - (size - 1));
        head = 0; // jump to beginning
        total_movement += (size - 1); // jump counted
    } else {
        head = 0; // already at end, just jump
        total_movement += (size - 1);
    }

    // Service remaining requests from beginning to before original head
    for (int i = 0; i < pos; i++) {
        printf("%d ", requests[i]);
        total_movement += abs(head - requests[i]);
        head = requests[i];
    }

    printf("\nTotal Head Movement: %d\n", total_movement);
    return 0;
}