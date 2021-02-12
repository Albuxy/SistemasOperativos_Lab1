#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
#include <stdio.h>     /* printf, perror */
#include <stdlib.h>    /* exit */
#include <unistd.h>    /* _exit, fork */
#include <string.h>

#include "myutils.h"
#include "myutils.c"

int main(void)
{
// declaració de variable que utilitzarem al codi
    int ret;
    int status;
    char buff[80];
    char buff_aux[80][80];
    char s = ' ';
    char caracter[80] = "&";
    int cont =  0;

    for (int i = 0; i < 80; i++){ //bucle que ens llegueix el buff i ho copia al buff_aux
    	if (s != '\n'){
    	   int valor = readSplit( 0, buff, &s, 80);
	   if (valor != 0){
	       strcpy(buff_aux[i], buff);
	       if (strcmp(buff_aux[i],caracter)==0){ //mirem que no hi hagi cap caracter en el buffer, en aquest cas &
		   cont = 1;
		}
	   }	
	}
    }

    startTimer(); //comença el contador

    ret = fork(); //s'inicialitza el procés

    if (ret == 0) { 
	if (cont != 1){ //mira que no tinguem cap caracter
            execlp(buff,buff, NULL); //execució
            printf("Son: shell program does not exist\n");
            exit(255);
	    }
	exit(1);
    } 
    
    while(ret > 0){
	ret = wait(&status); //el wait fa que sigui sequencial
	    
    }

    if (cont != 1){
        if ( WIFEXITED(status) ) {   
           status = WEXITSTATUS(status);
           if(status > 0) printf("Father: shell program does not exist\n");
        }
	long temps = endTimer();//acabem amb el contador i imprimim el valor obtingut
        printf("the process finished and lasted %ld miliseconds \n", temps);
    }

    return 0;
}
