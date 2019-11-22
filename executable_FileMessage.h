void createFileMessage(){

    // FILE DE MESSAGE GLOBALE 
    if ((global_file = msgget(CLEF_global_file, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
        perror("Erreur de creation de la file fileMSG_0 \n");
        exit(1);
    }else{
        printf("\n[1] FILE DE MESSAGE: Créée avec succès.\n");
    }

    // STREAM FILE 
    if ((stream_file = msgget(CLEF_stream_file, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
        perror("Erreur de creation de la file fileMSG_0 \n");
        exit(1);
    }else{
        printf("\n[1] FILE DE MESSAGE: Créée avec succès.\n");
    }
}

void pushInFile(processus proc){
    int res = msgsnd(global_file, &proc, sizeof(processus)-sizeof(long), 0);
    if(res == -1 ){
        perror("msgsnd"); exit(0);
    }else{
      //printf(" Envoyé dans la File.\n");
    }
}


void pushInStreamFile(processus proc){

    int res = msgsnd(stream_file, &proc, sizeof(processus)-sizeof(long), 0);
    if(res == -1 ){
        perror("msgsnd"); exit(0);
    }else{
      //printf(" Envoyé dans la File.\n");
    }
}

