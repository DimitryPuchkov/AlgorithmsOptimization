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
	{
		a[i] = (float)(i % 10);
	}

	return a;
}

double norma(double *A, int n, int m)
{
	double res = 0;
	long long i, j;

#pragma omp parallel for reduction(+:res)
	for (i = 0; i < n * m; i++)
		res += A[i] * A[i];

	return sqrt(res);
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
		int buf;

		if (rank == 1) {
			buf = 1;
			MPI_Send(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
		if (rank == 2) {
			buf = 2;
			MPI_Send(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}

	}
	else { // Master
		int sum = 0;
		int flag = -1, res;
		MPI_Request request;
		MPI_Status status;
		while (1) {
			if (flag != 0)
			{
				MPI_Irecv(&res, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
				flag = 0;
			}
			MPI_Test(&request, &flag, &status);

			if (flag != 0) {
				printf("recv : %d, slave : %d\n", res, status.MPI_SOURCE);
				if (status.MPI_SOURCE != -1)
					sum += res;
				flag = -1;
			}

			cout << sum;
			if (sum == 3)
				break;
		}

		printf("sum : %d\n", sum);
	}

	MPI_Finalize();
	return 0;

	/*int rank, size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank != 0)
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
			/*for (int i = 1; i < 5; i++)
			{
				MPI_Recv(&n, 1, MPI_DOUBLE, i, 100, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
				cout << "recived Norma: " << n << "Process: " << i << endl;
			}

	}
	
	MPI_Finalize();
	return 0;*/
}
