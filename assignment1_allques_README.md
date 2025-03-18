description : # MPI Random Walker Simulation

This project simulates random walkers moving across a 1D domain using **MPI (Message Passing Interface)** for parallel processing in C++.

## Overview

- Each MPI process controls a segment of the domain.
- Multiple walkers start in each process with random step counts.
- Walkers move step-by-step and are passed to the next process if they cross local boundaries.
- At the last process, walkers wrap around to the start of the domain.

## Features

- Parallel processing using MPI
- Randomized walker step counts
- Inter-process communication with `MPI_Send` and `MPI_Recv`

## Requirements

- C++ compiler (e.g., `g++`)
- MPI library (e.g., MPICH, OpenMPI)

## Compilation

```bash
mpic++ -o random_walker main.cpp

