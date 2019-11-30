long repartiteur_want_processus(int priorite, processus proc1, int nbTour){

    int longMSG;

    if(nbTour == 10){
        printf("quantum suivant");
        return 999;
    }

    if ((longMSG = msgrcv(global_file, &proc1, sizeof(processus) - 4, priorite, IPC_NOWAIT)) == -1) {
        
        if(priorite == 10){
            nbTour++;
            printf("tour Actuel: %d\n", nbTour);
            repartiteur_want_processus(1, proc1, nbTour );

        }else {
            priorite = priorite +1;
            nbTour++;
            printf("tour Actuel: %d\n", nbTour);
            repartiteur_want_processus(priorite, proc1, nbTour);
        }
        
    }else{ 
        pushInStreamFile(proc1);
        return proc1.priorite;
    }
}


processus repartiteur_msgrcv_processus(long priorite, processus proc1){

    int  longMSG;

    if ((longMSG = msgrcv(stream_file, &proc1, sizeof(processus) - 4, priorite, IPC_NOWAIT)) == -1) {
        printf("ERROR\n");
    }else{ 
        return proc1;
    }
}


void repartiteur_push_in_file(processus proc){
    
    int res = msgsnd(global_file, &proc, sizeof(processus)-sizeof(long), 0);
    
    if(res == -1 ){
        perror("msgsnd"); exit(0);
    }
}


processus processeur(processus proc, int temps_restant){

    int i = 1; 

    if((proc.tempsExecution - temps_restant) > 0 ){

        if(proc.priorite != 10){
            proc.priorite = proc.priorite+1 ;
        }

        proc.tempsExecution = proc.tempsExecution-temps_restant;
        
        printf("[4] [EXECUTION  %d] \n", temps_restant);
        printf("[4] [Terminé pour le moment] \n");
        printf("[4] [PRIORITÉ -1] \n");

        return proc; 

    }else{

        printf("[4] [EXECUTION  %d] \n", proc.tempsExecution);     
        printf("[4] [Terminé] \n");
        printf("[4] [Fin] \n\n");

        proc.priorite = -1;
        proc.pid = -1;
        proc.dateSoumission = -1;
        proc.tempsExecution = temps_restant - proc.tempsExecution;

        printf("\nNombre de Quantums restant: %d\n\n", proc.tempsExecution);

        return proc;
    }
}




