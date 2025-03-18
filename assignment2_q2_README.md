# MPI Matrix Multiplication (Parallelized with MPI and OpenMP)

This project performs **matrix multiplication** of two 70×70 matrices using **MPI (Message Passing Interface)** for distributed computing and **OpenMP** for timing.

## Overview

- Matrices `A` and `B` are initialized in the root process.
- Matrices are broadcast to all MPI processes.
- Each process computes a portion of the resulting matrix `C`.
- Results are gathered and combined at the root process.
- Execution time is measured using `omp_get_wtime()`.

## Features

- Efficient parallel computation using MPI
- Memory-safe allocation for partial results
- Dynamic support for varying process counts
- Handles uneven row distribution in last process

## Requirements

- C compiler (e.g., `gcc`)
- MPI library (e.g., MPICH, OpenMPI)
- OpenMP support for timing

## Compilation

```bash
mpicc -fopenmp -o mpi_matrix mpi_matrix.c
Execution
bash
Copy
Edit
mpirun -np 4 ./mpi_matrix
Replace 4 with the desired number of MPI processes 
