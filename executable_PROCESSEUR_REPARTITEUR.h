void work_processeur(){

}

void repartiteur_want_processus(int priorite, processus proc){

    int longMSG;

    //printf("Je cherche dans la priorité: %d\n", priorite);

    if ((longMSG = msgrcv(global_file, &proc, sizeof(processus) - 4, priorite, IPC_NOWAIT)) == -1) {
        //printf("ERROR\n");
        priorite = priorite +1;
        repartiteur_want_processus(priorite, proc);
    }else{ 
        //printf("GOOD\n");
        printf("Requete (FM)            [PROCESSUS A EXECUTER     Priorité = %ld       TempsExec = %d       DateSoumission = %d       PID: %d ] \n", proc.priorite, proc.tempsExecution, proc.dateSoumission, proc.pid);
    }
}

void repartiteur_push_in_file(processus proc){
    int res = msgsnd(global_file, &proc, sizeof(processus)-sizeof(long), 0);
    if(res == -1 ){
        perror("msgsnd"); exit(0);
    }
}

processus processeur(processus proc){

    int i = 1;

    if((proc.tempsExecution - quantum) > 0 ){
        proc.priorite = proc.priorite+1 ;
        proc.tempsExecution = proc.tempsExecution-quantum;
        
        printf("PROCESSEUR          [4] [EXECUTION  %d tics] \n", quantum);
                
        for(i; i<=quantum; i++){
            sleep(1);
        }
        printf("PROCESSEUR          [4] [Terminé pour le moment] \n");
        printf("PROCESSEUR          [4] [PRIORITÉ -1] \n");

        return proc; 

    }else{
        sleep(proc.tempsExecution*1);
        proc.priorite = -1;
        proc.pid = -1;
        proc.dateSoumission = -1;

        printf("PROCESSEUR          [4] [EXECUTION  %d tics] \n", proc.tempsExecution);
        for(i; i<=proc.tempsExecution; i++){
            sleep(1);
        }
        
        printf("PROCESSEUR          [4] [Terminé] \n");
        printf("**********          [3] [Fin] \n\n");

        return proc;
    }
    
}

