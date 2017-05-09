run: compile
	@echo "Broadcast Manual\n"
	@mpirun -np 4 --hostfile machinefile ./mpiEx5a

compile:
	@mpicc mpiEx5a.c -o ./mpiEx5a

clean:
	rm -rf ./mpiEx5a
