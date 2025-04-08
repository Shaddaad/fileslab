#include <stdio.h>

int main() {
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f], freq[f], time[f];
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }

    int faults = 0, t = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                freq[j]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            int min = freq[0], pos = 0;
            for (int j = 1; j < f; j++) {
                if (freq[j] < min || (freq[j] == min && time[j] < time[pos])) {
                    min = freq[j];
                    pos = j;
                }
            }
            frames[pos] = pages[i];
            freq[pos] = 1;
            time[pos] = t++;
            faults++;
        }
    }

    printf("Total Page Faults: %d\n", faults);
    return 0;
}
