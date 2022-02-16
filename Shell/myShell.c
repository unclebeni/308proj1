#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* prompt;
prompt = (char *) malloc(7);
prompt = "308sh> "; //this is the default prompt, can be changed when starting the shell
char command[100];
static char* promptFlag = "-p";

int main(int argc, char **argv)
{

	if(!strcmp(promptFlag, argv[1]))
	{
		if(strlen(argv[2]) != 0)
		{
		prompt = (char *) realloc(prompt, strlen(argv[2]));
		strcpy(prompt, argv[1]);
		}
	}

	while(1)
	{
		printf("%s", prompt);
		scanf("%s", command);
		printf("\nYou typed: %s\n", command);		
	
	}

	

}
