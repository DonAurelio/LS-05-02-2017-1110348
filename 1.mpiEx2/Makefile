run: compile
	@echo "\n\n1\n\n"
	@mpirun -np 2 --hostfile machinefile ./mpiEx2a
	@mpirun -np 4 --hostfile machinefile ./mpiEx2a
	@mpirun -np 8 --hostfile machinefile ./mpiEx2a
	@echo "\n\n2\n\n"
	@mpirun -np 2 --hostfile machinefile ./mpiEx2b
	@mpirun -np 4 --hostfile machinefile ./mpiEx2b
	@mpirun -np 8 --hostfile machinefile ./mpiEx2b
compile:
	@mpicc mpiEx2a.c -o ./mpiEx2a
	@mpicc mpiEx2b.c -o ./mpiEx2b

clean:
	rm -rf ./mpiEx2a
	rm -rf ./mpiEx2b
