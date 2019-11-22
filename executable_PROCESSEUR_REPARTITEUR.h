void work_processeur(){

}

long repartiteur_want_processus(int priorite, processus proc1){

    int longMSG;

    //printf("Je cherche dans la priorité: %d\n", priorite);

    if ((longMSG = msgrcv(global_file, &proc1, sizeof(processus) - 4, priorite, IPC_NOWAIT)) == -1) {
        //printf("ERROR\n");
        priorite = priorite +1;
        repartiteur_want_processus(priorite, proc1);
    }else{ 
        //printf("GOOD\n");
        //printf("repartiteur want proc affichage            [PROCESSUS A EXECUTER     Priorité = %ld       TempsExec = %d       DateSoumission = %d       PID: %d ] \n", proc1.priorite, proc1.tempsExecution, proc1.dateSoumission, proc1.pid);
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
                                          /**2**/ 
processus processeur(processus proc, int temps_restant){

    int i = 1; 

    /*if (temps_restant == nbTIC ){

        if((proc.tempsExecution - nbTIC) > 0 ){

            if(proc.priorite != 10){
                proc.priorite = proc.priorite+1 ;
            }

            proc.tempsExecution = proc.tempsExecution-nbTIC;
            
            printf("[4] [EXECUTION  %d tics] \n", nbTIC);
            printf("[4] [Terminé pour le moment] \n");
            printf("[4] [PRIORITÉ -1] \n");

            return proc; 

        }else{

      

            printf("[4] [EXECUTION  %d tics] \n", proc.tempsExecution);     
            printf("[4] [Terminé] \n");
            printf("[4] [Fin] \n\n");

            proc.priorite = -1;
            proc.pid = -1;
            proc.dateSoumission = -1;
            proc.tempsExecution = nbTIC - proc.tempsExecution;
            printf("\n\nNb tic restant: %d\n\n", proc.tempsExecution);

            return proc;
        }

    }else {*/

        if((proc.tempsExecution - temps_restant) > 0 ){

            if(proc.priorite != 10){
                proc.priorite = proc.priorite+1 ;
            }

            proc.tempsExecution = proc.tempsExecution-temps_restant;
            
            printf("[4] [EXECUTION  %d tics] \n", temps_restant);
            printf("[4] [Terminé pour le moment] \n");
            printf("[4] [PRIORITÉ -1] \n");

            return proc; 

        }else{

            printf("[4] [EXECUTION  %d tics] \n", proc.tempsExecution);     
            printf("[4] [Terminé] \n");
            printf("[4] [Fin] \n\n");

            proc.priorite = -1;
            proc.pid = -1;
            proc.dateSoumission = -1;
            proc.tempsExecution = temps_restant - proc.tempsExecution;
            printf("\n\nNb tic restant: %d\n\n", proc.tempsExecution);

            return proc;
        }
        
    /*}*/

}




