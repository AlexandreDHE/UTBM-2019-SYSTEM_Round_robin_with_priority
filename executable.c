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

int timer = 0; // Quantum en cours 
int quantum = 0; // Valeur du quantum dans la table CPU
int vitesse = 1;

int periode = 1 ; // La periode de remise en question du processus à executer 

int global_file; // File de message globale (File d'attente des processus)
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

#include "executable_StructProcessus.h"
#include "executable_Fichier.h"
#include "executable_FileMessage.h"
#include "executable_CreateProcessus.h"
#include "executable_PROCESSEUR_REPARTITEUR.h"

//INITIALISATION SEMAPHORES 
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

    processus proc1; // Creation d'une structure de processus pour 
    processus proc2; // Creation d'une structure de processus pour recuperer la structure du processus à executer

    long priorite; 

    printf("\n[3] Quantum: %d (Table d’allocation CPU => Processus de priorité: %d) \n", quantum, tableCPU[quantum]);
    
    priorite = repartiteur_want_processus(tableCPU[quantum], proc1); // Le repartiteur pousse dans filestream le bon processus à executer suivant la table CPU
    proc2 = repartiteur_msgrcv_processus(priorite, proc2); // Le repartiteur recupère dans filestream le processus devant etre executer
    printf("PROCESSUS A EXECUTER     [ Priorité = %ld       TempsExec = %d       DateSoumission = %d       PID: %d ] \n", proc2.priorite, proc2.tempsExecution, proc2.dateSoumission, proc2.pid);
    
    proc2 = processeur(proc2, temps_a_consommer); // Execution du processus par le processeur

    if (proc2.priorite != -1){ // Si le temps d'execution n'est pas terminé, on renvoie dans la file de message le processus apres un le prochain quantum
        printf("[PROCESSUS A CHANGE      [ Priorité = %ld       TempsExec = %d       DateSoumission = %d       PID: %d ] \n\n", proc2.priorite, proc2.tempsExecution, proc2.dateSoumission, proc2.pid);
        V(0); //Libération du generateur pour création de nouveaux processus
        P(1); //Blocage du processeur
        
        repartiteur_push_in_file(proc2); // Envoie du processus dans la file apres l'arrivée des nouveaux processus

    }else {

        printf("JE NE FAIT RIEN \n");
        V(0); //Libération du generateur pour création de nouveaux processus
        P(1); //Blocage du processeur
    }
}


int main(int argc, char *argv[])
{

    printf("*********************************************************************\n");
    printf("* Simulation de ROUND ROBIN AVEC PRIORITÉ - [PID:%d - PPID:%d] *\n", getpid(), getppid() );
    printf("*********************************************************************\n\n");

    char val[1]= {0}; // Variable pour la saisie
  
    printf("Choisissez votre mode: \n [1] Génération Automatique\n [2] Generation a partir du fichier 'Jeu_de_test.text'\n\nChoix:  ");
    scanf("%s", val);
    int choix;
    choix = (int) strtol(val, (char **)NULL, 10);
    
    printf("\nChoisissez la valeur du quantum: ");
    scanf("%s", val);
    periode = (int) strtol(val, (char **)NULL, 10);

    printf("\nChoisissez la vitesse d'execution: ");
    scanf("%s", val);
    vitesse = (int) strtol(val, (char **)NULL, 10);

    // Initialisation de la table CPU dans le systeme
    int* tableCPU = lectureTableCPU();
   
    long* tableau = jeu_de_test();
    int n=0; // Toutes les 4 valeurs du tableau de processus a executer (Date arrivée)

    // Initialisation des semaphores
    if((sem_id = initsem(SKEY)) < 0) return(1);

    //CREATION DE LA FILE DE MESSAGE
    createFileMessage();

    int resFork; 
    // GENERATEUR DE PROCESSUS // 
    if((resFork = fork()) == 0 ){

        printf("[2] GÉNÉRATEUR DE PROCESSUS: En marche.\n");
        printf("[3] RÉPARTITEUR DE PROCESSUS: En marche (Vitesse en fonction du temps d'execution des processus par le processeur).\n");
        printf("[4] PROCESSEUR: En marche (Processeur s'execute tous les %d QUANTUMS).\n\n", periode);

        while(1){

            printf("\n-------------------------------------------------------------------------------------------------------------------------------------\n\n");

            if(quantum == 56){  /*************** *****************/  
                quantum = 0;
            }

            printf("\nGENERATEUR                    * QUANTUM: %d -- Timer: %d *\n",quantum, timer);

            if((resFork = fork()) == 0 ){

                if (choix == 1 ){ // Génerateur automatique des processus
                    int nombreProcessus = rand()%(4 +1);
                    createProcessus(nombreProcessus, -1 , -1 , -1 , -1);
                }//else if(choix == 2) { // Generateur par lecture simple du fichier de creation

                    for(int i=1; i<tableau[0]; i++){
                        if(tableau[n*4+1] == quantum){ // Si la date de soumission du processus (toutes les 4 valeurs du tableau) = quantum actuel alors creer le processus            
                            createProcessus(-1, (long)tableau[n*4+1] , (int)tableau[n*4+2] ,(int)tableau[n*4+3] , (int)tableau[n*4+4]);
                            n++;
                        }
                    }  
                //}
                        
            }else{
                while(1){
                    sleep(10);};
            }

            sleep(vitesse);

            timer++; // On passe au quantum suivant 
            quantum++; // on passe au quantum suivant dans la table CPU 

            V(1); // Le générateur libère PROCESSEUR
            P(0); // Le générateur se bloque

        }

    // REPARTITEUR ET GENERATEUR // 
    }else {

        if((resFork = fork()) == 0 ){

            int quantum = 0;
            
            while(1){

                if(timer == 0){
                    P(1); // Le processeur commence par se bloquer pour laisser place a la création des premiers processus (Generateur)
                }

                if(quantum == 56){ /********************************** ALERTE ************/
                    quantum = 0;
                }

                printf("\n\n\n\nPROCESSEUR                    * QUANTUM: %d -- Timer: %d *\n",quantum, timer);
             
             
                if(timer%periode == 0){
                    recursivite_processeur(tableCPU, quantum, periode);
                }else {
                    V(0); //Libération du generateur pour création de nouveaux processus
                    P(1); //Blocage du processeur
                }
                

                sleep(vitesse);
                timer++; // On passe au quantum suivant 
                quantum++; // on passe au quantum suivant dans la table CPU 

            }

        }else{
            while(1){
                /*do{
                    scanf("%s", val);
                }while(val[0] != 'q' );
                printf(" EXIT\n");
                free(tableCPU);
                semctl(sem_id, 0, IPC_RMID);
                semctl(sem_id, 1, IPC_RMID);

                msgctl(global_file, IPC_RMID, NULL);
                msgctl(stream_file, IPC_RMID, NULL);*/
            }
   
        }
    }

    return EXIT_SUCCESS;
}