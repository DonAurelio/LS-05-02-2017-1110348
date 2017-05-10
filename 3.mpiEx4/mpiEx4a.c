/*
	Description:
		Reduction, consist in divide a big job in subjobs, then 
		the result of those subjobs are getting together. 

		On this example we need to get the sum of the first n 
		numbers. Suppose n = 10000 and the number of running 
		processes is size = 5. Then the work that perform each 
		process is divided as follows

		- Process 0 performs the sum from 1 to 2000
		- Process 1 performs the sum form 2001 to 4000
		- Process 2 performs the sum form 4001 to 6000
		- Process 3 performs the sum form 6001 to 8000
		- Process 4 performs the sum form 8001 to 10000

		MPI_Init: Starts an MPI Environment
		MPI_finalize: End the MPI Environment
		MPI_Comm_rank: Look for the process id on this case rank
		MPI_Comm_size: Look for the number of running processes

		MPI_Send: Sends a message to another process
		MPI_Recv: Wait for a message froma given process
		MPI_Get_count: Number of elements received
*/
#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	int i, sum=0, sumTotal=0, upToVal, insum=0;
	int start, end, size, rank;
	MPI_Status Stat;

	upToVal = 10000;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* Definning the part of the sum each process will perform */
	int offset = upToVal / size;
	start = rank * offset + 1;
	end = offset * (rank + 1);

	/* Each process performs its part of the sum */
	sum = 0;
	for(i=start; i<= end; i++){
		sum = sum +i;
	}

	/* If I am rank 0 process */
	if( rank == 0 ){
		/* I will recive the partials sums of rank > 0 process */
		for(i=1;i<size;i++){
			MPI_Recv(&insum, 1, MPI_INT, i, 1, MPI_COMM_WORLD,&Stat);
			sumTotal += insum;
		}
		/* Then I put my part of the sum to the total */
		sumTotal = sum;
		/* Finally I will print the total sum */
		printf ("\nTotal: %d\n",sumTotal);

	}else{
		/* 
			On the other hand, If I am NOT rank 0 process, 
			I will send my part of the sum to rank 0 process
		*/
		MPI_Send(&sum,1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	
	return 0;
}
