
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//#include <ptrhead.h>
#include "Bank.h"
/*
struct trans
{
	int acc_id;
	int amount;
}
struct request
{
	struct request * next;
	int	request_id;
	int	check_acc_id;
	struct	num_trans;
	struct	timeval starttime, endtime;
}

struct queue
{
	struct request * head, * tail;
	int num_jobs;
}
*/

int main(int argc, char** argv)
{
	int numThreads;
	int acCount;
	char * outputFile;
	int done = 0;
	int k;
	char * userIn; userIn = (char*) malloc(265);
	char ** userInBroken; userInBroken = (char**)malloc(10*sizeof(char*));	
	char * token = "";
	char delim[1] = " ";
	//CHECK IF ARGUMENTS ARE NOT NULL FIRST
	if(argv[0] != NULL && argv[2] != NULL && argv[3] != NULL )
	{
		numThreads = atoi(argv[1]);
		acCount = atoi(argv[2]);
		outputFile = (char*)calloc(sizeof(argv[3]), sizeof(argv[3]));	
		strcpy(outputFile, argv[3]);
	}
	else
	{
		printf("Null Argument(s)\n");
		exit(0);
	}

	//SET UP ACCOUNTS AND THREADS
	if(initialize_accounts(acCount) == 0)
	{
		printf("Error setting up accounts.\n");
		exit(0);
	}
	
	//make threads... not sure how to do that yet
	
	do{	//To start, we need to be able to take user input.
		userInBroken[0] = '\0';
		printf("ENTER COMMAND> ");
		fgets(userIn, 256, stdin);
		if((strlen(userIn) > 0) && (userIn[strlen(userIn)-1] == '\n'))
		{
			userIn[strlen(userIn)] = '\0';
		}
		k = 0;
		token = strtok(userIn, delim);
		while(token != NULL)
		{
			userInBroken[k] = calloc(strlen(token), strlen(token));
			strcpy(userInBroken[k], token);
			k++;
			token = strtok(NULL, delim);
		}		
		userInBroken[k] = NULL;
 		
		//now we can parse the input and decide how to procede.
		if(userInBroken[0] == NULL)
		{ /*do nothing*/ }
		else if(strcmp(userInBroken[0], "exit") == 0)
		{done = 1;}
		else if(strcmp(userInBroken[0], "EXIT") == 0)
		{done = 1;}
		else if(strcmp(userInBroken[0], "CHECK") == 0)
		{	//Check the given account.
			printf("$d\n", read_account(atoi(userInBroken[0])));
		}
		else if(strcmp(userInBroken[1], "BAL") == 0)
		{
			printf("Support coming soon.\n");
		}	
		else //default
		{printf("Command not recognized.\n");}
	

	}while(done == 0); 



	//free all the pointers I allocated space to.
	free(userIn);
	int i;
	for(i = 0; i < sizeof(userInBroken); i++)
	{
		free(userInBroken[i]);s
	}

	printf("done");
		 
}
