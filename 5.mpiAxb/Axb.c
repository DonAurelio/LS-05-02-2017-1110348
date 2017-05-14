/**
Este codigo busca hacer la multiplicacion de una matrix 'A' de dimension m x n
con un vector 'x' de dimension n x 1 y obtener como resultado el vector 'b' de
dimension m x 1.

El objetivo de este programa es evidenciar la utilidad de los TAGs en los 
mensajes enviados a traves de MPI.
Este programa funciona bajo el esquema maestro/trabajador y donde el proceso 
cuyo identificador es el '0' se denotara como el maestro. Los trabajadores 
tendran un 'rank' diferente de '0'. Si el numero total de procesos es 'p' 
entonces el numero total de trabajadores es 'p - 1'.

Algoritmo:
1- El maestro en un ciclo hara lo siguiente
	1.a- Despachara 'p - 1' filas entre los procesos trabajadores con un TAG
	     que indique que es una tarea a procesar
	1.b- Si el numero de filas 'm' es menor que el numero de procesos 
	     'p - 1', a los 'm - ( p - 1 )' procesos se les enviara un mensaje
	     indicandoles que no hay mas tareas que procesar
	1.c- El maestro recibira los resultados de los trabajadores ocupados y enviara 
	     un mensaje a estos que respondieron con un mensaje con un TAG que dice 
	     que no habra mas que procesar
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXFILAS 23
#define MAXCOL 5
#define TAGTAREA -1 // marca que denota que el mensaje es una tarea
#define TAGPARAR -2 // marca que denota que ya no hay mas mensajes por enviar

/**
Funcion usada por el maestro para enviar a los trabajadores el 
numero de la fila que deben procesar. Adicionalmente se 
encarga de colocar el resultado de cada trabajor en la matrix 
'x'.

Recibe: 
	- El numero de filas a procesar
	- La matrix donde se pondran los resultados
	- El numero de procesos 
**/
int distributereceive(int, int*, int);
/**
Funcion usada por el trabajador y quien se encarga de recibir numeros de filas de parte del 
maestro. El trabajador puede recibir o una numero de fila o un mensaje que le indique no hay mas
tareas a procesar.

Recibe:
	- El numero de proceso
	- La matrix 'A' cuyo numero de fila (segun indique el maestro) 
	va a ser multiplicada por el vector 'b'
	- El vector 'b'
**/
int receive(int, int*, int*);
/**
Funcion usada para imprimir una matrix de tamano MAXFILAS x MAXCOL.
**/
int printmatrix(int, int, int*);
/**
Funcion usada para imprimir un vector.
**/
int printvector(int, int*);

/**
Funcion 'main'
**/
int main(int argc, char **argv) {
	int matrix[MAXFILAS * MAXCOL]; // Matriz 'A' m x n
	int b[MAXCOL]; // Vector n x 1
	int x[MAXFILAS]; // Resultado m x 1
	int rank;
	int size;
	int i,j;

	/* Inicializacion de 'matrix' y vector 'b' */
	/* Todos los procesos inicializan 'A' y 'b' con los mismos valores  */
	for (i = 0; i < MAXFILAS; i++) 
		for (j = 0; j < MAXCOL; j++) {
			matrix[i*MAXCOL + j] = i*MAXCOL + j;
			if (i == 0) 
				b[j] = i*MAXCOL + j;
		}
	
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	/** 
	El maestro 
		- imprime por pantalla la matrix y el vector
		- envia cada numero de fila de la matrix a los trabajadores
		- imprime el resultado 
	*/
	if (rank == 0) {
		printf("MATRIX\n");
		printmatrix(MAXFILAS, MAXCOL, matrix);
		printf("VECTOR\n");
		printvector(MAXCOL, b);
		distributereceive(MAXFILAS, x, size);
		printf("Vector resultado\n");
		printvector(MAXFILAS, x);
	} else { // el trabajador espera por filas que procesar
		receive(m, b);
	}

	MPI_Finalize();
}

