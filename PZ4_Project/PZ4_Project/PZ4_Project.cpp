﻿#include "mpi.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <array>

using namespace std;

double* getMatrix(int n, int m)
{
   int N = m * n;
   double* a = NULL;

   if (a == NULL)
      a = new double[N];

   for (int i = 0; i < N; i++)
   {
      a[i] = (float)(i % 10);
   }

   return a;
}

double norma(double* A, int n, int m)
{
   double res = 0;
   long long i, j;

   for (i = 0; i < n * m; i++)
      res += A[i] * A[i];

   return sqrt(res);
}

double parallel_norma(double* A, int n, int m)
{
   double res = 0;
   long long i, j;

#pragma omp parallel for reduction(+:res)
   for (i = 0; i < n * m; i++)
      res += A[i] * A[i];

   return sqrt(res);
}



int main(int argc, char** argv)
{

   int rank, size;
   MPI_Status status;

   /* Init */
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   if (rank > 1)
   {
      double* v = getMatrix(1, 100000);
      double n = norma(v, 1, 100000);
      MPI_Send(&n, 1, MPI_DOUBLE, 0, 100, MPI_COMM_WORLD);
      cout << "Sended from " << rank << endl;
   }
   if (rank == 1) {
      double* v = getMatrix(1, 100000);
      double n = norma(v, 1, 100000);
      Sleep(10000);
      MPI_Send(&n, 1, MPI_DOUBLE, 0, 100, MPI_COMM_WORLD);
      cout << "Sended from " << rank << endl;
   }

   if (rank == 0) {
      double n[9] = { 0 };
      int *flag = new int[size] {0};
      int *flagr = new int[size] {0};
      bool w = true;
      MPI_Request *request = new MPI_Request[size];
      MPI_Status status;
      for (int i = 1; i < size; i++)
         MPI_Irecv(&n[i - 1], 1, MPI_DOUBLE, i, 100, MPI_COMM_WORLD, &request[i - 1]);
      bool cont = true;
      while (cont)
      {
         for (int i = 1; i < size; i++)
         {
            MPI_Test(&request[i - 1], &flag[i - 1], &status);
            if (flag[i - 1] != 0 && flagr[i - 1] == 0)
            {
               cout << "recived from " << i << " norma: " << n[i - 1] << endl;
               flagr[i - 1] = 1;
            }
         }
         cont = false;
         for(int i = 1; i < size; i++)
            if(flag[i] == 0)
               cont = true;
      }
         

         cout << "recived from " << 1 << " norma: " << n[0] << endl;

   }

   MPI_Finalize();
   return 0;
}