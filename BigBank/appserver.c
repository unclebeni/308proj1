#include <bank.h>
#include <stdio.h>
#include <unistd.h>
#include <ptrhead.h>
#include <bank.c>

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


int main(int argc, char** argv)
{
	int numThreads;
	int acCount;
	char * outputFile;
	int done = 0;	
	//CHECK IF ARGUMENTS ARE NOT NULL FIRST
	if(numThreads != null && acCount != null && argv[3] != null )
	{
		numThreads = argv[1];
		acCount = argv[2];
		outputfile = calloc(sizeof(argv[3], sizeof(argv[3]));	
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
		printf("Error setting up accounts."\n);
		exit(0);
	}
	for(int i = 0; i < numThreads; i++)
	{
		//make new thread.. not sure how to do that currently
	}
	
	do{

	}(while done == 0);

	printf("done");
		 
}
