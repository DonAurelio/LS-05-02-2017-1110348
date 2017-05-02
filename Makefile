run: compile
	mpirun -np 2 --hostfile machinefile ./mpiEx2b
	mpirun -np 4 --hostfile machinefile ./mpiEx2b
	mpirun -np 8 --hostfile machinefile ./mpiEx2b
compile:
	mpicc mpiEx2b.c -o ./mpiEx2b
clean:
	rm -rf ./mpiEx2b
