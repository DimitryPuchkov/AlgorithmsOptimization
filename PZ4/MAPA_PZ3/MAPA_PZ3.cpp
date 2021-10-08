#include "mpi.h"
#include <iostream>
#include <windows.h>

using namespace std;

double *getMatrix(int n, int m)
{
	int N = m * n;
	double *a = NULL;

	if (a == NULL)
		a = new double[N];

	for (int i = 0; i < N; i++)
	{
		a[i] = (float)(i % 10);
	}

	return a;
}

double norma(double *A, int n, int m)
{
	double res = 0;
	long long i, j;

	for (i = 0; i < n * m; i++)
		res += A[i] * A[i];

	return sqrt(res);
}

double parallel_norma(double *A, int n, int m)
{
	double res = 0;
	long long i, j;

#pragma omp parallel for reduction(+:res)
	for (i = 0; i < n * m; i++)
		res += A[i] * A[i];

	return sqrt(res);
}

void firstTask(int argc, char **argv)
{
	int rank, size;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	if (rank != 0)
	{
		double *v = getMatrix(1, 100000);
		double n = norma(v, 1, 100000);

		MPI_Send(&n, 1, MPI_DOUBLE, 0, 100, MPI_COMM_WORLD);

		cout << "Sended from " << rank << endl;

	}

	if (rank == 0)
	{
		double n = 0;

		for (int i = 1; i < size; i++)
		{
			MPI_Recv(&n, 1, MPI_DOUBLE, i, 100, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			cout << "recived Norma: " << n << "Process: " << i << endl;
		}

	}

	MPI_Finalize();
}

void secondTask(int argc, char **argv)
{
	int rank, size;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank != 0)
	{
		double *v = getMatrix(1, 100000);
		double n = parallel_norma(v, 1, 100000);

		MPI_Send(&n, 1, MPI_DOUBLE, 0, 100, MPI_COMM_WORLD);

		cout << "Sended from " << rank << endl;

	}

	if (rank == 0)
	{
		double n = 0;

		for (int i = 1; i < size; i++)
		{
			MPI_Recv(&n, 1, MPI_DOUBLE, i, 100, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			cout << "recived Norma: " << n << "Process: " << i << endl;
		}

	}

	MPI_Finalize();
}


int main(int argc, char **argv)
{

	int rank, size;
	MPI_Status status;

	/* Init */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank != 0) { // Slaves
		double buf;

		double *v = getMatrix(1, 100000);
		double n = norma(v, 1, 100000);



		if (rank == 1)
		{
			buf = n;
			MPI_Send(&buf, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
			cout << "Sended from" << rank << endl;

		}
		if (rank == 2) {
			buf = n;
			MPI_Send(&buf, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
			cout << "Sended from" << rank << endl;

		}
		

	}
	else { // Master
		double sum = 0, res=0;
		int flag = -1;
		MPI_Request request;
		MPI_Status status;

		while (1) {
			if (flag != 0)
			{
				MPI_Irecv(&res, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
				flag = 0;
				Sleep(10000);
			}
			MPI_Test(&request, &flag, &status);

			if (flag != 0) 
			{
				cout << "recv " << res << "slave " << status.MPI_SOURCE << endl;
				if (status.MPI_SOURCE != -1)
					sum += res;
				flag = -1;
			}


			if (abs(sum - 3376.39) < 0.01)
				break;
		}

		cout << "Summ: " << sum;

	}

	MPI_Finalize();
	return 0;

	//int rank, size;

	
	//secondTask(argc, argv);
	
	
	/*if (rank != 0)
	{
		double *v = getMatrix(1, 100000);
		double n = norma(v, 1, 100000);
		
		MPI_Send(&n, 1, MPI_DOUBLE	, 0, 100, MPI_COMM_WORLD);

		cout << "Sended from" << rank<<endl;
			
	}



	if (rank == 0)
	{
		double n;
		MPI_Request request;
		MPI_Status status;
		int flag = 0;
		MPI_Irecv(&n, 1, MPI_DOUBLE, 1, 100, MPI_COMM_WORLD, &request);
		MPI_Test(&request, &flag, &status);
		if (flag)
			cout << "recived Norma: " << n << "Process: " << 1 << endl;
		else
			cout << "error";
			for (int i = 1; i < 5; i++)
			{
				MPI_Recv(&n, 1, MPI_DOUBLE, i, 100, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
				cout << "recived Norma: " << n << "Process: " << i << endl;
			}

	}
	
	MPI_Finalize();
	return 0;*/
}
