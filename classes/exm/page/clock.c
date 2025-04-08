#include <stdio.h>

#define MAX 100

int main() {
    int pages[MAX], n, frames[MAX], ref[MAX], f;
    int pointer = 0, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        ref[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                ref[j] = 1;
                found = 1;
                break;
            }
        }

        // Page fault
        if (!found) {
            while (ref[pointer] == 1) {
                ref[pointer] = 0;
                pointer = (pointer + 1) % f;
            }

            // Replace the page
            frames[pointer] = pages[i];
            ref[pointer] = 1;
            pointer = (pointer + 1) % f;
            faults++;
        }

        // Print frames
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