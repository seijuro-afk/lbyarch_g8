#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

// Assembly kernel declaration
extern void asmhello(float* Z, int n, float A, float* X, float* Y);

// C version of the kernel
void c_kernel(float* Z, int n, float A, float* X, float* Y) {
    for (int i = 0; i < n; i++) {
        Z[i] = A * X[i] + Y[i];
    }
}

// Random float generator
float rand_float() {
    return (float)rand() / RAND_MAX;
}

int main() {
    srand((unsigned int)time(NULL));  // Seed RNG

    int sizes[] = {1 << 20, 1 << 24, 1 << 26};  // 1M, 16M, 64M
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    float A = 1.5f;

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        printf("\n=== Benchmarking Kernels ===\n");
        printf("Vector size: 2^%d = %d\n", (int)(log(n)/log(2)), n);

        // Allocate memory
        float* X = (float*)malloc(n * sizeof(float));
        float* Y = (float*)malloc(n * sizeof(float));
        float* Z_asm = (float*)malloc(n * sizeof(float));
        float* Z_c = (float*)malloc(n * sizeof(float));
        if (!X || !Y || !Z_asm || !Z_c) {
            printf("Memory allocation failed\n");
            free(X); free(Y); free(Z_asm); free(Z_c);
            continue;
        }

        // Initialize input arrays
        for (int i = 0; i < n; i++) {
            X[i] = rand_float();
            Y[i] = rand_float();
        }

        LARGE_INTEGER freq, start, end;
        QueryPerformanceFrequency(&freq);

        // Time assembly kernel
        double asm_time = 0.0;
        for (int run = 0; run < 30; run++) {
            QueryPerformanceCounter(&start);
            asmhello(Z_asm, n, A, X, Y);
            QueryPerformanceCounter(&end);
            asm_time += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
        }

        // Time C kernel
        double c_time = 0.0;
        for (int run = 0; run < 30; run++) {
            QueryPerformanceCounter(&start);
            c_kernel(Z_c, n, A, X, Y);
            QueryPerformanceCounter(&end);
            c_time += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
        }

        // Print results
        printf("Assembly Kernel Average Time (30 runs): %.4f ms\n", asm_time / 30.0);
        printf("C Kernel Average Time        (30 runs): %.4f ms\n", c_time / 30.0);

        // First 10 elements for quick check
        printf("First 10 results from Assembly:\n");
        for (int i = 0; i < 10 && i < n; i++) {
            printf("Z_asm[%d] = %.4f\n", i, Z_asm[i]);
        }

        printf("First 10 results from C:\n");
        for (int i = 0; i < 10 && i < n; i++) {
            printf("Z_c[%d] = %.4f\n", i, Z_c[i]);
        }

        free(X); free(Y); free(Z_asm); free(Z_c);
    }

    return 0;
}