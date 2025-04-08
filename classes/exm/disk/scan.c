#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

int main() {
    int requests[100], n, head, direction;
    int size = 200; // size of disk (cylinders 0 to 199)

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    requests[n++] = head;
    sort(requests, n);

    int pos;
    for (int i = 0; i < n; i++)
        if (requests[i] == head)
            pos = i;

    int total_movement = 0;
    printf("\nSCAN Order: ");

    if (direction == 1) { // moving right
        for (int i = pos; i < n; i++) {
            printf("%d ", requests[i]);
            total_movement += abs(head - requests[i]);
            head = requests[i];
        }
        if (head != size - 1) {
            total_movement += abs(head - (size - 1));
            head = size - 1;
        }
        for (int i = pos - 1; i >= 0; i--) {
            printf("%d ", requests[i]);
            total_movement += abs(head - requests[i]);
            head = requests[i];
        }
    } else { // moving left
        for (int i = pos; i >= 0; i--) {
            printf("%d ", requests[i]);
            total_movement += abs(head - requests[i]);
            head = requests[i];
        }
        if (head != 0) {
            total_movement += head;
            head = 0;
        }
        for (int i = pos + 1; i < n; i++) {
            printf("%d ", requests[i]);
            total_movement += abs(head - requests[i]);
            head = requests[i];
        }
    }

    printf("\nTotal Head Movement: %d\n", total_movement);
    return 0;
}