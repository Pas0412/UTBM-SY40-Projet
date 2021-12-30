//
//  main.c
//  UTBM-SY40-Projet
//
//  Created by 黄永辉 on 01/12/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE_BATEAU 10
#define SIZE_TRAIN 10
#define SIZE_CAMION 10
pthread_mutex_t mutex;
pthread_cond_t truck_wait, truck_sleep;
pthread_t tid[5];
int Nb_truck = 0;
int Nb_train = 0;
int Nb_boat = 0;
//define 3 structs of transports: index, number of containers, destinations
struct truck_str{
    int i;
    int Nb_container;
    char des[];
};

struct train_str{
    int i;
    int Nb_container;
    char des[];
};

struct boat_str{
    int i;
    int Nb_container;
    char des[];
};
//define 3 objects of transports: 2 boats, 2 trains, 4 trucks.
struct boat_str boat_obj[1];
struct truck_str truck_obj[3];
struct train_str train_obj[1];

//proccess to create boat
int cre_boat(void* arg){
    pid_t pid;
    pid = fork();
    return pid;
}

//proccess to create train
int cre_train(void* arg){
    pid_t pid;
    pid = fork();
    return pid;
}

//function of truck
void truck(struct truck_str truck_obj){
    pthread_mutex_lock(&mutex);
    printf("truck %d arrives\n", truck_obj.i);
    Nb_truck ++;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&truck_sleep);
//    printf("printf of truck %d between signal and wait\n", car.i);
    pthread_cond_wait(&truck_wait, &mutex);
    printf("truck %d is the first in line\n", truck_obj.i);
    sleep(2);
    printf("truck %d leaves\n", truck_obj.i);
    Nb_truck --;
    pthread_mutex_unlock(&mutex);
}
//function of truck
void * func_truck(int i){
    truck_obj[i].i = i;
    truck(truck_obj[i]);
    pthread_exit(NULL);
}
//function of managing truck
void truck_manager(){
    while(1){
        pthread_mutex_lock(&mutex);
        if(Nb_truck > 0){
            printf("next car\n");
            pthread_mutex_unlock(&mutex);
            pthread_cond_signal(&truck_wait);
            sleep(1);
            printf("the portique is working, please wait\n");
            //works to do:
            //juge if semaphore is available
            //yes: V() || no: wait
            //jude destination and send a message to object processus
            //recieve if there is an message
            printf("the work is done\n");
            sleep(2);
            pthread_mutex_unlock(&mutex);
        }else{
            printf("there is no car waiting\n");
            pthread_cond_wait(&truck_sleep, &mutex);
        }
    }
}
//function of managing truck
void * func_truck_manager(void* arg){
    truck_manager();
    pthread_exit(NULL);
}

//proccess to create truck
int cre_truck(){
    pid_t pid;
//    pid = fork();
    int i;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&truck_wait, NULL);
    pthread_cond_init(&truck_sleep,NULL);
    
    pthread_create(tid+4,0,func_truck_manager,4);
    for(i = 0;i < 4;i++){
        pthread_create(tid+i, NULL, func_truck, i);
    }
    
    pthread_join(tid+4, NULL);
    for(i = 0;i < 4;i++){
        pthread_join(tid[i], NULL);
    }
    return pid;
}

int main(){
    int t = cre_truck();
    return 0;
}

