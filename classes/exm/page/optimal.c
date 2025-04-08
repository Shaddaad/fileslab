#include <stdio.h>

int search(int key, int frames[], int f) {
    for (int i = 0; i < f; i++)
        if (frames[i] == key)
            return 1;
    return 0;
}

int predict(int pages[], int frames[], int n, int index, int f) {
    int res = -1, farthest = index;
    for (int i = 0; i < f; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i; // page not used again
    }
    return (res == -1) ? 0 : res;
}

int main() {
    int pages[100], frames[10], n, f, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        if (search(pages[i], frames, f)) {
            // Already in memory
        } else {
            faults++;
            int empty = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if (empty != -1)
                frames[empty] = pages[i];
            else {
                int pos = predict(pages, frames, n, i + 1, f);
                frames[pos] = pages[i];
            }
        }

        printf("Frames: ");
        for (int j = 0; j < f; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}