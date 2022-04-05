
/***************************************
 * Author: Benito Moeckly
 * CPRE 308
 * */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
//#include <ptrhead.h>
#include "Bank.h"

void threadWorker();
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
	struct trans * t;
};

struct queue
{
	struct request * head, * tail;
	int num_jobs;
};

#define MAX_THREADS = 10;

pthread_mutex_t* mut; //NEED THIS TO LOCK THE BANK ACCOUNTS
pthread_cond_t job_cv;

int main(int argc, char** argv)
{
/**FIRST INIALIZE ALL THE VARIABLES WE WILL NEED**/
	int numThreads;
	int acCount;
	char * outputFile;
	int done = 0;
	int k, i;

	char * userIn; userIn = (char*) malloc(265); //dont forget to free
	char ** userInBroken; userInBroken = (char**)malloc(10*sizeof(char*));	//don't forget to free	
	char * token = "";
	char delim[1] = " ";

	pthread_t threadArray[numThreads];

	int helper;
	int helperTwo;

	int requests = 0;

	struct queue* q = createQ();

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

/****THIS LOOP WILL INITIALIZE ACCOUNTS*************/
	if(initialize_accounts(acCount) == 0)+
	{
		printf("Error setting up accounts.\n");
		exit(0);
	} else{initialize_account(acCount);}
/****THIS LOOP WILL INTITALIZE THE THREADS AND MUTEXES****/
	for(i = 0; i < numThreads && i < 10; i++)
	{
		pthread_create(&threadArray[i], NULL, (void*)&threadWorker, &q);
	}
	mut = (pthread_mutex_t*)malloc(acCount*sizeof(pthread_mutex_t));
	for(i = 0; i < acCount; i++)
	{
		pthread_mutex_init(&mut[i], NULL);
	}
	pthread_cond_init(&job_cv, NULL);

/****TAKE USER INPUT****/
	do{	
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
		{
			requests +=1;
			 enQ(q, requests, atoi(userInBroken[1]), NULL);
		}
		else if(strcmp(userInBroken[0], "TRANS") == 0)
		{
			struct trans * t;
			trans = calloc(MAX_THREADS, MAX_THREADS*sizeof(struct trans));
			i = 1;
			while(i < k)
			{
				
				transaction[i].acc_id = atoi(userInBroken[i]);
				i+=1; 
				transaction[i-1].amount = atoi(userIntBroken[i]);
				i+=;
				
			}
			while(i < MAX_THREADS)
			{
				transaction[i].acc_id = 0;
				transaction[i].amount = 0;
				i+=1;
			}

			requests +=1;
			enQ(q, requests, -1, transaction);
		}	
		else
			{
			printf("Unrecognized Command");
			}
	
	}while(done != 1);
	//free all the pointers I allocated space to.
	free(userIn);
	int i;
	for(i = 0; i < sizeof(userInBroken); i++)
	{
		free(userInBroken[i]);
	}

	printf("done");
		 
}

void threadWorker(struct queue * q))
{
	int currentRequestId;
	int checkAccount;
	struct trans t;
	int o = 0;

	while(true)
	{
		while(q.num_jobs == 0)
			pthread_cond_wait(&job_cv)
		
		currentRequestId = q->head.request_id;
		checkId = q->head.check_acc_id;
		t = q->t;
		deQ(q);
		if(checkId == -1) //This means we need to go through the transactions
		{
			while(transaction[o].account > 0)
			{
				
			}
		}
		else
		{
			pthread_mutex_lock(&mut[checkId]);
		}
		
	}
}
int transaction(transaction * t)
{
	//stuff here
}
int check(int idNum)
{
	return(read_account(idNum));
}

struct queue* createQ()
{
	//make queue
	struct queue *q;
	q = malloc(sizeof(struct queue));
	//queue will always have this dummy node, dummy starts as head and tail
	//the tail will point to the head
	struct request *r;
	r = malloc(sizeof(request));
	r->next = r;
	r.request_id = -1;
	r.check_acc_id = -1;
	r.transactions = NULL;
	q->head = q->tail = r;
}
void deQ(struct queue *q)
{
	struct request *r;
	r = q-> head;
	q->head = r->next;
	free(r);
	q.num_jobs-=1;
}
void enQ(struct queue *q, int req_id, int check_id, struct trans * transactions)
{
	struct request *r;
	r = malloc(sizeof(struct request));

	r.request_id = req_id;
	r.check_acc_id = check_id;
	r->t = transactions

	if(q->head.request_id == -1)
	{
		q->head = r;
	}
	else
	{
		q->tail->next = r;
	}
	q->tail = r;
	q.num_jobs +=1;
	if(q.num_jobs == 1)
	{
		pthread_cond_braodcast(&job_cv);
	}
}