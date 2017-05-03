run: compile
	@echo "\n\n 1 \n\n"
	@mpirun -np 4 --hostfile machinefile ./mpiEx4a
compile:
	@mpicc mpiEx4a.c -o ./mpiEx4a

clean:
	rm -rf ./mpiEx4a