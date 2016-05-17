/*
Name: Tolga Bilbey
Number: 150130045
Date: 02.05.2016
*/
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define SEMKEY 8
#define KEYSHM 1
#define KEYSHM1 2
#define KEYSHM2 3

typedef struct question{
  char text[30];
  int approvals;
} Question;

typedef struct application{
  int exam_score;
  int interview_score;
  int total_score;
} ApplicationForm;

FILE *input;
Question *questions;
int sem_id;

void sem_signal(int semid, int val){
  struct sembuf semaphore;
  semaphore.sem_num=0;
  semaphore.sem_op=val;
  semaphore.sem_flg=1;
  semop(semid,&semaphore,1);
}

void sem_wait(int semid, int val){
  struct sembuf semaphore;
  semaphore.sem_num=0;
  semaphore.sem_op=(-1*val);
  semaphore.sem_flg=1;
  semop(semid,&semaphore,1);
}

void mysignal(int signum){
  //printf("Received signal with num=%d\n",signum);
}

void mysigset(int num){
  struct sigaction mysigaction;
  mysigaction.sa_handler=(void*)mysignal;
  mysigaction.sa_flags=0;
  sigaction(num,&mysigaction,NULL);
}

void *create_question(void *t){
  char line[100], line_members[3][30];
  int counter=0,index;
  char *token;
  fgets(line,100,input);
  token = strtok(line," ");
  while(token){
    strcpy(line_members[counter],token);
    counter++;
    token = strtok(NULL," ");
  }
  index = atoi(line_members[0])-1;
  sleep(atoi(line_members[2]));
  strcpy(questions[index].text,line_members[1]);
  questions[index].approvals=0;
  printf("WEC member %d: A question is prepared on %s\n",index+1,line_members[1]);
  pthread_exit(NULL);
}
//Registrar Process
int main(int argc, char *argv[]){
  mysigset(12);
  int i,j,T,M,I,f,m,shmid,shmid1,shmid2;
  int *num,*num1,*num2;
  T = atoi(argv[2]);
  M = atoi(argv[3]);
  I = atoi(argv[4]);
  ApplicationForm forms[3];
  f = fork();
  if(f!=0){
    printf("The Registrar started taking applications\n");
    sleep(3);
    printf("The Registrar finished taking applications\n");
    kill(f,12);
    wait(NULL);
  }
  //WEC Process
  else{
    pause();
    input = fopen(argv[1],"r");
    pthread_t thread[T];
    questions = (Question*)malloc(T*sizeof(Question));
    printf("The Written Exams Committee started preparing questions.\n");
    for(i=0;i<T;i++){
      if(pthread_create(&thread[i],NULL,create_question,NULL)){
        printf("error creating thread");
        abort();
      }
    }
    for(i=0;i<T;i++){
      pthread_join(thread[i],NULL);
    }
    sem_id = semget(SEMKEY,1, 0700|IPC_CREAT);
    semctl(sem_id,0,SETVAL,T);
    for(i=0;i<T;i++){
      sem_wait(sem_id,1);
      for(j=0;j<T;j++){
        if(i != j){
          sleep(1);
          questions[j].approvals++;
          if(questions[j].approvals == T-1){
            printf("WEC member %d: Question %d is ready\n",i+1,j+1);
          }
        }
      }
      sem_signal(sem_id,1);
    }
    printf("The Written Exams Committee finished preparing questions.\n");
    semctl(sem_id,0,IPC_RMID,0);
    fclose(input);
    exit(0);
  }
  m=fork();
  if(m!=0){
    printf("The Registrar started the written exam.\n");
    srand(time(NULL));
    sleep(M);
    for(i=0;i<3;i++){
      forms[i].exam_score = rand()%50;
      printf("Written exam score of applicant %d is %d.\n",i+1,forms[i].exam_score);
    }
    printf("The Registrar finished the written exam.\n");
    shmid=shmget(KEYSHM,sizeof(int),0700|IPC_CREAT);
    shmid1=shmget(KEYSHM1,sizeof(int),0700|IPC_CREAT);
    shmid2=shmget(KEYSHM2,sizeof(int),0700|IPC_CREAT);
    num = (int*)shmat(shmid,0,0);
    num1 = (int*)shmat(shmid1,0,0);
    num2 = (int*)shmat(shmid2,0,0);
    kill(m,12);
    wait(NULL);
    forms[0].interview_score = *num;
    forms[1].interview_score = *num1;
    forms[2].interview_score = *num2;
    printf("The Registrar started calculating total scores.\n");
    for(i=0;i<3;i++){
      forms[i].total_score = forms[i].exam_score + forms[i].interview_score;
      printf("Total score of applicant %d is %d.\n",i+1,forms[i].total_score);
    }
    printf("The Registrar finished calculating total scores.\n");
    shmdt(num);
    shmdt(num1);
    shmdt(num2);
    exit(0);
  }
  else{
    pause();
    printf("The Interviewer started interviews.\n");
    shmid=shmget(KEYSHM,sizeof(int),0700|IPC_CREAT);
    shmid1=shmget(KEYSHM1,sizeof(int),0700|IPC_CREAT);
    shmid2=shmget(KEYSHM2,sizeof(int),0700|IPC_CREAT);
    num = (int*)shmat(shmid,0,0);
    num1 = (int*)shmat(shmid1,0,0);
    num2 = (int*)shmat(shmid2,0,0);
    for(i=0;i<3;i++){
      sleep(I);
      forms[i].interview_score = rand()%50;
      if(i==0){
        *num=forms[i].interview_score;
      }
      else if(i==1){
        *num1=forms[i].interview_score;
      }
      else if(i==2){
        *num2=forms[i].interview_score;
      }
      printf("Interview score of applicant %d is %d.\n",i+1,forms[i].interview_score);
    }
    printf("The Interviewer finished interviews.\n");
    shmdt(num);
    shmdt(num1);
    shmdt(num2);
    exit(0);
  }
  shmctl(shmid,IPC_RMID,0);
  shmctl(shmid1,IPC_RMID,0);
  shmctl(shmid2,IPC_RMID,0);
  free(questions);
  return 0;
}
