#include <stdio.h>
#include <unistd.h>

int buffer[100]; 
int count = 0;    
int BUFFER_SIZE;   

void producer(int totalItems, int delay) {
    for (int i = 1; i <= totalItems; i++) {
        if (count < BUFFER_SIZE) { 
            buffer[count] = i; 
            printf("Produced: %d\n", i);
            count++;
        } else {
            printf("Buffer Full! Producer waiting...\n");
            i--; 
        }
        sleep(delay);
    }
}

void consumer(int totalItems, int delay) {
    for (int i = 1; i <= totalItems; i++) {
        if (count > 0) { 
            printf("\tConsumed: %d\n", buffer[count - 1]);
            count--;
        } else {
            printf("\tBuffer Empty! Consumer waiting...\n");
            i--;  
        }
        sleep(delay);
    }
}

int main() {
    int totalItems, producerDelay, consumerDelay;

    printf("Enter buffer size: ");
    scanf("%d", &BUFFER_SIZE);

    printf("Enter total items to produce: ");
    scanf("%d", &totalItems);

    printf("Enter producer delay (seconds): ");
    scanf("%d", &producerDelay);

    printf("Enter consumer delay (seconds): ");
    scanf("%d", &consumerDelay);

    producer(totalItems, producerDelay);
    consumer(totalItems, consumerDelay);

    return 0;
}
