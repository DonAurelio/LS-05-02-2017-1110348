run: compile
	@echo "\n\n 1 \n\n"
	@mpirun -np 4 --hostfile machinefile ./mpiEx4a
	@echo "\n\n 2 \n\n"
	@mpirun -np 4 --hostfile machinefile ./mpiEx4b

compile:
	@mpicc mpiEx4a.c -o ./mpiEx4a
	@mpicc mpiEx4b.c -o ./mpiEx4b

clean:
	rm -rf ./mpiEx4a
	rm -rf ./mpiEx4b