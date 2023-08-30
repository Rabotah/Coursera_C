#include <mpi.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    int N = 120;
    int mass[N];
    int rank;
    int size;
    
    int st = MPI_Init(&argc, &argv);
    if (st != MPI_SUCCESS)
	MPI_Abort(MPI_COMM_WORLD, 1);
    st = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (st != MPI_SUCCESS)
	MPI_Abort(MPI_COMM_WORLD, 2);
    st = MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (st != MPI_SUCCESS)
	MPI_Abort(MPI_COMM_WORLD, 3);

    int mass1[N/size];
    for (int it = size*rank; it < size*rank + N/size + 1; it++)
        mass1[it] = rank;
    st = MPI_Gather(&mass1[size*rank], N/size, MPI_INT, mass, N/size,  MPI_INT, 0, MPI_COMM_WORLD);
    if (st != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, 5);

    if (N % size != 0)
    {
	cout << "Error";
	MPI_Abort(MPI_COMM_WORLD, 6);
    }
    if (rank == 0)
    {
        ofstream file;
	file.open("mass.txt");
	for (int i = 0; i < N; i++)
	    file << mass[i] << ' ';
	file.close();
    }

    MPI_Finalize();

    return 0;
}