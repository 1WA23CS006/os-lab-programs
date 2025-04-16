#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;
sem_t full;
sem_t empty;
int x = 0;


void producer();
void consumer();

int main() {
    int choice;
    int buffer_capacity;

    printf("Enter buffer capacity: ");
    scanf("%d", &buffer_capacity);

    if (buffer_capacity <= 0) {
        printf("Invalid buffer capacity. Exiting...\n");
        return 1;
    }


    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, buffer_capacity);

    while (1) {

        printf("\nChoose an option:\n");
        printf("1. Producer\n");
        printf("2. Consumer\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            producer();
        } else if (choice == 2) {
            consumer();
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice, please try again.\n");
        }
    }


    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}

void producer() {

    sem_wait(&mutex);


    if (sem_trywait(&empty) == 0) {

        x++;
        printf("Produced item: %d\n", x);

        sem_post(&full);
    } else {

        printf("Buffer is full. Cannot produce more items.\n");
    }


    sem_post(&mutex);
}

void consumer() {

    sem_wait(&mutex);

    if (sem_trywait(&full) == 0) {

        printf("Consumed item: %d\n", x);
        x--;


        sem_post(&empty);
    } else {

        printf("Buffer is empty. Cannot consume items.\n");
    }


    sem_post(&mutex);
}
