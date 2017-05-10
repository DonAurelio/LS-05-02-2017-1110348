#include <stdio.h>
#include "mpi.h"

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
		
		MPI_Reduce(
			void* send_data, 		// The partial sum that each process perfomed 
			void* recv_data, 		// The variable that will contain the total sum, 
										it is only relevant with the process with a rank of root
			int count,				// Number of datum sended 			
			MPI_Datatype datatype,	// Type of send and recv data (MPI_INT,MPI_FLOAT,..., etc)
			MPI_Op op,				// Type of reduction (MPI_SUM, MPI_PROD, MPI_MAX,..., etc)
			int root,				// The process that will receive and put together the partial sums
			MPI_Comm communicator	
			)
*/

int main(int argc,char *argv[]){
	int i, sum, sumTotal, upToVal;
	int start, end, size, rank;

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

	MPI_Reduce(&sum,&sumTotal,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0) printf ("\nTotal: %d\n",sumTotal);

	MPI_Finalize();
	
	return 0;
}
