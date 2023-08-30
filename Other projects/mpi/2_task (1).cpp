#include <iostream>
#include <fstream>
#include <mpi.h>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]){
    int init = MPI_Init(&argc, &argv);
    if(init != MPI_SUCCESS){
        cout <<"Error!" ;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
    MPI_Status st;
    int size, rank, N;
    
    ifstream f("N.txt");
    
    int sz = MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(sz != MPI_SUCCESS){
        cout <<"Error!" ;
        MPI_Abort(MPI_COMM_WORLD, 2);
    }
    
    int rk = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(sz != MPI_SUCCESS){
        cout <<"Error!" ;
        MPI_Abort(MPI_COMM_WORLD, 3);
    }
    if(rank == 0)
	f >> N;

    int bc = MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (bc != MPI_SUCCESS)
    {
        cout << "Error!";
        MPI_Abort(MPI_COMM_WORLD,4);
    }
     
    double sum(0.0), h(2.0/N), m(0.0), t(0.0); 
    
    m = m + N*rank/size*h;
    
    for(int i = 0; i <= N/size-1; i++) 
    {
    	t = t + 0.5*h*(sqrt(4.0 - m*m) + sqrt(4.0 - (m+h)*(m+h)));
    	m = m + h;
    }
    
    int rd = MPI_Reduce(&t, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rd != MPI_SUCCESS)
    {
	cout << "Error!";
	MPI_Abort(MPI_COMM_WORLD, 5);
    }   
    
    if (rank == 0)
	cout << "Pi = " << sum;

    f.close();
    MPI_Finalize();
    return 0;
}
