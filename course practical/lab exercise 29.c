#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 3 // Buffer capacity
int mutex = 1;
int full = 0;
int empty = CAPACITY;
int item_count = 0;
void producer() {
    --mutex; // Wait(mutex)
    ++full;  // Signal(full)
    --empty; // Wait(empty)
    item_count++;
    printf("Producer produced item %d\n", item_count);   
    ++mutex; // Signal(mutex)
}
void consumer() {
    --mutex; // Wait(mutex)
    --full;  // Wait(full)
    ++empty; // Signal(empty)
    printf("Consumer consumed item %d\n", item_count);
    item_count--;   
    ++mutex; // Signal(mutex)
}
int main() {
    int choice;
    printf("--- Producer-Consumer Simulation ---\n");
    printf("Buffer Capacity: %d\n", CAPACITY);
    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if ((mutex == 1) && (empty != 0)) {
                    producer();
                } else {
                    printf("Buffer is FULL! Producer must wait.\n");
                }
                break;
            case 2:
                if ((mutex == 1) && (full != 0)) {
                    consumer();
                } else {
                    printf("Buffer is EMPTY! Consumer must wait.\n");
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}