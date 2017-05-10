/*
	Description:
		Process with rank 0 prints a message and the other processes 
		print a different message.

		MPI_Init: Starts an MPI Environment
		MPI_finalize: End the MPI Environment
		MPI_Comm_rank: Look for the process id on this case rank
		MPI_Comm_size: Look for the number of running processes
*/
#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]){
	int  rank, size;
	
	/* start up MPI */
	MPI_Init(&argc, &argv);
	
	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(rank == 0){
		printf("\nI am the master of %d running processes !\n", size);

	}else{
		printf("\nI am the %d process of %d running processes !\n", rank, size);
	}    

	/* shut down MPI */
	MPI_Finalize(); 
	
	return 0;
}


