# MPI Examples - 1110348

MPI is a parallel programming standard that specifies how parallel processes can communicate to perform a collective work or in other words, work in the same problem. MPI allow processes in share and distribute memory systems, It provides built-in functions that make easy inter process communication. 

* 1.mpiEx2 Contains two examples about how to initialize an MPI Parallel Environment 
(**MPI_init** and **MPI_Finalize**) and how to use the rank identifier to differentiate processes (**MPI_Comm_rank**).

* 2.mpiEx3 Contains two examples about how process can communicate by messages using **MPI_Send** and **MPI_Recv**.

* 3.mpiEx4 Contains two examples about how processes can perfom a sum of the first 1000000 numbers together
using divide and conquer approach with **MPI_Reduce** and the PI calculation using monecarlo method and **MPI_Reduce**

# References 
[MPI Examples Detail](https://github.com/josanabr/distributedsystems/blob/master/MPI/README.md)

[MPI Tutorial](http://mpitutorial.com/)
