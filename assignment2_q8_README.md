# MPI Parallel Matrix Transposition

This project demonstrates **parallel matrix transposition** using **MPI (Message Passing Interface)**. Each process is responsible for transposing a portion of the matrix to achieve improved efficiency in large-scale computations.

## Problem Statement

Given a matrix **A**, the goal is to compute its transpose **B**, where:

B[j][i] = A[i][j]

csharp
Copy
Edit

## Features

- Matrix is divided row-wise among processes.
- Each process transposes its portion locally.
- Transposed sections are gathered to form the final result.
- Works with any square matrix size that is divisible by the number of processes.

## Matrix Size

Defined by the constant:

```c
#define SIZE 6  // Change as needed (ensure divisible by process count)
Example
Original 6x6 Matrix:

Copy
Edit
  1.0   2.0   3.0   4.0   5.0   6.0
  7.0   8.0   9.0  10.0  11.0  12.0
 13.0  14.0  15.0  16.0  17.0  18.0
 19.0  20.0  21.0  22.0  23.0  24.0
 25.0  26.0  27.0  28.0  29.0  30.0
 31.0  32.0  33.0  34.0  35.0  36.0
Transposed Matrix:

Copy
Edit
  1.0   7.0  13.0  19.0  25.0  31.0
  2.0   8.0  14.0  20.0  26.0  32.0
  3.0   9.0  15.0  21.0  27.0  33.0
  4.0  10.0  16.0  22.0  28.0  34.0
  5.0  11.0  17.0  23.0  29.0  35.0
  6.0  12.0  18.0  24.0  30.0  36.0
Requirements
C compiler (e.g., gcc)
MPI library (e.g., MPICH, OpenMPI)
Compilation
bash
Copy
Edit
mpicc -o matrix_transpose matrix_transpose.c
Execution
bash
Copy
Edit
mpirun -np 3 ./matrix_transpose
