#include "p3130141-p3130210-auebsh.h"

int exc_worker(char ** tokens){
	
	int flag=0;
	int in;
	int out;
	
	int savedin=dup(0);		
	int savedout=dup(1);
	char ** temp = tokens;
		
	if(strcmp(tokens[0],"cd")==0){	
		if(tokens[1]==NULL){
			fprintf(stderr,"expected argument to \"cd\"\n");
		}else{		
			chdir(tokens[1]);
		}
	}else{
		pid_t pid = fork() ;

	if (pid>0){			// == Parent Proccess ==   , forked successful
		waitpid(pid,NULL,0);
		if (flag!=0){		
			dup2(savedin,0);
			close(savedin);
			dup2(savedout,1);
			close(savedout);
		}
	}else if(!pid){			// == Child Proccess ==    , forked successful
		while(*temp!=NULL){	
			if(flag==1){
				in= open((char*)*temp,O_RDONLY);
				if (in<0){
					perror("Fail opening the file.");
					exit(1);
				}
				dup2(in,0);
				*temp=NULL;
				flag=3;
			}
			if(flag==2){
				out= open((char*)*temp,O_WRONLY|O_TRUNC|O_CREAT,S_IRUSR|S_IRGRP|S_IWGRP|S_IWUSR);
				if (out<0){
					perror("Fail opening the file.");
					exit(1);
				}
				dup2(out,1);
				*temp=NULL;
				flag=3;
			}	
			if(*temp!=NULL && strcmp(*temp,"<")==0){
				*temp=NULL;
				flag=1;
			}
			if(*temp!=NULL && strcmp(*temp,">")==0){
				*temp=NULL;
				flag=2;
			}
			
			temp++;
			}		
			
			execvp(tokens[0],tokens);
	
	}else{				//  Unable to fork ! Unsuccessful termination!
		perror("Fatal Error on excecution!");
		exit(1);
	}
	}
	
	return 1;
}
