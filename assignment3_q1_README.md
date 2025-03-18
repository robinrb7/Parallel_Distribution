# DAXPY Operation using MPI

This project implements the **DAXPY operation** using **MPI (Message Passing Interface)** and compares it with a serial version to analyze performance and speedup.

## Problem Statement

Perform the DAXPY operation:

X[i] = a * X[i] + Y[i]

markdown
Copy
Edit

Where:
- `X` and `Y` are vectors of size `2^16 = 65536`
- `a` is a scalar value
- The computation is parallelized using MPI by dividing the vectors among multiple processes.

## Features

- Parallel implementation of DAXPY using **MPI**.
- Serial version for performance comparison.
- Time measurement using `MPI_Wtime()`.
- Speedup calculation based on runtime of serial vs parallel execution.

## Constants

```c
#define N (1 << 16)  // 65536 elements
double a = 2.5;      // Scalar multiplier
Compilation
Use an MPI compiler such as mpicc:

bash
Copy
Edit
mpicc -o daxpy_mpi daxpy_mpi.c -fopenmp
-fopenmp is included in case you want to explore hybrid MPI+OpenMP versions later.

Execution
MPI Parallel Version
bash
Copy
Edit
mpirun -np 4 ./daxpy_mpi
