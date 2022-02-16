#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**static char* prompt; 
prompt = (char *) malloc(7*sizeof(char));
prompt = "308sh>"; //this is the default prompt, can be changed when starting the shell**/
char command[100];
static char* promptFlag = "-p";

int main(int argc, char **argv)
{
	char* prompt; 
	prompt = (char *) malloc(7*sizeof(char));
	prompt = "308sh>"; //this will be the default prompt when startin the shell

	if(!strcmp(promptFlag, argv[1]))
	{
		if(strlen(argv[2]) != 0)
		{
		prompt = calloc(strlen(argv[2]), strlen(argv[2])*sizeof(char));
		strcpy(prompt, argv[2]);
		}
	}

	while(1)
	{
		printf("%s", prompt);
		scanf("%s", command);
		printf("\nYou typed: %s\n", command);		
	
	}

	free(prompt);	
	
	return 0;
}
