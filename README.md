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
- sanity.c - C program to check if assembly subroutine is correct (aka sanity check)
- Vid_DEMO.mp4 - contains the demo video of the whole MP

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
- The average execution time over 30 runs of both kernels
- The first 10 values of the resulting vector Z

### Comparative Analysis
Benchmarking was done across vector sizes:
- 2^{20} = 1,048,576 elements
- 2^{24} = 16,777,216 elements
- 2^{26} = 67,108,864 elements

Each kernel version was executed 30 times per size, using QueryPerformanceCounter to measure runtime precisely.
#### Results:
- Vector size: 2^20 = 1048576
- Assembly Kernel Average Time (30 runs): 1.1697 ms
- C Kernel Average Time        (30 runs): 1.3477 ms

<img width="567" height="348" alt="image" src="https://github.com/user-attachments/assets/77b3c6ce-21e3-4095-b73c-43a5cb1f9994" />

<img width="359" height="255" alt="image" src="https://github.com/user-attachments/assets/2313a547-d6ec-4a26-a90d-cf57b45049f8" />


- Vector size: 2^24 = 16777216
- Assembly Kernel Average Time (30 runs): 37.0390 ms
- C Kernel Average Time        (30 runs): 35.0534 ms

<img width="494" height="329" alt="image" src="https://github.com/user-attachments/assets/aaed68a0-df33-49f5-96ef-352f19eb15c1" />

<img width="469" height="253" alt="image" src="https://github.com/user-attachments/assets/047400ee-d829-4eb9-8b28-9bf7eed19cce" />

- Vector size: 2^26 = 67108864
- Assembly Kernel Average Time (30 runs): 107.6310 ms
- C Kernel Average Time        (30 runs): 136.6501 ms

<img width="587" height="347" alt="image" src="https://github.com/user-attachments/assets/429df714-30b0-4f82-a4c0-d314f631d710" />

<img width="459" height="249" alt="image" src="https://github.com/user-attachments/assets/0eb094b9-fecd-489c-9e80-c8606ede358e" />

### Analysis and Interpretation

- Small Size (2²⁰): Assembly outperforms C slightly. This is consistent with lower-level optimization benefits like tighter loops and reduced overhead.
- Medium Size (2²⁴): Surprisingly, the C kernel edges ahead. This may point to cache alignment or loop unrolling decisions made by the compiler — or even memory bandwidth saturation that favors C’s predictable pattern.
- Large Size (2²⁶): Assembly clearly pulls ahead with a ~27% speedup. This is where custom ASM implementations shine: bypassing some of C’s abstractions and tapping directly into CPU registers.


### Correctness Check:
To verify if the program is outputing the right values, sanity.c is created to check whether the expected values match the returned value of the assembly.

Code:
- C:\nasm\nasm.exe -f win64 funcasm.asm -o funcasm.obj
- gcc sanity.c funcasm.obj -o sanity.exe
- sanity.exe

Output:


<img width="621" height="274" alt="image" src="https://github.com/user-attachments/assets/c91e48f4-d4e3-4c19-99a1-50b0568b0bd1" />


