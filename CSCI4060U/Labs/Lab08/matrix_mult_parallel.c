#include <stdio.h>
#include <CL/cl.h>

/*
Efficiency Problem:
    We are creating a large number of kernels since we create one for each element in the output matrix. This is inefficient and could cause a lot of overhead.

Solution:
    Instead of having each kernel do a single multiplication, we can have each kernel do a row of the output matrix. 
    This will reduce the number of kernels we need to create and will reduce the overhead of creating and destroying kernels.
*/

/* Kernel
__kernel void matrix_mult(int m_dim, int k_dim, int n_dim, __global float *a, __global float *b, __global float *ab) {
    int m = get_global_id(0);
    int n = get_global_id(1);

    float temp = 0.0;
    for (int i = 0; i < k_dim; i++) {
        temp += a[m*k_dim+i] * b[i*n_dim+n];
    }

    ab[m*n_dim+n] = temp;
}
*/

void parallel_matrix_mult(float* a, float* b, float* ab, const int M, const int N, const int K); //[AB] = [A] * [B]

void seq_matrix_mult(
    int m_dim, int k_dim, int n_dim,
    float *a, float *b, float *ab); //[AB] = [A] * [B]

int main()
{
    int md = 4;
    int kd = 2;
    int nd = 3;
    int k, n, m;

    printf("MATRIX A\n");
    float matrix_a[md * kd];
    for (m = 0; m < md; m++)
    {
        for (k = 0; k < kd; k++)
        {
            matrix_a[m * kd + k] = m * k + 1;
            printf("%f\t", matrix_a[m * kd + k]);
        }
        printf("\n");
    }

    printf("MATRIX B\n");
    float matrix_b[kd * nd];
    for (k = 0; k < kd; k++)
    {
        for (n = 0; n < nd; n++)
        {
            matrix_b[k * nd + n] = k * n + 1;
            printf("%f\t", matrix_b[k * nd + n]);
        }
        printf("\n");
    }

    printf("MATRIX AB (RESULT)\n");
    float matrix_result[md * nd];

    seq_matrix_mult(md, kd, nd,
                    matrix_a, matrix_b, matrix_result);

    for (m = 0; m < md; m++)
    {
        for (n = 0; n < nd; n++)
        {
            printf("%f\t", matrix_result[m * nd + n]);
        }
        printf("\n");
    }

}


// matrix a [m by k]
// matrix b [k by n]
// matrix ab [m by n]
void seq_matrix_mult(
    int m_dim, int k_dim, int n_dim,
    float *a, float *b, float *ab)
{

    int m, k, n;
    float temp;

    for (m = 0; m < m_dim; m++)
    {
        for (n = 0; n < n_dim; n++)
        {
            temp = 0.0;
            // do actual multiplication
            // ab[m][n] = sum(a[m][k] * b[k][n])
            for (k = 0; k < k_dim; k++)
            {
                temp += *(a + (m * k_dim + k)) * *(b + (k * n_dim + n));
                // same as temp += a[m][k] * b[k][n]
            }
            *(ab + (m * n_dim + n)) = temp;
            // same as ab[m][n]
        }
    }
}