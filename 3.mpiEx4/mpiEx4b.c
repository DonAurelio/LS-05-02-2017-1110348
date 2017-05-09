#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	int i, sum, sumTotal, upToVal;
	int start, end, size, rank;

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
	// Utilice la funcion 'MPI_Reduce' para guardar en la variable 
	// 'sumTotal' la suma parcial de todos las tareas 
	MPI_Reduce(&sum,&sumTotal,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0) printf ("\nTotal: %d\n",sumTotal);

	MPI_Finalize();
	
	return 0;
}
