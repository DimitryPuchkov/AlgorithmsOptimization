#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	int rank, size, my_rank,p ;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	//MP//I_Comm_size(MPI_COMM_WORLD, &p);

	cout << "Total process: "<< size <<" Current rank: " <<rank;
		


	MPI_Finalize();
	return 0;
}
