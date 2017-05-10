#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

/*
	Description:
		Montecarlo to approximante PI calculation. We can approximante 
		PI value generating pseudo random points x and y (between 0 and 1). Then 
		cheking how many poins fall inside the circle of r = 1. As more
		poinst are generated more increase PI accuarancy. 

		As the number of points increase this task looks ideal to divide 
		the point generation among processes.
 
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
	srand(time(NULL));
	int i, count, countTotal, npoints;
	int start, end, rank, size, offset;
	double x, y;

	/* Total number of points to generate */
	npoints = 100000000;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* Each process sum to its count variable */
	count = 0;
	int my_number_of_points = npoints / size;
	for (i = 0; i < my_number_of_points; ++i)
	{
		x = (double)rand() / (double)RAND_MAX;
		y = (double)rand() / (double)RAND_MAX;
		/* if the point fall inside the circle */
		if(x * x + y * y <= 1.0) count ++;
	}

	MPI_Reduce(&count,&countTotal,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0) printf ("\nTotal: %f\n", ( (double)countTotal / npoints) * 4.0);

	MPI_Finalize();
	
	return 0;
}
