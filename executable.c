#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/sem.h>

int timer = 0;
int quantum = 0;

int nbTIC = 3;



int global_file;
int stream_file;

#define IFLAGS (SEMPERM | IPC_CREAT)
#define SKEY   (key_t) IPC_PRIVATE	
#define SEMPERM 0600		 /* Permission */

int sem_id ;
struct sembuf sem_oper_P ;  
struct sembuf sem_oper_V ;
    
FILE* fichier = NULL;

#define CLEF_global_file 0x00000000
#define CLEF_stream_file 0x00000001

#include "executable_Fichier.h"
#include "executable_StructProcessus.h"
#include "executable_FileMessage.h"
#include "executable_CreateProcessus.h"
#include "executable_PROCESSEUR_REPARTITEUR.h"

int initsem(key_t semkey) 
{
	int status = 0;		
	int semid_init;

	// Structure definie pour le systeme ->
   	union semun {
		int val;
		struct semid_ds *stat; 
		short * array;
	} ctl_arg;

    if ((semid_init = semget(semkey, 2, IFLAGS)) > 0) {
		
		// Tableau de semaphores
		short array[2] = {0, 0};
		ctl_arg.array = array;
		status = semctl(semid_init, 0, SETALL, ctl_arg); /* Prend la structure et met dans le tableau de sémaphores */
		}

   if (semid_init == -1 || status == -1) { 
	perror("Erreur initsem");
	return (-1);
	} else {
		return (semid_init);
	}
}

// semnum identifiant du semaphore das le tableau
 
int P(int semnum) {
    //printf("JE BLOQUE le semaphore %d\n ", semnum);
	sem_oper_P.sem_num = semnum;
	sem_oper_P.sem_op  = -1 ; // On decremente de 1
	sem_oper_P.sem_flg = 0 ;
	return semop(sem_id,&sem_oper_P,1); // On opère ici le changement sur le semaphore 
}

int V(int semnum) {
    //printf("JE LIBERE le semaphore %d\n ", semnum);
	sem_oper_V.sem_num = semnum;
	sem_oper_V.sem_op  = 1 ; 
	sem_oper_V.sem_flg  = 0 ;	
	return semop(sem_id,&sem_oper_V,1); // On opère ici le changement sur le semaphore 
}

void recursivite_processeur(int* tableCPU, int quantum, int temps_a_consommer){

    processus proc1;
    processus proc2;

    long priorite;

    printf("[3] Quantum: %d (Table d’allocation CPU => Processus de priorité: %d) \n", quantum, tableCPU[quantum]);
    
    priorite = repartiteur_want_processus(tableCPU[quantum], proc1);
    proc2 = repartiteur_msgrcv_processus(priorite, proc2);
    printf("PROCESSUS A EXECUTER     [ Priorité = %ld       TempsExec = %d       DateSoumission = %d       PID: %d ] \n", proc2.priorite, proc2.tempsExecution, proc2.dateSoumission, proc2.pid);
    
    proc2 = processeur(proc2, temps_a_consommer);

    if (proc2.priorite != -1){
        // processus sup a 3
        printf("[PROCESSUS A CHANGE      [ Priorité = %ld       TempsExec = %d       DateSoumission = %d       PID: %d ] \n\n", proc2.priorite, proc2.tempsExecution, proc2.dateSoumission, proc2.pid);
        V(0); //Je libere le GENERATEUR
        P(1); // Je ME bloque
        
        repartiteur_push_in_file(proc2);

    }else {
        // processus =3 / =2 / =1
        if (proc2.tempsExecution != 0 ){
            printf("il me reste %d tic a utiliser\n", proc2.tempsExecution );
            recursivite_processeur(tableCPU, quantum, proc2.tempsExecution );
        }else {
            V(0); //Je libere le GENERATEUR
            P(1); // Je ME bloque
        }
    }

}


int main(int argc, char *argv[])
{

    printf("*********************************************************************\n");
    printf("* Simulation de ROUND ROBIN AVEC PRIORITÉ - [PID:%d - PPID:%d] *\n", getpid(), getppid() );
    printf("*********************************************************************\n");

    int* tableCPU = lectureTableCPU();
    int resFork;

    if((sem_id = initsem(SKEY)) < 0) return(1);

    //CREATION DE LA FILE DE MESSAGE
    createFileMessage();

    if((resFork = fork()) == 0 ){

        printf("[2] GÉNÉRATEUR DE PROCESSUS: En marche.\n");
        printf("[3] RÉPARTITEUR DE PROCESSUS: En marche (Vitesse en fonction du temps d'execution des processus par le processeur).\n");
        printf("[4] PROCESSEUR: En marche (1 QUANTUM = 3 tics).\n\n");

        while(1){

            printf("\n-------------------------------------------------------------------------------------------------------------------------------------\n\n");


            if(quantum == 11){
                quantum = 0;
            }

            printf("\nGENERATEUR                    * QUANTUM: %d -- Timer: %d *\n",quantum, timer);

            if((resFork = fork()) == 0 ){
                int nombreProcessus = rand()%(4 +1);
                createProcessus(nombreProcessus);

            }else{
                while(1){sleep(10);};
            }

            sleep(1);


            timer++;
            quantum++;

            V(1); // Je libère PROCESSEUR
            P(0); // Je me bloque
            
        }

    }else {

        if((resFork = fork()) == 0 ){

            int quantum = 0;
            
            while(1){

                

                if(timer == 0){
                    P(1); // Je ME bloque
                }

                if(quantum == 11){
                    quantum = 0;
                }

                printf("\n\nPROCESSEUR                    * QUANTUM: %d -- Timer: %d *\n",quantum, timer);
             
                recursivite_processeur(tableCPU, quantum, nbTIC);

                sleep(1);
                quantum++;
                timer++;

            }

        }else{
            while(1){sleep(10);}
        }
    }

    free(tableCPU);
    semctl(sem_id, 0, IPC_RMID);

    return EXIT_SUCCESS;
}