#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int st, size, rank, num, i, msg = 0;
    int REPEAT = 3;
    MPI_Status status;

    st = MPI_Init(&argc, &argv);
    if (st != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, 1);
    st = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (st != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, 2);
    st = MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (st != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, 3);

    if (rank == 0)
    {
        for (i = 0; i < REPEAT*(size - 1); i++)
        {
            st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 4);
            printf("Rank 0 recv request from %d\n", status.MPI_SOURCE);

            st = MPI_Send(&msg, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 5);
            printf("Rank 0 sent answer to %d\n", status.MPI_SOURCE);

            st = MPI_Recv(&msg, 1, MPI_INT, status.MPI_SOURCE, 2, MPI_COMM_WORLD, &status);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 6);
            printf("Rank 0 recv release from %d\n", status.MPI_SOURCE);
        }
    }
    else
    {
        srandom(rank);
        for (i = 0; i < REPEAT; i++)
        {
            st = MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 7);
            printf("Rank %d sent request to rank 0\n", rank);

            st = MPI_Recv(&msg, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 8);
            printf("Rank %d recv answer from rank 0\n", rank);

            sleep(random() % 5 + 1);

            st = MPI_Send(&msg, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 9);
            printf("Rank %d sent release to rank 0\n", rank);

            sleep(random() % 5 + 1);
        }
    }

    MPI_Finalize();
    return 0;
}
