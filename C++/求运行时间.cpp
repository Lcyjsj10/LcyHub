#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include <chrono>

auto start_time = chrono::high_resolution_clock::now();
// for (int i = 0; i < n; i++)
// {
//     for (int k = 0; k < n; k++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             C[i][j] += A[i][k] * B[k][j];
//         }
//     }
// }
auto serial_time = chrono::high_resolution_clock::now();