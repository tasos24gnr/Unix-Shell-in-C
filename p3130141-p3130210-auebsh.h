#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void ShellyLoop();

char * read_input();

char ** cook( char * );

int orient(char **);

int pre_pip(char **);

void piping(char ***);

int exc_worker(char **);






