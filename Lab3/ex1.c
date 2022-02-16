#include <pthread.h>
#include <stdio.h>

void* thread1();

void* thread2();

int main (int argc, char *argv[])
{
pthread_t i1, i2; //create ids for the threaded programs

pthread_create(&i1, NULL, (void*)&thread1, NULL);
pthread_create(&i1, NULL, (void*)&thread2, NULL); //Create new threads for the programs

pthread_join(i1, NULL); 
pthread_join(i2, NULL); //This tells the computer to wait for the threade processes to finish before completing the main()

printf("\nHello from main.");

return 0;
}

void* thread1()
{
	sleep(5);
	printf("\nHello from thread1");
}

void* thread2()
{
	sleep(5);
	printf("\nHello from thread2");
}
