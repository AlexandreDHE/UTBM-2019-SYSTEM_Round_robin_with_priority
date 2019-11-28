int* lectureTableCPU(){
    int* tableCPU;
    int caractereActuel = 0;
    int i = 0;
    int j = 0;
    char chaine[3];

    fichier = fopen("tableCPU.txt", "r");
 
    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un
        do
        {   
            caractereActuel = fgetc(fichier); 

            if(caractereActuel == ':'){
                if(i == 89 ){
                    fscanf(fichier, "%d", &caractereActuel);
                    tableCPU = malloc(caractereActuel*sizeof(int));
                }else{
                    fscanf(fichier, "%d", &caractereActuel);
                    tableCPU[j] = caractereActuel;
                    j++;
                }
            }

            i++;

        } while (caractereActuel != EOF); 
 
        fclose(fichier);
    }

    return tableCPU;

}

long* jeu_de_test(){

    long* tableau;
    int caractereActuel = 0;
    int i = 0;
    int j = 1;
    char chaine[3];

    fichier = fopen("jeu_de_test.txt", "r");
 
    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un
        do
        {   
            caractereActuel = fgetc(fichier); 

            if(caractereActuel == ':'){
                if(i == 35){
                    fscanf(fichier, "%d", &caractereActuel);
                    tableau = malloc(1+4*caractereActuel*sizeof(long));
                }else{
                    fscanf(fichier, "%d", &caractereActuel);
                    tableau[j] = caractereActuel;
                    j++;
                }
            }

            i++;

        } while (caractereActuel != EOF); 
 
        fclose(fichier);
        tableau[0] = j;

    }

    return tableau;

}

void ecritureProcessusGeneres(FILE* fichier, long priorite, int tempsExecution, int dateSoumission, int pid){
    
    fichier = fopen("./processusGeneres.txt", "a+");
    
    if (fichier != NULL)
    {   
        fseek(fichier,0, SEEK_END);
        fprintf(fichier, "New processus ( Priorité = %ld       TempsExec = %d TIC       DateSoumission = %d)      [PID: %d]\n",priorite, tempsExecution, dateSoumission, pid );
        fflush(fichier);
        fclose(fichier);
    }

}