#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames[10], pages[30], time[10];
    int n, f, count = 0, flag1, flag2, pos, faults = 0;

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
        flag1 = flag2 = 0;

        // Check if page is already in frame
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                count++;
                time[j] = count;
                flag1 = flag2 = 1;
                break;
            }
        }

        // Page not found in frame
        if (flag1 == 0) {
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    count++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = count;
                    flag2 = 1;
                    break;
                }
            }
        }

        // Replace least recently used
        if (flag2 == 0) {
            pos = findLRU(time, f);
            count++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = count;
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