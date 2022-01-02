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
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define SIZE_BOAT 8
#define SIZE_TRAIN 8
#define SIZE_TRUCK 2
//semaphore
sem_t sem;

//file de message
int msgid;
key_t key;
int ctn;

//thread et mutex
pthread_mutex_t mutex;
pthread_cond_t twait, tsleep;
pthread_t transportId[9];

int Nb_truck = 0;
int Nb_train = 0;
int Nb_boat = 0;
struct container{
    char des[8];
};
struct transport_str{
    int i;
    int Nb_container;
    struct container container[8];
};
struct msg_str{
    long type;
    int nb_ctn;
};

struct msg_str msg_ctn[8];
struct msg_str msg_rcv[8];
struct transport_str transport_obj[8];
struct transport_str transport_obj_final[8];

void origin_output(){
    printf("         | name of container         \n");
    printf("---------|---------------------------\n");
    printf("  boat0  |  tn_0                     \n");
    printf("  boat0  |  tk_0                     \n");
    printf("  boat1  |  tn_1                     \n");
    printf("  boat1  |  tk_1                     \n");
    printf("  train0 |  bo_0                     \n");
    printf("  train0 |  tk_2                     \n");
    printf("  train1 |  bo_1                     \n");
    printf("  train1 |  tk_3                     \n");
    printf("  truck0 |  bo_0                     \n");
    printf("  truck1 |  bo_1                     \n");
    printf("  truck2 |  bo_2                     \n");
    printf("  truck3 |  bo_3                     \n");
    printf("_________|___________________________\n");
}

void final_output(struct transport_str to[]){
    printf("         | name of container         \n");
    printf("---------|---------------------------\n");
    printf("  boat0  |  %s                     \n", to[0].container[0].des);
    printf("  boat0  |  %s                     \n", to[0].container[1].des);
    printf("  boat1  |  %s                     \n", to[1].container[0].des);
    printf("  boat1  |  %s                     \n", to[1].container[1].des);
    printf("  train0 |  %s                     \n", to[2].container[0].des);
    printf("  train0 |  %s                     \n", to[2].container[1].des);
    printf("  train1 |  %s                     \n", to[3].container[0].des);
    printf("  train1 |  %s                     \n", to[3].container[1].des);
    printf("  truck0 |  %s                     \n", to[4].container[0].des);
    printf("  truck1 |  %s                     \n", to[5].container[0].des);
    printf("  truck2 |  %s                     \n", to[6].container[0].des);
    printf("  truck3 |  %s                     \n", to[7].container[0].des);
    printf("_________|___________________________\n");
}

int juge_destination(char a[]){
    if(!strcmp(a,"bo_0")){
        return 0;
    }else if(!strcmp(a,"bo_1")){
        return 1;
    }else if(!strcmp(a,"tn_0")){
        return 2;
    }else if(!strcmp(a,"tn_1")){
        return 3;
    }else if(!strcmp(a,"tk_0")){
        return 4;
    }else if(!strcmp(a,"tk_1")){
        return 5;
    }else if(!strcmp(a,"tk_2")){
        return 6;
    }else if(!strcmp(a,"tk_3")){
        return 7;
    }else{return 8;
    }
}
//function of transport
void transport(int i, struct transport_str transport_ob){
    pthread_mutex_lock(&mutex);
    if(i == 0 || i == 1){
        printf("boat %d arrives\n", transport_ob.i);
        Nb_boat ++;
        pthread_mutex_unlock(&mutex);
        sleep(1);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&tsleep);
        pthread_cond_wait(&twait, &mutex);
        printf("boat %d is the first in line\n", transport_ob.i);
        sleep(2);
        //jude destination and send a message to object processus
        msg_ctn[i].type = 1;
        msg_ctn[i].nb_ctn = juge_destination(transport_ob.container[0].des);
        printf("des is %s\n",transport_ob.container[0].des);
        if (msgsnd(msgid, &msg_ctn[i], sizeof(struct msg_str),0) == -1) {
                perror("Erreur de lecture 1\n");
                exit(1);
            }
        msg_ctn[i].type = 1;
        msg_ctn[i].nb_ctn = juge_destination(transport_ob.container[1].des);
        printf("des is %s\n",transport_ob.container[1].des);
        if (msgsnd(msgid, &msg_ctn[i], sizeof(struct msg_str),0) == -1) {
                perror("Erreur de lecture 2\n");
                exit(1);
            }
        Nb_boat --;
        pthread_mutex_unlock(&mutex);
    }
    else if(i == 2 || i == 3)
    {
        printf("train %d arrives\n", transport_ob.i - 2);
        Nb_boat ++;
        pthread_mutex_unlock(&mutex);
        sleep(1);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&tsleep);
        pthread_cond_wait(&twait, &mutex);
        printf("train %d is the first in line\n", transport_ob.i - 2);
        sleep(2);
        
        msg_ctn[i].type = 1;
        msg_ctn[i].nb_ctn = juge_destination(transport_ob.container[0].des);
        printf("des is %s\n",transport_ob.container[0].des);
        if (msgsnd(msgid, &msg_ctn[i], sizeof(struct msg_str),0) == -1) {
                perror("Erreur de lecture 3\n");
                exit(1);
        }
        msg_ctn[i].type = 1;
        msg_ctn[i].nb_ctn = juge_destination(transport_ob.container[1].des);
        printf("des is %s\n",transport_ob.container[1].des);
        if (msgsnd(msgid, &msg_ctn[i], sizeof(struct msg_str),0) == -1) {
                perror("Erreur de lecture 4\n");
                exit(1);
            }
        Nb_boat --;
        pthread_mutex_unlock(&mutex);
    }
    else if(i == 4 || i == 5 || i == 6 || i == 7)
    {
        printf("truck %d arrives\n", transport_ob.i - 4);
        Nb_truck ++;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&tsleep);
        pthread_cond_wait(&twait, &mutex);
        printf("truck %d is the first in line\n", transport_ob.i - 4);
        sleep(2);
        msg_ctn[i].type = 1;
        msg_ctn[i].nb_ctn = juge_destination(transport_ob.container[0].des);
        printf("des is %s\n",transport_ob.container[0].des);
        if (msgsnd(msgid, &msg_ctn[i], sizeof(struct msg_str),0) == -1) {
                perror("Erreur de lecture 5\n");
                exit(1);
            }
        Nb_truck --;
        pthread_mutex_unlock(&mutex);
    }
}
//function of boat
void * func_transport(int i){
    //define index of tranport depends on i
    transport_obj[i].i = i;
    //define parameters of transports for testing
    for(int j = 0; j < 4; j++){
        transport_obj[j].Nb_container = 2;
    }
    for(int k = 4; k < 8; k++){
        transport_obj[k].Nb_container = 1;
    }
    strcpy(transport_obj[0].container[0].des,"tn_0");
    strcpy(transport_obj[0].container[1].des,"tk_0");
    strcpy(transport_obj[1].container[0].des,"tn_1");
    strcpy(transport_obj[1].container[1].des,"tk_1");
    strcpy(transport_obj[2].container[0].des,"bo_0");
    strcpy(transport_obj[2].container[1].des,"tk_2");
    strcpy(transport_obj[3].container[0].des,"bo_1");
    strcpy(transport_obj[3].container[1].des,"tk_3");
    strcpy(transport_obj[4].container[0].des,"bo_0");
    strcpy(transport_obj[5].container[0].des,"bo_1");
    strcpy(transport_obj[6].container[0].des,"tn_0");
    strcpy(transport_obj[7].container[0].des,"tn_1");
    transport(i, transport_obj[i]);
    pthread_exit(NULL);
}
//function of transport management
void transport_manager(){
    int j = 0;
    while(1){
        pthread_mutex_lock(&mutex);
        if(Nb_truck > 0 || Nb_boat > 0 || Nb_train > 0){
            pthread_mutex_unlock(&mutex);
            pthread_cond_signal(&twait);
            sleep(1);
            printf("the portique is working, please wait\n");
            //works to do:
            //juge if semaphore is available
            sem_wait(&sem);
            printf("the work is done\n");
            sleep(2);
            pthread_mutex_unlock(&mutex);
            j++;
        }else{
            pthread_cond_wait(&tsleep, &mutex);
        }
        if(j>8){
            break;
        }
    }
}
//function of transport management
void * func_transport_manager(void* arg){
    transport_manager();
    pthread_exit(NULL);
}

