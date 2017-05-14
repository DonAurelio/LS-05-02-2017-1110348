# MPI Examples - 1110348

MPI is a parallel programming standard that specifies how parallel processes can communicate to perform a collective work or in other words, work in the same problem. MPI allow processes in share and distribute memory systems, It provides built-in functions that make easy inter process communication. 

## 1.mpiEx2 

Contains two examples about how to initialize an MPI Parallel Environment 
(**MPI_init** and **MPI_Finalize**) and how to use the rank identifier to differentiate processes (**MPI_Comm_rank**).

## 2.mpiEx3 

Contains two examples about how process can communicate by messages using **MPI_Send** and **MPI_Recv**.

## 3.mpiEx4 
Contains two examples: 

- how processes can perfom a sum of the first 1000000 numbers together using divide and conquer approach with **MPI_Reduce**.
  
- The PI calculation using monecarlo method and **MPI_Reduce**.
  
## 4.mpiEx5 
Contains an implementation of **MPI_Bcast** procedure using **MPI_Send** and **MPI_Recv**.

## 5.mpiAxb 

This code looks for apply MPI to perform a matrix vector product. Given a matrix 'A' (m x n) and a vector 'v' (n x 1) the product matrix 'x' would be m x 1. Having in mind that all MPI processes has a copy of the values of 'A' and 'b'. I divided matriz vector product between processes as follows: 

- [x] The **master** (rank 0) will send to each process the row number in 'A' that it will multiply with v. Then, master will receive each partial product and put them together on the final result vector 'x'.
- [x] **Slave** processes or workers will recive row numbers from master with a work tag 'TAGTAREA' it means that data received is a row in 'A' that the worker will perfom the product with 'v'. Then the worker will send its partial product to the master and it will keep waiting for new work or when the master sends it the finalization tag 'TAGPARAR'.

# References 
[MPI Examples Detail](https://github.com/josanabr/distributedsystems/blob/master/MPI/README.md)
[MPI Tutorial](http://mpitutorial.com/)
