#define CLEF_priorite_0 0x00000000
#define CLEF_priorite_1 0x00000001
#define CLEF_priorite_2 0x00000002
#define CLEF_priorite_3 0x00000003
#define CLEF_priorite_4 0x00000004
#define CLEF_priorite_5 0x00000005
#define CLEF_priorite_6 0x00000006
#define CLEF_priorite_7 0x00000007
#define CLEF_priorite_8 0x00000008
#define CLEF_priorite_9 0x00000009
#define CLEF_priorite_10 0x00000010

void creationFilesDeMessage()
{

    int fileMSG_0;
    int fileMSG_1;
    int fileMSG_2;
    int fileMSG_3;
    int fileMSG_4;
    int fileMSG_5;
    int fileMSG_6;
    int fileMSG_7;
    int fileMSG_8;
    int fileMSG_9;
    int fileMSG_10;

    printf("\n");

    if ((fileMSG_0 = msgget(CLEF_priorite_0, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_0 \n");
      exit(1);
    }

    if ((fileMSG_1 = msgget(CLEF_priorite_1, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_1 \n");
      exit(1);
    }

    if ((fileMSG_2 = msgget(CLEF_priorite_2, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_2 \n");
      exit(1);
    }

    if ((fileMSG_3 = msgget(CLEF_priorite_3, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_3 \n");
      exit(1);
    }

    if ((fileMSG_4 = msgget(CLEF_priorite_4, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_4 \n");
      exit(1);
    }

    if ((fileMSG_5 = msgget(CLEF_priorite_5, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_5 \n");
      exit(1);
    }

    if ((fileMSG_6 = msgget(CLEF_priorite_6, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_6 \n");
      exit(1);
    }

    if ((fileMSG_7 = msgget(CLEF_priorite_7, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_7 \n");
      exit(1);
    }

    if ((fileMSG_8 = msgget(CLEF_priorite_8, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_8 \n");
      exit(1);
    }

    if ((fileMSG_9 = msgget(CLEF_priorite_9, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_9 \n");
      exit(1);
    }

    if ((fileMSG_10 = msgget(CLEF_priorite_10, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
      perror("Erreur de creation de la file fileMSG_10 \n");
      exit(1);
    }

}