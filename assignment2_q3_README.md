# MPI Parallel Odd-Even Sort

This project implements **Parallel Odd-Even Sort** using **MPI (Message Passing Interface)** to sort an array across multiple processes.

## Overview

- The unsorted array is divided among MPI processes.
- Each process sorts its local portion using **Bubble Sort**.
- Processes then exchange data with neighbors using the **Odd-Even Transposition Sort** algorithm.
- Final sorted data is gathered at the root process and printed.

## Features

- Demonstrates MPI collective communication: `MPI_Scatter`, `MPI_Gather`, `MPI_Sendrecv`.
- Highlights parallel sorting using odd-even phases.
- Scalable for larger arrays and multiple processes.

## Requirements

- C compiler (e.g., `gcc`)
- MPI library (e.g., MPICH, OpenMPI)

## Compilation

```bash
mpicc -o mpi_sort mpi_sort.c
Execution
bash
Copy
Edit
mpirun -np 4 ./mpi_sort
