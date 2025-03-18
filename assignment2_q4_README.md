# MPI Heat Distribution Simulation

This project simulates **heat distribution over a 2D grid** using **MPI (Message Passing Interface)** for parallel processing.

## Overview

- The grid is initialized with boundary conditions (top and bottom rows heated).
- The simulation iteratively updates grid values using the **finite difference method**.
- Processes exchange boundary rows and compute updates in parallel.
- Simulation stops when it converges (change < `EPSILON`) or reaches `MAX_ITER` iterations.

## Features

- Demonstrates MPI communication: `MPI_Bcast`, `MPI_Sendrecv`, `MPI_Allreduce`, `MPI_Gather`.
- Parallelizes a **numerical heat diffusion** problem.
- Shows real-time **temperature convergence** over iterations.

## Requirements

- C compiler (e.g., `gcc`)
- MPI library (e.g., MPICH, OpenMPI)

## Compilation

```bash
mpicc -o heat_simulation heat_simulation.c -lm
Execution
bash
Copy
Edit
mpirun -np 4 ./heat_simulation
