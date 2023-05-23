#include <iostream>
#include <omp.h>

using namespace std;

#define MATRIX_SIZE 2500

void matrix_multiply(int** A, int** B, int** C, int n) {
    #pragma omp parallel for // распараллеливание цикла по строкам
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void print_matrix(int** M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int** A = new int* [MATRIX_SIZE];
    int** B = new int* [MATRIX_SIZE];
    int** C = new int* [MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; i++) {
        A[i] = new int[MATRIX_SIZE];
        B[i] = new int[MATRIX_SIZE];
        C[i] = new int[MATRIX_SIZE];
    }

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            A[i][j] = rand() % 9 + 1;
            B[i][j] = rand() % 9 + 1;
        }
    }
    //cout << "matrix A:" << endl;
    //print_matrix(A, MATRIX_SIZE);
    //cout << "matrix B:" << endl;
    //print_matrix(B, MATRIX_SIZE);

    for (int i = 1; i < 30; i++) 
    {
        int num_threads = i;
        omp_set_num_threads(num_threads);

        double start_time = omp_get_wtime();
        matrix_multiply(A, B, C, MATRIX_SIZE);
        double end_time = omp_get_wtime();
        double elapsed_time = end_time - start_time;
        printf("%dx%d, thNum %d - %f sec\n", MATRIX_SIZE, MATRIX_SIZE, num_threads, elapsed_time);
        //cout << "matrix C:" << endl;
        //print_matrix(C, MATRIX_SIZE);
    }
    /*for (int i = 0; i < MATRIX_SIZE; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }

    delete[] A;
    delete[] B;
    delete[] C;*/
}