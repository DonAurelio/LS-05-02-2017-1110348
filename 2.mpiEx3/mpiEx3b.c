/*
	Description:
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
	int inmsg, outmsg;
	MPI_Status Stat;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
	  dest = 1;
	  source = size - 1;
	  outmsg = rank;
	  MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	  MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
      printf("Soy el proceso %d y recibo %d\n", rank, inmsg);
	}else{
	  dest = (rank == size - 1) ? 0 : rank + 1;
	  source = rank - 1;
	  MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  printf("Soy el proceso %d y recibo %d\n", rank, inmsg);
	  outmsg = rank;
	  MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	 }

	MPI_Finalize();
}



