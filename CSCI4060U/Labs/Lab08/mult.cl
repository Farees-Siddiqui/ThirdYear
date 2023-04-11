__kernel void matrix_mult(int m_dim, int k_dim, int n_dim, __global float *a, __global float *b, __global float *ab) {
    int m = get_global_id(0);
    int n = get_global_id(1);

    float temp = 0.0;
    for (int i = 0; i < k_dim; i++) {
        temp += a[m*k_dim+i] * b[i*n_dim+n];
    }

    ab[m*n_dim+n] = temp;
}