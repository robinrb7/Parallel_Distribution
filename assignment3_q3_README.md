# Parallel Prime Number Finder using MPI

This program uses **MPI_Send** and **MPI_Recv** to parallelize the task of finding prime numbers up to a specified limit. It implements a **master-worker model** where the master process distributes numbers to test, and worker processes check for primality.

## Problem Statement

Find all prime numbers up to a maximum number (e.g., 100) using MPI. The computation is distributed among multiple processes to improve performance.

## Key Concepts

- **Master Process (rank 0)**:
  - Distributes numbers from 2 to `MAX_NUM` to worker processes.
  - Receives readiness signals from workers and sends them the next number to test.
  - Sends a termination signal (`-1`) to all workers after the work is done.
  
- **Worker Processes (rank > 0)**:
  - Notify the master of readiness.
  - Receive a number, check if it’s prime, and send the result back to the master.
  - Exit when they receive `-1`.

## Primality Check

A simple function `is_prime(int n)` is used to check if a number is prime by testing divisibility up to √n.

## Compilation

Use an MPI compiler such as `mpicc`:

```bash
mpicc -o mpi_primes mpi_primes.c
Execution
Run the program with multiple processes:

bash
Copy
Edit
mpirun -np 4 ./mpi_primes
