#include "mpi.h"
#include <iostream>

using namespace std;
double *getMatrix(int n, int m)
{
   int N = m * n;
   double *a = NULL;
   if (a == NULL)
      a = new double[N];
   for (int i = 0; i < N; i++)
      a[i] = (float)(i % 15);
   return a;
}

double* AB_parallel(double* A, double* B, int n, int m, int l)
{
   long long i, j, k;
   double* C = new double[n * l]{ 0 };
#pragma omp parallel for num_threads(8) private(j, k)
   for (i = 0; i < n; i++)
      for (j = 0; j < l; j++)
         for (k = 0; k < m; k++)
            C[i * l + j] += A[i * m + k] * B[k * l + j];

   return C;
}


int main(int argc, char **argv)
{
   int rank, size= 0;
   MPI_Status status;
   /* Init */
   
   int m = 10; // число столбцов и размер вектора
   int n = 500; //число строк ( по ним идет разбиение матрицы)
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   double *r = new double[m]{ 0};
   double *M = NULL;
   double *data = new double[m*n/size] {0};
   double *result = new double[n]{0};
   if (rank == 0)
   {
      M = getMatrix(n, m);
      r = getMatrix(1, m);
   }
   //for (int i = 0; i < 10; i++) cout<<"data before: " << rank << ":  " << data[i]<<endl;
   MPI_Scatter(M, m*n/size, MPI_DOUBLE, data, m*n/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   //if(rank == 0) cout<<"************************"<<endl;
   //for(int i = 0; i<n*m/10;i++) cout << "data after: " << rank << ":  " << data[i] << endl;

   MPI_Bcast(r, m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   //for (int i = 0; i < m; i++) cout << "r: " << rank << ":  " << r[i] << endl;

   //Calculate matrix
   double *rs = AB_parallel(data, r, n, m, 1 );
   //for(int i = 0; i<n/10; i++)
     //cout<<rs[0]<<endl;
      

   MPI_Gather(rs, n/size, MPI_DOUBLE, result, n/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   
   if(rank == 0)
   {
      int i = 0;
      for (i = 0; i < n; i++) cout << result[i] << endl;
      cout << "*************************" << endl << i;
   }
      
   /*double *result= AB_parallel(data, r, 1, 10, 1);*/
  //cout<<result[0]<<endl;


   //cout << "data after: " << rank << ":  "<< data<<endl;
   //MPI_Gather(M1, 1, MPI_DOUBLE, M2, 10, MPI_DOUBLE, 0, MPI_COMM_WORLD);


   //if (rank != 0)
   //{
   //   cout << M2[1] << endl;
   //}

   MPI_Finalize();
   return 0;
}
