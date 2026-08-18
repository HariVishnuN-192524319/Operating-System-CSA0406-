#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
pthread_mutex_t chopsticks[N];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id, right = (id + 1) % N;

    for (int i = 0; i < 2; i++) {
        printf("Philosopher %d is thinking...\n", id);
        
        // Asymmetric pick-up to avoid deadlock
        if (id % 2 == 0) {
            pthread_mutex_lock(&chopsticks[left]);
            pthread_mutex_lock(&chopsticks[right]);
        } else {
            pthread_mutex_lock(&chopsticks[right]);
            pthread_mutex_lock(&chopsticks[left]);
        }

        printf("Philosopher %d is eating\n", id);
        sleep(1);

        pthread_mutex_unlock(&chopsticks[left]);
        pthread_mutex_unlock(&chopsticks[right]);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    for (int i = 0; i < N; i++) pthread_mutex_init(&chopsticks[i], NULL);
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++) pthread_join(threads[i], NULL);
    for (int i = 0; i < N; i++) pthread_mutex_destroy(&chopsticks[i]);

    return 0;
}