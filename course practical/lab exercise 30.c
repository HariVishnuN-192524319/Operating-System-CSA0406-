#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t t1, t2; // Global thread identifiers

// Worker function for threads
void* thread_runner(void* arg) {
    int thread_num = *(int*)arg;
    pthread_t current_thread = pthread_self();

    printf("Thread %d started (ID: %lu)\n", thread_num, (unsigned long)current_thread);

    // (iii) pthread_equal: Check if this thread matches Thread 1
    if (pthread_equal(current_thread, t1)) {
        printf(" -> Status: Running inside Thread 1\n");
    } else {
        printf(" -> Status: Running inside Thread 2\n");
    }

    // (iv) pthread_exit: Terminate the thread safely
    pthread_exit(NULL);
}

int main() {
    int id1 = 1, id2 = 2;

    // (i) pthread_create: Spawn two worker threads
    if (pthread_create(&t1, NULL, thread_runner, &id1) != 0) {
        perror("Failed to create Thread 1");
        return 1;
    }
    if (pthread_create(&t2, NULL, thread_runner, &id2) != 0) {
        perror("Failed to create Thread 2");
        return 1;
    }

    // (iii) pthread_equal: Compare thread IDs in main thread
    if (pthread_equal(t1, t2)) {
        printf("Main: Threads are equal.\n");
    } else {
        printf("Main: Thread 1 and Thread 2 are distinct threads.\n");
    }

    // (ii) pthread_join: Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main: Both threads joined successfully. Exiting program.\n");
    return 0;
}