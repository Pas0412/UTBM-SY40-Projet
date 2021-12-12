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

void manager_camion(char * destination[], int i){
    int pid = fork();
    if(pid != 0)
      return;
    pthread_mutex_lock(&mutex);
    if(NbCamion > 0){
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&attendre);
    }
    else{
        printf("Il n'y a pas de camion.\n");
        pthread_cond_wait(&dormir, &mutex);
    }
    
    exit(0);
}

void camion(int i){
    pthread_mutex_lock(&mutex);
    printf("Le camion %d arrive\n", i);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&dormir);
    pthread_cond_wait(&attendre, &mutex);
    printf("Camion %d est le premier en ligne", i);
    pthread_mutex_unlock(&mutex);
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
    
    
    
    return 0;
}
