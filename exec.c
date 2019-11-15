#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "exec.h"
#include "generateurProcessus.h"

int main(void)
{
    printf("*********************************************************************\n");
    printf("Simulation de ROUND ROBIN AVEC PRIORITÉ - [PID:%d - PPID:%d] \n", getpid(), getppid() );
    printf("*********************************************************************\n");

    printf("\n");

    int retour = fork();

    if(retour == 0 ){

      printf("[* P1 *] Générateur de processus: LANCÉ [PID:%d - PPID:%d] \n", getpid(), getppid() );
      generateurProcessus();

    }else{

      retour = fork();

      if(retour == 0 ){
        
        printf("[* P2 *] Gestionnaire CPU: LANCÉ [PID:%d - PPID:%d] \n", getpid(), getppid() );
        while(1){
          //
          sleep(0.1);
        }

      }else{
        retour = fork();
        if(retour == 0 ){
          printf("[* P3 *] Superviseur: LANCÉ [PID:%d - PPID:%d] \n", getpid(), getppid() );

          while(1){
            //
            sleep(0.1);
          }

        }else{
          retour = fork();
          if(retour == 0 ){
            printf("[* P4 *] Repartiteur: LANCÉ [PID:%d - PPID:%d] \n", getpid(), getppid() );
            while(1){
              //
              sleep(0.1);
            }
          }else{
            while(1){
              //
              sleep(0.1);
            }
          }
        }
      }
    }

    return EXIT_SUCCESS;
}
