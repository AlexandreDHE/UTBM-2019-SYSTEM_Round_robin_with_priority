void createProcessus(int nombreProcessus, long dateArrive, int priorite, int tempsExec, int pid){
    
    int resFork; 

    if(nombreProcessus == -1){
        processus proc;
        proc.priorite = priorite;
        proc.tempsExecution =  tempsExec;
        proc.dateSoumission = dateArrive ; 
        proc.pid = pid;
        
        printf("                              [2] new processus ( Priorité = %ld       TempsExec = %d Q      DateSoumission = %d)      [PID: %d]\n", proc.priorite, proc.tempsExecution, proc.dateSoumission, proc.pid );

        pushInFile(proc);
        ecritureProcessusGeneres(fichier, proc.priorite, proc.tempsExecution, proc.dateSoumission, proc.pid);
                

    }
    else {
        if(nombreProcessus == 0 ){

        }else{
            nombreProcessus--;
            
            long priorite = (long) (rand()%10)+1;
            int tempsExecution = (rand()%6)+1;
            int dateSoumission = timer; 

            if((resFork = fork()) == 0 ){
                
                processus proc;
                proc.priorite = priorite;
                proc.tempsExecution =  tempsExecution;
                proc.dateSoumission = dateSoumission ; 
                proc.pid = getpid();

                printf("                              [2] new processus ( Priorité = %ld       TempsExec = %d Q       DateSoumission = %d)      [PID: %d]\n", proc.priorite, proc.tempsExecution, proc.dateSoumission, proc.pid );

                pushInFile(proc);
                ecritureProcessusGeneres(fichier, proc.priorite, proc.tempsExecution, proc.dateSoumission, proc.pid);
                
                // p(0) ou v(0) -> SEMAPHORES
                
                exit(0);

            }else{
                sleep(0.2);
                createProcessus(nombreProcessus, -1, -1, -1, -1);
            }
        }
    }
}