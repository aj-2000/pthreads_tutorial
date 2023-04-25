#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void* roll_dice(){
    int val = (rand() % 6) + 1;
    int* result = malloc(sizeof(int));
    *result = val;
    return (void*)result;
}

int main(int argc, char* argv[]){
    int *res;
    srand(time(NULL));
    pthread_t th;

    if (pthread_create(&th, NULL, roll_dice, NULL) != 0){
        return 1;
    }
    if (pthread_join(th, (void **) &res) != 0){
        return 2;
    }
    printf("Rolling dice: %d\n", *res);

    return 0;
}