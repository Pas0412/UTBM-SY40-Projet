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
#define NbTh 10

pthread_t tid[SIZE_CAMION];
pthread_mutex_t mutex;
pthread_cond_t attendre, dormir;

int NbCamion = 0;

void bateau(char * destination[]){
    int pid = fork();
    if(pid != 0)
      return;
    exit(0);
}

void train(char * destination[]){
    int pid = fork();
    if(pid != 0)
      return;
    exit(0);
}

void manager_camion(){
    while(1){
    pthread_mutex_lock(&mutex);
    if(NbCamion > 0){
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&attendre);
        sleep(1);
    }
    else{
        printf("Il n'y a pas de camion.\n");
        pthread_cond_wait(&dormir, &mutex);
    }
    }
    
}



void camion(int i){
    pthread_mutex_lock(&mutex);
    printf("Le camion %d arrive\n", i);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&dormir);
    pthread_cond_wait(&attendre, &mutex);
    printf("Camion %d est le premier en ligne\n", i);
    pthread_mutex_unlock(&mutex);
    sleep(1);
}

void* func_mancamion(){
    manager_camion();
    pthread_exit(NULL);
}
void* func_camion(void* i){
    camion((int)(size_t) i);
    pthread_exit(NULL);
}



int protique1(char * destination[]){
    int pid = fork();
    if(pid != 0)
      return pid;
    
    int pos = 0;
    
    
    return 0;
}

int protique2(char * destination[]){
    int pid = fork();
    if(pid != 0)
      return pid;
    
    int pos = 0;
    
    
    return 0;
}

int main(int argc, const char * argv[]) {
    pthread_cond_init(&attendre, NULL);
    pthread_cond_init(&dormir, NULL);
    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(tid + NbTh, 0, func_mancamion, (void*)NbTh);
    for(int i = 0;i < SIZE_CAMION;i++){
        
        pthread_create(tid + i, 0, func_camion, (void*)(int)i);
        NbCamion++;
    }
    for(int i = 0;i < SIZE_CAMION;i++){
        
        pthread_join(tid[i], NULL);
    }

    return 0;
}


