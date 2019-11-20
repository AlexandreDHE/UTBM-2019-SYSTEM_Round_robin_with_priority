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



void ecritureProcessusGeneres(FILE* fichier, long priorite, int tempsExecution, int dateSoumission, int pid){
    
    fichier = fopen("./processusGeneres.txt", "a+");
    
    
    if (fichier != NULL)
    {   
        fseek(fichier,0, SEEK_END);
        fprintf(fichier, "[2] new processus ( Priorité = %ld       TempsExec = %d TIC       DateSoumission = %d)      [PID: %d]\n",priorite, tempsExecution, dateSoumission, pid );
        fflush(fichier);
        fclose(fichier);

    }

}