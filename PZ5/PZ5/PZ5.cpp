#include "mpi.h"
#include <iostream>

using namespace std;
double* getMatrix(int n, int m)
{
   int N = m * n;
   double* a = NULL;
   if (a == NULL)
      a = new double[N];
   for (int i = 0; i < N; i++)
      a[i] = (float)(i % 10);
   return a;
}

int main(int argc, char** argv)
{
   int rank, size;
   MPI_Status status;
   /* Init */
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   double* r = new double[5] {0, 0, 0, 0, 0};
   double* M = NULL;
   if (rank == 0)
   {
      r = getMatrix(1, 10);
      double *M = getMatrix(10, 10);
      MPI_Scatter(M, 10, MPI_DOUBLE, M, 10, MPI_DOUBLE, 0, MPI_COMM_WORLD);

   }
   //MPI_Bcast(r, 5, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   
   if(rank != 0)
   {
      cout << M[3] <<endl;
   }

   MPI_Finalize();
   return 0;
}
