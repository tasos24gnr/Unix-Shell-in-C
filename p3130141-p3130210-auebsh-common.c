#include "p3130141-p3130210-auebsh.h"

int main( int argc , char * argv[]){
	printf("\n ================================");	
	printf("\n   WELCOME TO OUR AMAZING SHELL! ");
	printf("\n ================================\n\n");
	printf(" Type your first command > ");
			
	ShellyLoop();	
		
	return 0;
}

void ShellyLoop(){ 
	int m = 1;	
	char * ln; 	//Characters Array
	char ** params;	//Character Pointers Array
	
	while (m){
		ln = read_input();		//Read the input command from the user
		params = cook(ln);		//Splits command into seperate parts
		m=orient(params);		//Determines which shell is running
		
		free(ln);			//Releases the specified block of memory
		free(params);			
	}	
}

char * read_input(){ 
	int n =255;
	int p = 0;
	int ch;
	char * arrln = malloc(sizeof(char)*n);	//255 char memory blocks allocated for the array arrln
						
	if(arrln == NULL){
		fprintf(stderr,"Fatal: failed to allocate %i bytes.\n",n);
		abort();
	}

	while(1){
		ch = getchar();
		if( ch!=10){			//10 is the ASCII value for "\n"
			arrln[p] = ch;
			p=p+1;
		}else {
			arrln[p] = '\0';
			return arrln;
			
		}
		if (ch==-1){			//-1 is the ASCII value for Ctrl-D
		printf(" Thank you for using our shell! \n");
		exit(0);
		}
		
		if(p>=n){
			n=n+255;
			arrln = realloc(arrln,n);
		}
	}
}

char ** cook( char * l ) {
	int i=0;					//Potition of tokarray Array
	const char  s[2] = " \n";
	int n=50;					//Number of parameters
	char * token;
	char ** tokarray=malloc(sizeof(char *) * n);	//Contains character pointers of each token
	
	if(tokarray == NULL){
		fprintf(stderr,"Fatal: failed to allocate %i bytes.\n",n);
		abort();
	}					

	token = strtok(l,s);

	while(token != NULL){
		if(i == n-1){
			n=n+50;
			tokarray = realloc(tokarray,sizeof(char *) * n);
			printf(" realloced= %i \n",i);
		}
		tokarray[i]= token;
		i=i+1;
		token = strtok(NULL,s);	
	}
	tokarray[i]=NULL;
	
	return tokarray;
}

int orient(char ** vlax){ 
char ** c= vlax;
int num_pipes=0;
int redirections=0;
int frouraki=0;
int current=1;
	while(*c!=NULL){	
		if(strcmp(*c,"|")==0){			
			num_pipes++;		
		}
		if(strcmp(*c,">")==0 || strcmp(*c,"<")==0){			
			redirections++;	
			if(current==3){
				frouraki=1;			
			}	
		}
		c++;
		current++;
	}
	
	if(num_pipes>1){
		pre_pip(vlax);		
		printf("\nauebsh5> ");
	}else if(num_pipes==0 && redirections!=0 && frouraki==0){
		exc_worker(vlax);
		printf("\nauebsh2> ");
	}else if(frouraki!=0){
		exc_worker(vlax);		
		printf("\nauebsh3> ");
	}else if(num_pipes==1){
		pre_pip(vlax);		
		printf("\nauebsh4> ");
	}else if(num_pipes==0 && redirections==0){
		exc_worker(vlax);		
		printf("\nauebsh1> ");
	}
	return 1;
}
