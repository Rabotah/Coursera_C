#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int sigflag = 1;

void handler(int n)
{
    sigflag = 0;
}

int main(int argc, char *argv[])
{
    int st, size, rank, num, i;
    int RANK = 1, TIMEOUT = 5, VOTE = 0, OK = 1, COORD = 2, msg = 0, flag = 0;
    MPI_Status status;

    signal(SIGALRM, handler);
    st = MPI_Init(&argc, &argv);
    if (st != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, 1);
    st = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (st != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, 2);
    st = MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (st != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, 3);

    srand(rank);
    num = rand();
    if (num % 2 != 0 && rank != RANK)
    {
        printf("Rank %d stopped it's work\n", rank);
        MPI_Finalize();
        return 0;
    }


    
    if (rank == RANK)
    {
        printf("Rank %d is the coordinator\n", rank);
        for (i = rank+1; i < size; ++i)
            MPI_Send(&rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        alarm(TIMEOUT);

        while(sigflag)
        {
            st = MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 4);

            if (flag && status.MPI_TAG == OK)
            {
                printf("rank %d recv okay\n", rank);
                st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, OK, MPI_COMM_WORLD, &status);
                if (st != MPI_SUCCESS)
                    MPI_Abort(MPI_COMM_WORLD, 5);

                alarm(0);

                st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, COORD, MPI_COMM_WORLD, &status);
                if (st != MPI_SUCCESS)
                    MPI_Abort(MPI_COMM_WORLD, 6);
                printf("coordinator of process %d get msg from rank %d\n", rank, status.MPI_SOURCE);

                MPI_Finalize();
                return 0;
            }
            else if (flag && status.MPI_TAG == VOTE)
            {
                printf("rank %d recv vote from %d, sent ok\n", rank, status.MPI_SOURCE);
                st = MPI_Send(&msg, 1,MPI_INT, status.MPI_SOURCE, OK, MPI_COMM_WORLD);
                if (st != MPI_SUCCESS)
                    MPI_Abort(MPI_COMM_WORLD, 7);
            }
        }

        printf("rank %d is oranizer\n", rank);
        for (i = 0; i < size; ++i)
            if (rank != RANK)
                MPI_Send(&rank, 1, MPI_INT, i, COORD, MPI_COMM_WORLD);
        MPI_Finalize();
        return 0;
    }
    else
    {
        st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if (st != MPI_SUCCESS)
            MPI_Abort(MPI_COMM_WORLD, 8);

        if (status.MPI_TAG == COORD)
        {
            printf("coordinator of proess %d recv msg from rank %d\n", rank, status.MPI_SOURCE);
            MPI_Finalize();
            return 0;
        }

        printf("rank %d recv vote from %d, sent ok\n", rank, status.MPI_SOURCE);

        st = MPI_Send(&msg, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
        if (st != MPI_SUCCESS)
            MPI_Abort(MPI_COMM_WORLD, 100);

        for (i = rank+1; i < size; i++)
        {
            st = MPI_Send(&rank, 1, MPI_INT, i, VOTE, MPI_COMM_WORLD);
            if (st != MPI_SUCCESS)
            MPI_Abort(MPI_COMM_WORLD, 9);
        }

        alarm(TIMEOUT);
        while(sigflag)
        {
            st = MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 10);

            if (flag)
            {
                st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                if (st != MPI_SUCCESS)
                    MPI_Abort(MPI_COMM_WORLD, 11);

                if (status.MPI_TAG == VOTE)
                {
                    printf("rank %d recv vote from %d, sent ok\n", rank, status.MPI_SOURCE);

                    st = MPI_Send(&msg, 1, MPI_INT, status.MPI_SOURCE, OK, MPI_COMM_WORLD);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 12);
                } else if (status.MPI_TAG == OK)
                {
                    printf("rank %d recv okay from %d\n", rank, status.MPI_SOURCE);
                    alarm(0);
                } else if (status.MPI_TAG == COORD)
                {
                    printf("coordinator of proc %d recv ,sg from %d\n", rank, status.MPI_SOURCE);
                    MPI_Finalize();
                    return 0;
                }
            }
        }
        printf("rank %d is coordinator",rank);
        for (i = 0; i < size; i++)
            if (rank != RANK)
            {
                st = MPI_Send(&rank, 1, MPI_INT, i, COORD, MPI_COMM_WORLD);
                if (st != MPI_SUCCESS)
                    MPI_Abort(MPI_COMM_WORLD, 8);
            }
        MPI_Finalize();
        return 0;
    }
    MPI_Finalize();
    return 0;
}
