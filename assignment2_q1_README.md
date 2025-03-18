# MPI Monte Carlo Pi Estimation

This project estimates the value of **π (Pi)** using the **Monte Carlo method** with **MPI (Message Passing Interface)** for parallel processing in C.

## Overview

- Generates random points in a unit square.
- Calculates how many fall inside a unit circle.
- Uses **MPI_Reduce** to sum results from all processes.
- Estimates Pi using the ratio of points inside the circle to total points.

## Requirements

- C compiler (e.g., `gcc`)
- MPI library (e.g., MPICH, OpenMPI)

## Compilation

```bash
mpicc -o mpi_pi mpi_pi.c
Execution
bash
Copy
Edit
mpirun -np 4 ./mpi_pi
