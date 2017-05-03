#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	srand(time(NULL));
	int i, count, countTotal, npoints;
	int start, end, rank, size, offset;
	double x, y;

	npoints = 100000000;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	count = 0;
	offset = npoints / size;
	start = rank * offset;
	end = start + offset;
	for (i = start; i < end; ++i)
	{
		x = (double)rand() / (double)RAND_MAX;
		y = (double)rand() / (double)RAND_MAX;
		if(x * x + y * y <= 1.0) count ++;
	}

	// Utilice la funcion 'MPI_Reduce' para guardar en la variable 
	// 'sumTotal' la suma parcial de todos las tareas 
	MPI_Reduce(&count,&countTotal,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0) printf ("\nTotal: %f\n", ( (double)countTotal / npoints) * 4.0);

	MPI_Finalize();
	
	return 0;
}
