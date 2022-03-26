#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**static char* prompt; 
prompt = (char *) malloc(7*sizeof(char));
prompt = "308sh>"; //this is the default prompt, can be changed when starting the shell**/
char command[100];
static char promptFlag[2] = "-p";

//static char* lsFlag	= "ls";

int main(int argc, char **argv)
{
	char* prompt; 
	prompt = calloc(7, 7*sizeof(char));

	if(argv[1] != NULL)
	{
		if(!strcmp(promptFlag, argv[1]))
		{
			if(argv[2] != NULL)
			{
			prompt = calloc(strlen(argv[2]), strlen(argv[2])*sizeof(char));
			strcpy(prompt, argv[2]);
			}
			else
			{
				strcpy(prompt, "308sh> ");
			}
		}
	}
	else
	{
		strcpy(prompt, "308sh> ");
	}

	while(1)
	{
		printf("%s", prompt);
		scanf("%s", command);
		
		if(strcmp(command, "exit") == 0)
		{return 0;}
		/*look for supported commands here*/

		printf("You typed: %s\n", command);		
	
	}

	free(prompt);	
	
	return 0;
}
