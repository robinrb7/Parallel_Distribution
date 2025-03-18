# MPI Parallel Dot Product

This project implements a **parallel dot product** of two vectors using **MPI**. It efficiently distributes the computational workload of calculating the dot product across multiple processes.

## Formula

The dot product is calculated as:

dot_product = A₀×B₀ + A₁×B₁ + ... + Aₙ×Bₙ

markdown
Copy
Edit

## Overview

- Vectors `A` and `B` are initialized with random integers (0–9) by the root process.
- The vectors are divided equally across MPI processes.
- Each process computes a **local dot product** of its segment.
- The local results are combined using `MPI_Reduce` to produce the **global dot product**.

## Features

- Efficient use of `MPI_Scatter` for distributing vector data.
- Aggregation of partial results with `MPI_Reduce`.
- Demonstrates parallelism for numerical computations.

## Requirements

- C compiler (e.g., `gcc`)
- MPI library (e.g., MPICH, OpenMPI)

## Compilation

```bash
mpicc -o dot_product dot_product.c
Execution
bash
Copy
Edit
mpirun -np 4 ./dot_product
