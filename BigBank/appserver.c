
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

pthread_mutex_t* mut; //NEED THIS TO LOCK THE BANK ACCOUNTS //MUT[0] WILL ACT AS THE FILE MUTEX SINCE THERE IS NOT BANK ACCOUNT 0
pthread_mutex_t* q_mut; //NEED THIS TO LOCK THE QUEUE
pthread_cond_t job_cv;
char * outputFile;
FILE *f;

int main(int argc, char** argv)
{
/**FIRST INIALIZE ALL THE VARIABLES WE WILL NEED**/
	int numThreads;
	int acCount;
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
/****OPEN FILE****/
f = fopen(outputfile, "w+");

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
	ptrhead_mutex_init(&q_mut, NULL);

/****TAKE USER INPUT****/	fclose(fp);
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
			pthread_mutex_trylock(&q_mut);
			enQ(q, requests, atoi(userInBroken[1]), NULL);
			pthread_mutex_unlock(&q_mut);
		}
		else if(strcmp(userInBroken[0], "TRANS") == 0)
		{
			struct trans * t;
			trans = calloc((k-1)/2, ((k-1)/2)*sizeof(struct trans));
			i = 1;
			while(i < k)
			{
				
				transaction[i].acc_id = atoi(userInBroken[i]);
				i+=1; 
				transaction[i-1].amount = atoi(userIntBroken[i]);
				i+=1;
				
			}
			
			requests +=1;
			pthread_mutex_trylock(&q_mut);
			enQ(q, requests, -1, transaction);
			pthread_mutex_unlock(&q_mut);
		}	
		else
			{
			printf("Unrecognized Command");
			}
	
	}while(done != 1);
	//free all the pointers I allocated space to.
	free(userIn);
	free(mut);
	int i;
	for(i = 0; i < sizeof(userInBroken); i++)
	{
		free(userInBroken[i]);
	}
	fclose(fp);
	printf("done");
		 
}

void threadWorker(struct queue * q))
{
	int currentRequestId;
	int checkAccount;
	struct timeval starttime;
	struct timeval endtime;
	struct trans t;
	int j = 0;
	int skip = 0;
	int previousAccount;
	char * outString;

	while(true)
	{
		while(q.num_jobs == 0 || q->head->next == q->tail)
			pthread_cond_wait(&job_cv)
		
		
		currentRequestId = q->head.request_id;
		checkId = q->head.check_acc_id;
		t = q->t;
		deQ(q);
		//lock down all accounts
		for(j = 0; j < sizeof(t); j++)
		{ pthread_mutex_trylock(&mut[t[j].acc_num]);}
		//see if all the accounts have sufficient funds
		j=0;
		for(j = 0; j < sizeof(t); j++)
		{ 
			if(read_account(t[j].acc_num) + t[j].amount < 0)
			{ skip = 1; break;}
		}
		if(skip == 1)
		{//insufficient funds
			outString = snprintf();	
		}
		else
		{//carry on with the transaction
			for(j = 0; j < sizeof(t); j++)
			{
				write_account(t[j].acc_num, t[j].amount);			
			}	
			outString =snprintf();	
		}
		for(j = 0; j < sizeof(t); j++)
		{
			pthread_mutex_unlock(&mut[t[j].acc_num]);
		}
		pthread_mutex_trylock(&mut[0]);
		fputs(outString, f);
		pthread_mutex_unlock(&mut[0]);
		skip = 0;
		}
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
	r = q-> head->next;
	q->head->next = r->next;
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
}struct request * next; // pointer to the next request in the list
int request_id; // request ID assigned by the main thread
int check_acc_id;



