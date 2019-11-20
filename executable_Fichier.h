int* lectureTableCPU(){

    FILE* fichier = NULL;
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