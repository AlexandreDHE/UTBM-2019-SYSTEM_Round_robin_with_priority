
/* Pour les constantes EXIT_SUCCESS et EXIT_FAILURE */
#include <stdlib.h>
/* Pour fprintf() */
#include <stdio.h>
/* Pour fork() */
#include <unistd.h>
/* Pour perror() et errno */
#include <errno.h>
/* Pour le type pid_t */
#include <sys/types.h>
/* Pour rand */
#include <time.h>
/* Pour wait() */
#include <sys/wait.h>
#include "exec.h"

/* Fonction qui retourne un nombre aléatoire entre les bornes a et b */
double frand_a_b(double a, double b){
    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

/* Fonction récursive qui a partir d'un processus pere commun, créé des fils */
void newProcess(void)
{
  float f = frand_a_b(0.2,3); /*Temps de latence aléatoire dans la création de processus */
  sleep(f);
  int retour = fork();
  if(retour == 0 ){

    struct Processus proc;
    proc.pid = getpid();
    proc.poids = rand()%10+1;
    proc.timeExec = rand()%15+1;
    printf("    [* P1 *] NEW PROCESSUS [PID:%d - PPID:%d - POIDS:%d - TIME EXEC:%d ] \n", proc.pid , getppid(), proc.poids, proc.timeExec ); //PPID COMMUN A TOUS LES PROCESSUS

    while(1){
      //sleep(10);
      //printf(" ............................................[FILS PID:%d  -- PPID:%d] \n", getpid(), getppid());
    }
  }else{
    newProcess();
  }
}

int main(void)
{
    printf("*********************************************************************\n");
    printf("Simulation de ROUND ROBIN AVEC PRIORITÉ - [PID:%d - PPID:%d] \n", getpid(), getppid() );
    printf("*********************************************************************\n");

    printf("\n");

    int retour = fork();

    if(retour == 0 ){

      printf("[* P1 *] Générateur de processus: LANCÉ [PID:%d - PPID:%d] \n", getpid(), getppid() );
      retour = fork();
      if(retour == 0 ){
        sleep(1);

        struct Processus proc;
        proc.pid = getpid();
        proc.poids = rand()%10+1;
        proc.timeExec = rand()%15+1;
        printf("    [* P1 *] NEW PROCESSUS [PID:%d - PPID:%d - POIDS:%d - TIME EXEC:%d ] \n", proc.pid , getppid(), proc.poids, proc.timeExec ); //PPID COMMUN A TOUS LES PROCESSUS

        while(1){
          //sleep(10);
          //printf(" ............................................[FILS PID:%d  -- PPID:%d] \n", getpid(), getppid());
        }
      }else{
        newProcess();
      }

    }else{

      retour = fork();
      if(retour == 0 ){
        printf("[* P2 *] Gestionnaire CPU: LANCÉ [PID:%d - PPID:%d] \n", getpid(), getppid() );
        while(1){
          sleep(0.1);
        }
      }else{
        retour = fork();
        if(retour == 0 ){
          printf("[* P3 *] Superviseur: LANCÉ [PID:%d - PPID:%d] \n", getpid(), getppid() );
          while(1){
            sleep(0.1);
          }
        }else{
          retour = fork();
          if(retour == 0 ){
            printf("[* P4 *] Repartiteur: LANCÉ [PID:%d - PPID:%d] \n", getpid(), getppid() );
            while(1){
              sleep(0.1);
            }
          }else{
            while(1){
              sleep(0.1);
            }
          }
        }
      }
    }

    return EXIT_SUCCESS;
}
