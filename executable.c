#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int timeSYSTEME = 1;

int timeCREATION_PROCESSUS = 1;


int quantum = 3 ;
int timer;
int global_file;

#define CLEF_global_file 0x00000000

#include "executable_Fichier.h"
#include "executable_StructProcessus.h"
#include "executable_FileMessage.h"
#include "executable_CreateProcessus.h"
#include "executable_PROCESSEUR_REPARTITEUR.h"

int main(int argc, char *argv[])
{

    printf("*********************************************************************\n");
    printf("* Simulation de ROUND ROBIN AVEC PRIORITÉ - [PID:%d - PPID:%d] *\n", getpid(), getppid() );
    printf("*********************************************************************\n");

    int* tableCPU = lectureTableCPU();

    timer = 0;
    
    int resFork;

    //CREATION DE LA FILE DE MESSAGE
    createFileMessage();

    if((resFork = fork()) == 0 ){

        printf("[2] GÉNÉRATEUR DE PROCESSUS: En marche (x%d s).\n", timeCREATION_PROCESSUS);
        // GENERATEUR DE PROCESSUS 

        sleep(0.2);

        while(1){
            if(timer == 11){
                timer = 0;
            }
/*********/ //printf("\n                    * Horloge: %ds *\n", timer);

            if((resFork = fork()) == 0 ){
                int nombreProcessus = rand()%(3+1);
                createProcessus(nombreProcessus);
            }else{
                while(1){sleep(10);};
            }
            timer++;
            sleep(timeCREATION_PROCESSUS);
        }

        /*int temps = 11;

        for(temps = 0; temps<11; temps++){
            if(timer == 11){
                timer = 0;
            }
            printf("Timer: %d \n", timer);
            if((resFork = fork()) == 0 ){
                int nombreProcessus = rand()%(3+1);
                createProcessus(nombreProcessus);
            }else{
                while(1){sleep(10);};
            }
            timer++;
            sleep(timeCREATION_PROCESSUS);
        }

        printf("\nFin de la création des processus ... \n\n");

        while(1){sleep(10);}*/


    }else {

        if((resFork = fork()) == 0 ){

            printf("[3] RÉPARTITEUR DE PROCESSUS: En marche (Vitesse en fonction du temps d'execution des processus par le processeur).\n");
            printf("[4] PROCESSEUR: En marche (1 QUANTUM = %d s).\n\n", timeSYSTEME);
            
            
            
            
            
            sleep(4);
            // REPARTITEUR 
            int quantum = 0;

            while(1){
                
                printf("\n===================================================================================================================================================================================\n");
                
                if(quantum == 11){
                    quantum = 0;
                }

                processus proc;

                printf("\n                    [3] Quantum: %d (Table d’allocation CPU => Processus de priorité: %d) \n", quantum, tableCPU[quantum]);
                proc = repartiteur_want_processus(tableCPU[quantum], proc);
                printf("Requete (FM)            [PROCESSUS A EXECUTER     Priorité = %ld       TempsExec = %d       DateSoumission = %d       PID: %d ] \n", proc.priorite, proc.tempsExecution, proc.dateSoumission, proc.pid);
                proc = processeur(proc);
                if (proc.priorite != -1){
                    printf("RENVOIE (FM)            [CHANEGEMENT PROCESSUS    Priorité = %ld       TempsExec = %d       DateSoumission = %d       PID: %d ] \n\n", proc.priorite, proc.tempsExecution, proc.dateSoumission, proc.pid);
                    repartiteur_push_in_file(proc);
                }

                quantum++;
            }

        }else{
            while(1){sleep(10);}
        }
    }

    free(tableCPU);

    return EXIT_SUCCESS;
}