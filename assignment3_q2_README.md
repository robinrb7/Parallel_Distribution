# Approximation of π using MPI

This project approximates the value of **π (Pi)** using numerical integration (Riemann sum) in a parallelized manner with **MPI (Message Passing Interface)**.

## Problem Statement

Approximate π using the following integral:

π ≈ ∑ (4 / (1 + x^2)) * step, for x in [0, 1]

markdown
Copy
Edit

Where:
- `step = 1 / NUM_STEPS`
- The approximation improves with more `NUM_STEPS`.

## Parallelization Strategy

- Use `MPI_Bcast` to broadcast the `step` value to all processes.
- Each process computes a **partial sum** of the series.
- Use `MPI_Reduce` to **aggregate partial sums** into the final result at the root process.

## Constants

```c
#define NUM_STEPS 100000  // Number of intervals for approximation
Compilation
Use an MPI compiler like mpicc:

bash
Copy
Edit
mpicc -o mpi_pi mpi_pi.c
Execution
Run with desired number of processes:

bash
Copy
Edit
mpirun -np 4 ./mpi_pi
