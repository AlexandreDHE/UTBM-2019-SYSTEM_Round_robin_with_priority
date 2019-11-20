void work_processeur(){

}

processus repartiteur_want_processus(int priorite, processus proc){

int longMSG;

  if(priorite == 1 ){
    if ((longMSG = msgrcv(global_file, &proc, sizeof(processus) - 4, 1, IPC_NOWAIT)) == -1) {
	  perror("Erreur de lecture requete \n");exit(1);}else{ return proc;}
  }else if(priorite == 2 ){
    if ((longMSG = msgrcv(global_file, &proc, sizeof(processus) - 4, 2, IPC_NOWAIT)) == -1) {
	  perror("Erreur de lecture requete \n");exit(1);}else{ return proc;}
  }else if(priorite == 3 ){
    if ((longMSG = msgrcv(global_file, &proc, sizeof(processus) - 4, 3, IPC_NOWAIT)) == -1) {
	  perror("Erreur de lecture requete \n");exit(1);}else{ return proc;}
  }else {
    if ((longMSG = msgrcv(global_file, &proc, sizeof(processus) - 4, 4, IPC_NOWAIT)) == -1) {
	  perror("Erreur de lecture requete \n");exit(1);}else{ return proc;}
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
            sleep(timeSYSTEME);
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
            sleep(timeSYSTEME);
        }
        printf("PROCESSEUR          [4] [Terminé] \n");
        printf("**********          [3] [Fin] \n\n");

        return proc;
    }
    
}

