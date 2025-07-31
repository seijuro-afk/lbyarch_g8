# SAXPY Kernel Benchmark

### Overview
This project benchmarks the performance of a custom vector kernel written in both C and x86-64 assembly, comparing execution times across large vector sizes. The kernel operation performed is:

*Required to use functional scalar SIMD registers
*Required to use functional scalar SIMD floating-point instructions

Input: Scalar variable n (integer) contains the length of the vector;  Scalar variable A is a single-precision float. Vectors X, Y and Z are single-precision float.
Process: Z[i] = A * X[i] + Y[i]

Example:

A --> 2.0
x -> 1.0, 2.0, 3.0
y -> 11.0, 12.0, 13.0
(answer) z--> 13.0, 16.0, 19.0

Output: store result in vector Z.  Display the result of 1st ten elements of vector Z for all versions of kernel (i.e., C and x86-64).

### Files
- main.c - C program that benchmarks the assembly kernel
- funcasm.asm - x86-64 assembly implementation of the kernel logic

### Requirements
- Windows OS
- NASM assembler (e.g., located at C:\nasm\nasm.exe)
- MinGW-w64 or MSVC for compiling C code

### Setup and Compile Steps

C:\nasm\nasm.exe -f win64 funcasm.asm -o funcasm.obj
gcc main.c funcasm.obj -o saxpy.exe
saxpy.exe

At execution, program benchmarks the kernel for vector sizes:
- 2^{20} = 1,048,576
- 2^{24} = 16,777,216
- 2^{26} = 67,108,864
  
And prints:
- The average execution time over 30 runs
- The first 10 values of the resulting vector Z



