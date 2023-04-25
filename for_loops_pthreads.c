#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

int mails = 0;

void * routine() {

    for(int i = 0; i < 10000000; i++){
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
    
}

int main(int argc, char* argv[]) {
    pthread_t th[4];
    int i = 0;
    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i < 4; i++){
        if(pthread_create(th + i, NULL, &routine, NULL) != 0) {
            return i+1;
        }
    }

    for(int i = 0; i < 4; i++){
        if(pthread_join(th[i], NULL) != 0) {
            return i+1+4;
        }
       
    }
   
    pthread_mutex_destroy(&mutex);
    printf("mails: %d\n", mails);
    return 0;
}