int cre_transport(){
    pid_t pid;
    int i;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&twait, NULL);
    pthread_cond_init(&tsleep,NULL);
    
    pthread_create(transportId+8,0,func_transport_manager,8);
    //i = 0~1 : boat
    //i = 2~3 : train
    //i = 4~7 : truck
    for(i = 0;i < 8;i++){
        pthread_create(transportId+i, NULL, func_transport, i);
    }
    
    pthread_join(transportId+8, NULL);
    for(i = 0;i < 8;i++){
        pthread_join(transportId[i], NULL);
    }
    
    
    return pid;
}

void portique(){
    int j = 0;
    sleep(2);
    while(j<9){
        sem_post(&sem);//make portique available
        if ((ctn =
                 msgrcv(msgid, &msg_rcv[j], sizeof(struct msg_str), 1,
                        0)) == -1) {
                perror("Erreur de rcv \n");
        }
        if(msg_rcv[j].nb_ctn == 0){
            strcpy(transport_obj_final[0].container[0].des,"bo_0");
            strcpy(transport_obj_final[0].container[1].des,"bo_0");}
        else if (msg_rcv[j].nb_ctn == 1){
            strcpy(transport_obj_final[1].container[0].des,"bo_1");
            strcpy(transport_obj_final[1].container[1].des,"bo_1");}
        else if (msg_rcv[j].nb_ctn == 2){
            strcpy(transport_obj_final[2].container[0].des,"tn_0");
            strcpy(transport_obj_final[2].container[1].des,"tn_0");}
        else if (msg_rcv[j].nb_ctn == 3){
            strcpy(transport_obj_final[3].container[0].des,"tn_1");
            strcpy(transport_obj_final[3].container[1].des,"tn_1");}
        else if (msg_rcv[j].nb_ctn == 4){
            strcpy(transport_obj_final[4].container[0].des,"tk_0");}
        else if (msg_rcv[j].nb_ctn == 5){
            strcpy(transport_obj_final[5].container[0].des,"tk_1");}
        else if (msg_rcv[j].nb_ctn == 6){
            strcpy(transport_obj_final[6].container[0].des,"tk_2");}
        else if (msg_rcv[j].nb_ctn == 7){
            strcpy(transport_obj_final[7].container[0].des,"tk_3");
        }
        j++;
    }
    final_output(transport_obj_final);
}

int main(int argc, char *argv[]){
    origin_output();
    if ((key = ftok(argv[0], 'A')) == -1) {
        perror("Erreur de creation de la clé \n");
        exit(1);
        }
    if ((msgid = msgget(key, 0600|IPC_CREAT)) == -1) {
        perror("Erreur de creation de la file\n");
        exit(1);
        }
    sem_open("sem", O_CREAT|O_EXCL, S_IRWXU, 0);
    int pid = fork();
    if(pid != 0){
        int transport = cre_transport();
    }
    portique();
    sem_unlink("sem");
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
