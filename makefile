all : exec

exec : executable_StructProcessus.o executable_Fichier.o executable_FileMessage.o executable_CreateProcessus.o executable_PROCESSEUR_REPARTITEUR.o executable.o 
	gcc -o exec  executable_StructProcessus.o executable_Fichier.o executable_FileMessage.o executable_CreateProcessus.o executable_PROCESSEUR_REPARTITEUR.o executable.o 
	
executable_StructProcessus.o: executable_StructProcessus.h
	gcc -o executable_StructProcessus.o -c executable_StructProcessus.h

executable_Fichier.o: executable_Fichier.h
	gcc -o executable_Fichier.o -c executable_Fichier.h

executable_FileMessage.o: executable_FileMessage.h
	gcc -o executable_FileMessage.o -c executable_FileMessage.h

executable_CreateProcessus.o: executable_CreateProcessus.h
	gcc -o executable_CreateProcessus.o -c executable_CreateProcessus.h

executable_PROCESSEUR_REPARTITEUR.o: executable_PROCESSEUR_REPARTITEUR.h
	gcc -o executable_PROCESSEUR_REPARTITEUR.o -c executable_PROCESSEUR_REPARTITEUR.h

executable.o: executable.c
	gcc -o executable.o -c executable.c -lpthread
