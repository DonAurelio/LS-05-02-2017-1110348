run: compile
	@echo "Reducción Manual\n"
	@mpirun -np 4 --hostfile machinefile ./mpiEx4a
	@echo "MPI Reduce\n"
	@mpirun -np 4 --hostfile machinefile ./mpiEx4b
	@echo "Montecarlo\n"
	@mpirun -np 4 --hostfile machinefile ./mpiEx4c

compile:
	@mpicc mpiEx4a.c -o ./mpiEx4a
	@mpicc mpiEx4b.c -o ./mpiEx4b
	@mpicc mpiEx4b.c -o ./mpiEx4c

clean:
	rm -rf ./mpiEx4a ./mpiEx4b ./mpiEx4c
