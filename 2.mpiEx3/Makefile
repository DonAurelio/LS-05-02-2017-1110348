run: compile
	@echo "First Example\n"
	@mpirun -np 2 --hostfile machinefile ./mpiEx3a
	@echo "\n"
	@echo "Second Example\n"
	@mpirun -np 6 --hostfile machinefile ./mpiEx3b
compile:
	@mpicc mpiEx3a.c -o ./mpiEx3a
	@mpicc mpiEx3b.c -o ./mpiEx3b
clean:
	rm -rf ./mpiEx3a ./mpiEx3b