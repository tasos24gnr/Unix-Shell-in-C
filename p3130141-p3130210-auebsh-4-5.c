#include "p3130141-p3130210-auebsh.h"

int pre_pip(char ** cmd){
	char ** temp = cmd;		//gia elegxo
	char ** temp2 = cmd;
	char ** god =malloc(sizeof(char *) * 250);
	char ** luc = god;
	char *** z =malloc(sizeof(char **) * 50);
	char *** z2=z;
	*z=luc;
	if(god == NULL){
		fprintf(stderr,"Fatal: failed to allocate memory.\n");
		abort();
	}
	if(z == NULL){
		fprintf(stderr,"Fatal: failed to allocate memory.\n");
		abort();
	}
		while(*temp2!=NULL){
			
			if(strcmp(*temp2,"|")==0){ 
				*god=NULL;
				god++;
				luc=god;
				z++;
				*z=luc;
						
			}else{
				*god=*temp2;
				god++ ;
			}
			temp2++	;
		}		
		z++;
		*z=NULL;
		piping(z2);

	return 1;
}


void piping(char *** ptcmd){
	pid_t pid;
	int fd[2];
	int in = 0;

	while (* ptcmd != NULL){
		pipe(fd);
		if ((pid = fork()) == -1){		//  Unable to fork ! Unsuccessful termination!
			perror("Fatal Error on excecution!");			
			exit(1);
		}
		else if (pid == 0){			// == Child Proccess ==    , forked successful
			dup2(in, 0); 				
			if ( *(ptcmd + 1) != NULL ){
				dup2(fd[1], 1);	
						
			}
			if(close(fd[0])==-1){
				perror("Error closing reading end of pipe");
				exit(1);			
			}				//child -> closes input/Read side of pipe
			exc_worker(*ptcmd);
			exit(0);
		}
		else					// == Parent Proccess ==   , forked successful
		{
			wait(NULL);				
			if(close(fd[1])==-1){ //parent -> closes output/Write side of pipe
				perror("Error closing writting end of pipe");
				exit(1);			
			}			
			in = fd[0]; 				// in = next command's input
			ptcmd++;
		}
	}
}


