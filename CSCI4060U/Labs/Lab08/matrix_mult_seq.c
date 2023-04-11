#include <stdio.h>

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
