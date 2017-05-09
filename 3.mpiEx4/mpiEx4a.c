/*
	MPI Reduccion manual
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

	// Defina aqui el segmento que debe procesar una tarea
	// El inicio del segmento en la variable 'start', el fin del segmento
	// la variable 'end'
	int offset = upToVal / size;
	start = rank * offset + 1;
	end = offset * (rank + 1);

	sum = 0;
	for(i=start; i<= end; i++){
		sum = sum +i;
	}

	if( rank == 0 ){

		/* Recibiendo sumas parciales de procesos de rank > 0*/
		for(int i=1;i<size;i++){
			MPI_Recv(&insum, 1, MPI_INT, i, 1, MPI_COMM_WORLD,&Stat);
			sumTotal += insum;
		}
		/* sumando la suma parcial del proceso con rank 0 */
		sumTotal = sum;
		/* resultado total */
		printf ("\nTotal: %d\n",sumTotal);

	}else{
		/* enviando suma parcial al proceso con rank 0 */
		MPI_Send(&sum,1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	
	return 0;
}