/**
Metodo usado por el maestro para distribuir las filas
*/
int distributereceive(int f, int *x, int size) {
	/*
	Mientras haya filas de la matrix que procesar, envie a los procesos. Siga
	enviando filas hasta que se recorran todas las filas de la matrix. 
	Reciba los resultados de los procesos, cada proceso debe devolver un valor
	entero resultado de multiplicar una fila de la matrix por el vector 'b'.
	Si no hay mas filas que procesar enviar un mensaje a los procesos para que 
	detengan su ejecucion.
	*/
	int i = 0;
	int norow = 0;				// Dato que no es valido como una fila
	int current_row = 0; 		// Fila actual a enviar para procesar 
	int current_worker = 1;		// Trabajador actual disponible para procesar
	int workers_to_receive = 0;	// Ńumero de trabajadores de los que se espera un resultado
	int partial_result = 0;		// Multiplicacion parcial de cada trabajador
	MPI_Status stat;	

	// Muestras la fila actual es menor al numero de filas a procesar
	while( current_row < f ){
		// Miestras hayan trabajadores disponibles
		while( current_worker < size ){
			if( current_row < f ){
				// Envio al numero de trajador actual el numero de fila actual a procesar
				MPI_Send(&current_row, 1, MPI_INT, current_worker, TAGTAREA, MPI_COMM_WORLD);
				// Paso a la siguiente fila
				++current_row;
				// Indico que voy a esperar respuesta de un trabajador 
				++workers_to_receive;
				// Paso al siguiente trabajador disponible
				++current_worker;
			}else{
				MPI_Send(&norow, 1, MPI_INT, worker_rank, TAGPARAR, MPI_COMM_WORLD);
				++current_worker;
			}
		}

		// Recibo los resultados en orden trabador 1,2,...,size.
		for(i = 1; i <= workers_to_receive; ++i){
			MPI_Recv(&partial_result, 1, MPI_INT, i, MPI_ANY_TAG, &stat);
			// Recibo la suma parcial y el tag que envia el trabajador indicando
			// el numero de la fila que proceso, para asi mismo colocar ese resultado
			// en el vector resultado de forma correcta 
			x[stat.MPI_TAG] = part_result;
		}
		// Vuelvo a colocar al trabajador 1 disponible, esto implicitamente indica
		// que los trabajadores 1,2,....,size tambien estan disponibles ya que
		// al terminar el clico for he recibido los resultados paraciales de cada uno
		current_worker = 1;
		// Indico que ya no estoy esperando recibir resultados de algun trajador
		workers_to_receive = 0;
	}

	return 0;
}

/**
Esta funcion es usada por un proceso trabajador. El proceso recibe inicialmente
el vector 'b' el cual se usa para multiplicar las diferentes filas de la matrix
'A'. La matrix 'A' sera enviada, fila x fila, por parte del maestro y en el 
proceso trabajador recibe dicha fila y la multiplica por el b. El resultado de
dicha multiplicacion es enviada al maestro que ira guardando el resultado en 
cada posicion del vector respuesta 'x'.
*/
int receive(int rank, int* m, int* b) {
	/*
	Este metodo ejecutado por cada proceso trabajador debe 
	1- Recibir mensaje del maestro
		1.a- Una fila de la matrix para multiplicar por 'b' y ese valor 
		     enviarselo al nodo maestro
		1.b- Que no hay mas filas a procesar
	*/
	int data;			// El dato que se recibe del maestro 
	int source = 0;		// El maestro es el origen de los mensajes es decir el proceso con rank == 0
	int online = 1;		// Indica si este proceso (proceso trabajador) esta recibiendo peticiones
	MPI_Status stat;

	// Miestras este en linea
	while(online){
		MPI_Recv(&data, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);

		// Si recino el tag tarea significa que el maestro me ha enviado un 
		// numero de fila para procesar
		if(stat.MPI_TAG == TAGTAREA){
			int row_to_process = data;
			int partial_result = 0;
			int i;
			for(j = 0; j < MAXCOL ; ++j){
				partial_result += m[ row_to_process * MAXCOL + j ] * b[ j ];
			}
			MPI_Send(&partial_result, 1, MPI_INT, 0, row_to_process, MPI_COMM_WORLD)
		}else{ // En caso contrario entonces termino mi servicio
			online = 0;
		}
	}
	return 0;
}

/** 
Metodo usado para imprimir los elementos de una matrix de dimensiones 'm x n'
*/
int printmatrix(int m, int n, int *mt) {
	int i, j;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			printf("%5.1d ", *(mt+i*MAXCOL + j));
		printf("\n");
	}
	return 0;
}

/** 
Metodo usado para imprimir los elementos de un vector de longitud 'n'
*/
int printvector(int n, int *v) {
	int i;
	for (i = 0; i < n; i++)
		printf("%5.1d ", v[i]);
	printf("\n");
	return 0;
}