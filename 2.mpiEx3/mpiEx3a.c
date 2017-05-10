/*
	Description:
		- Master process rank 0 sends a message (MPI_Send) to rank 1 process 
		and wait for a incomming message (MPI_Recv).
		- Rank 1 process receive the message (MPI_Recv) from rank 0 process 
		and send another message to rank 0 process (MPI_Send)
		- after that, each process (rank 0 and 1) prints the amount of data received.

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
	int size, rank, dest, source, count, tag=1;
	int inmsg, outmsg=3;
	MPI_Status Stat;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
	  dest = 1;
	  source = 1;
	  MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	  MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	}else if (rank == 1) {
	  dest = 0;
	  source = 0;
	  MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	 }

	MPI_Get_count(&Stat, MPI_INT, &count);
	printf("Task %d: Received %d int(s) from task %d with tag %d \n",
		   rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

	MPI_Finalize();
}



