#include <stdio.h>

// Correct declaration (must match assembly label)
extern void saxpy_asm(int n, float A, float* X, float* Y, float* Z);

int main() {
    float A = 2.0f;
    float X[] = { 1.0f, 2.0f, 3.0f };
    float Y[] = { 11.0f, 12.0f, 13.0f };
    float Z[3] = { 0.0f, 0.0f, 0.0f };  // Initialize all elements explicitly

    printf("Input values:\n");
    printf("A = %.1f\n", A);
    printf("X = [%.1f, %.1f, %.1f]\n", X[0], X[1], X[2]);
    printf("Y = [%.1f, %.1f, %.1f]\n", Y[0], Y[1], Y[2]);
    printf("\n");

    saxpy_asm(3, A, X, Y, Z);

    printf("Results (Z = A*X + Y):\n");
    for (int i = 0; i < 3; i++) {
        printf("Z[%d] = %.1f\n", i, Z[i]);
    }

    // Expected results: Z[0] = 13.0, Z[1] = 16.0, Z[2] = 19.0
    printf("\nExpected: Z[0] = 13.0, Z[1] = 16.0, Z[2] = 19.0\n");

    return 0;
}