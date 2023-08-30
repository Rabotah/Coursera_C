#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    int rank, size, n;
    
    int st = MPI_Init(&argc, &argv);
    if (st != MPI_SUCCESS)
	MPI_Abort(MPI_COMM_WORLD, 1);
    st = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (st != MPI_SUCCESS)
	MPI_Abort(MPI_COMM_WORLD, 2);
    st = MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (st != MPI_SUCCESS)
	MPI_Abort(MPI_COMM_WORLD, 3);
	
    int * mass1 = new int [rank + 1];
    for (size_t i = 0; i < rank + 1; i++)
	mass1[i] = rank+1;
    int * recvcount, *displs, *mass;
    if (rank == 0)
    {
	recvcount = new int[size];
	displs = new int [size];
	for (int i = 0; i < size; i++)
	{
	    recvcount[i] = i+1;
	    if (i == 0)
		displs[0] = 0;
	    else
		displs[i] = i + recvcount[i-1] + displs[i-1];
	}
	n = size + displs[size-1];
	mass = new int [n];
	for (size_t i = 0; i < n; i++)
    	    mass[i] = 0;
    }
    st = MPI_Gatherv(mass1, (rank+1), MPI_INT, mass, recvcount, displs, MPI_INT, 0, MPI_COMM_WORLD);
    if (st != MPI_SUCCESS)
    {
	delete [] mass;
	delete [] mass1;
	delete [] recvcount;
	delete [] displs;
        MPI_Abort(MPI_COMM_WORLD, 5);
    }
    if (rank == 0)
    {
	for (size_t i = 0; i < n; i++)
	    cout << mass[i];
	delete [] mass;
	delete [] mass1;
	delete [] recvcount;
	delete [] displs;
    }
    MPI_Finalize();
    return 0;
}