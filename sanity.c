#include <stdio.h>

// Declare external assembly kernel
extern void asmhello(float* Z, int n, float A, float* X, float* Y);

int main() {
    float A = 2.0f;
    float X[3] = {1.0f, 2.0f, 3.0f};
    float Y[3] = {11.0f, 12.0f, 13.0f};
    float Z[3] = {0.0f, 0.0f, 0.0f};

    int n = 3;
    asmhello(Z, n, A, X, Y);

    printf("Verifying asmhello: Z = A * X + Y\n");
    for (int i = 0; i < n; i++) {
        float expected = A * X[i] + Y[i];
        printf("Z[%d] = %.1f (Expected: %.1f)\n",
               i, Z[i], expected);
    }

    return 0;
}