# MPI Parallel Prefix Sum (Scan)

This project demonstrates the use of **MPI_Scan** to perform a **parallel prefix sum** (also called a cumulative sum) across multiple processes.

## Formula

The prefix sum for an array `A` is defined as:

prefix_sum[i] = A[0] + A[1] + ... + A[i]

pgsql
Copy
Edit

In this implementation, each process contributes one element, and **MPI_Scan** is used to compute the prefix sum across processes.

## Features

- Each process holds a local value equal to its rank + 1.
- **MPI_Scan** computes the prefix sum across all processes.
- Demonstrates efficient data aggregation using MPI’s built-in scan operation.

## Example

Assuming 4 processes with `local_value = rank + 1`:

| Process | Local Value | Prefix Sum |
|---------|-------------|------------|
|   0     |     1       |     1      |
|   1     |     2       |     3      |
|   2     |     3       |     6      |
|   3     |     4       |    10      |

## Requirements

- C compiler (e.g., `gcc`)
- MPI library (e.g., MPICH, OpenMPI)

## Compilation

```bash
mpicc -o prefix_sum prefix_sum.c
Execution
bash
Copy
Edit
mpirun -np 4 ./prefix_sum
