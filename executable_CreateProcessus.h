void createProcessus(int nombreProcessus){
    
    int resFork; 

    if(nombreProcessus == 0 ){

    }else{
        nombreProcessus--;
        long priorite = (long) (rand()%4)+1;
        int tempsExecution = (rand()%6)+1;
        int dateSoumission = timer; 

        if((resFork = fork()) == 0 ){
            
            processus proc;
            proc.priorite = priorite;
            proc.tempsExecution =  tempsExecution;
            proc.dateSoumission = dateSoumission ; 
            proc.pid = getpid();

            printf("                              [2] new processus ( Priorité = %ld       TempsExec = %d TIC       DateSoumission = %d)      [PID: %d]\n", proc.priorite, proc.tempsExecution, proc.dateSoumission, proc.pid );

            pushInFile(proc);
            ecritureProcessusGeneres(fichier, proc.priorite, proc.tempsExecution, proc.dateSoumission, proc.pid);
            
            // p(0) ou v(0) -> SEMAPHORES
            
            while(1){sleep(10);}

        }else{
            sleep(0.2);
            createProcessus(nombreProcessus);
        }
    }
}