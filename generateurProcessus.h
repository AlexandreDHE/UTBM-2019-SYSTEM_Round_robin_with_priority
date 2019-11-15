/* Fonction qui retourne un nombre aléatoire entre les bornes a et b */
double frand_a_b(double a, double b){
    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

/* Fonction récursive qui a partir d'un processus pere commun, créé des fils */

void newProcess(void)
{
  float f = frand_a_b(0.2,3.0); /*Temps de latence aléatoire dans la création de processus */
  sleep(f);
  int retour = fork();

  if(retour == 0 ){

    requeteImProcessus processus;
    processus.priorite = rand()%10+0;
    processus.pid = getpid();
    processus.tempsExec = rand()%(16-0);
    processus.dateSoumission = 0;
    printf("    [* P1 *] NEW PROCESSUS [Priorité: %ld - PID: %d - TempsExec:%d ] \n", processus.priorite , processus.pid, processus.tempsExec ); //PPID COMMUN A TOUS LES PROCESSUS

    while(1){
      //sleep(10);
      //printf(" ............................................[FILS PID:%d  -- PPID:%d] \n", getpid(), getppid());
    }

  }else{
    newProcess();
  }
}


void generateurProcessus()
{    
    int retour = fork();
      
    if(retour == 0 ){
        
        sleep(1);

        requeteImProcessus processus;
        processus.priorite = rand()%10+0;
        processus.pid = getpid();
        processus.tempsExec = rand()%(16+0);
        processus.dateSoumission = 0;

        printf("\n");

        printf("    [* P1 *] NEW PROCESSUS [Priorité: %ld - PID: %d - TempsExec:%d ] \n", processus.priorite , processus.pid, processus.tempsExec ); //PPID COMMUN A TOUS LES PROCESSUS

        while(1){
          //sleep(10);
          //printf(" ............................................[FILS PID:%d  -- PPID:%d] \n", getpid(), getppid());
        }

    }else{
        newProcess();
      }
}