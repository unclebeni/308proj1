#include <bank.h>
#include <stdio.h>
#include <unistd.h>
#include <ptrhead.h>

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
	struct request * head, * taile;
	int num_jobs;
}


int main(int argc, char** argv)
{
	//NEED TO CHECK IF ARGUMENTS ARE NOT NULL FIRST
	int numThreads = argv[1];
	int acCount = argv[2];
	char * outputFile = calloc(sizeof(argv[3], sizeof(argv[3]);
	strcpy(outputFile, argv[3]);
	
 

}
