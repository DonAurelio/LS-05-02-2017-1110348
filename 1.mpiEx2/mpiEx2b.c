/*
	Description:
		Only the master process (or rank 0 process) print 
		the number of running processes

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
		printf("\nI am the master and there are %d running processes !\n", size);
	}  

	/* shut down MPI */
	MPI_Finalize(); 
	
	return 0;
}


