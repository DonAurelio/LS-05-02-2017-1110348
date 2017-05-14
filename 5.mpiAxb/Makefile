run: compile
	@mpirun -np 4 --hostfile machinefile ./Axb
compile:
	@mpicc Axb.c -o ./Axb
clean:
	rm -rf ./Axb
