#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

// Declare external assembly kernel
extern void asmhello(float* Z, int n, float A, float* X, float* Y);

// Random float generator between 0 and 1
float rand_float() {
    return (float)rand() / RAND_MAX;
}

int main() {
    srand((unsigned int)time(NULL));  // Seed RNG

    // Desired sizes: 2^20, 2^24, 2^28 (or adjust as needed)
    int sizes[] = {1 << 20, 1 << 24, 1 << 26};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    float A = 1.5f;  // Sample scalar value

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        printf("\n=== Benchmarking Assembly Kernel ===\n");
        printf("Vector size: 2^%d = %d\n", (int)(log(n)/log(2)), n);

        // Allocate memory
        float* X = (float*)malloc(n * sizeof(float));
        float* Y = (float*)malloc(n * sizeof(float));
        float* Z = (float*)malloc(n * sizeof(float));
        if (!X || !Y || !Z) {
            printf("Memory allocation failed for size %d\n", n);
            free(X); free(Y); free(Z);
            continue;
        }

        // Initialize X and Y with random floats
        for (int i = 0; i < n; i++) {
            X[i] = rand_float();
            Y[i] = rand_float();
        }

        // Timing loop
        LARGE_INTEGER freq, start, end;
        QueryPerformanceFrequency(&freq);
        double total_time = 0.0;

        for (int run = 0; run < 30; run++) {
            QueryPerformanceCounter(&start);
            asmhello(Z, n, A, X, Y);
            QueryPerformanceCounter(&end);
            double elapsed = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
            total_time += elapsed;
        }

        // Print average execution time
        double avg_time = total_time / 30.0;
        printf("Average Execution Time (30 runs): %.4f ms\n", avg_time);

        // Show first 10 elements of Z
        printf("First 10 results of Z:\n");
        for (int i = 0; i < 10 && i < n; i++) {
            printf("Z[%d] = %.4f\n", i, Z[i]);
        }

        free(X); free(Y); free(Z);
    }

    return 0;
}