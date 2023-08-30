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
    int st, size, rank, num, i, msg = 0, fin = 2, flag;
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

    srand(rank);

    if (rank == 0)
    {
        st = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        if (st != MPI_SUCCESS)
            MPI_Abort(MPI_COMM_WORLD, 4);
        printf("Rank %d sent marker\n", rank);
        i = 0;
        while (i != REPEAT)
        {
            printf("Rank %d is waiting marker\n", rank);
            st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 5);

            printf("Rank %d recieved marker and started critical section\n", rank);

            sleep(rand() % 2 + 1);

            printf("Rank %d fell asleep\n", rank);

            st = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 6);

            printf("Rank %d sent marker\n", rank);

            sigflag = 1;
            signal(SIGALRM, handler);
            alarm(rand() % 5 + 1);
            while (sigflag)
            {
                st = MPI_Iprobe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &flag, &status);
                if (st != MPI_SUCCESS)
                    MPI_Abort(MPI_COMM_WORLD, 7);

                if (flag)
                {
                    st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 8);

                    st = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 9);
                }
            }

            i++;
        }

        printf("Rank %d ends his sections\n", rank);
        st = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
        if (st != MPI_SUCCESS)
            MPI_Abort(MPI_COMM_WORLD, 10);

        sigflag = 1;
        int count = 0;
        while (sigflag)
        {
            st = MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 11);
            if (flag)
            {
                if (status.MPI_TAG == 0)
                {
                    st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 12);

                    st = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 13);
                }
                if (status.MPI_TAG == 1)
                {
                    st = MPI_Recv(&fin, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 14);

                    printf("Rank %d recv FIN\n", rank);

                    st = MPI_Send(&fin, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 15);
                    printf("Rank %d sent FIN\n", rank);

                    count++;
                    if (count == 2)
                    {
                        break;
                    }
                }
            }
        }
        MPI_Finalize();
        return 0;
    }
    else
    {
        i = 0;
        while (i != REPEAT)
        {
            printf("Rank %d is waiting marker\n", rank);
            st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 16);
            printf("Rank %d recieved marker and started critical section\n", rank);

            sleep(rand() % 2 + 1);

            printf("Rank %d fell asleep\n", rank);

            st = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 17);

            printf("Rank %d sent marker\n", rank);

            sigflag = 1;
            signal(SIGALRM, handler);
            alarm(rand() % 5 + 1);
            while (sigflag)
            {
                st = MPI_Iprobe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &flag, &status);
                if (st != MPI_SUCCESS)
                    MPI_Abort(MPI_COMM_WORLD, 18);

                if (flag)
                {
                    st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 19);

                    st = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 20);
                }
            }

            i++;
        }
        printf("Rank %d ends his sections\n", rank);
        int count = 0;
        sigflag = 1;
        while (sigflag)
        {
            st = MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
            if (st != MPI_SUCCESS)
                MPI_Abort(MPI_COMM_WORLD, 21);
            if (flag)
            {
                if (status.MPI_TAG == 0)
                {
                    st = MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 22);

                    st = MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 23);
                }
                if (status.MPI_TAG == 1)
                {
                    st = MPI_Recv(&fin, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 24);

                    printf("Rank %d recv FIN\n", rank);

                    st = MPI_Send(&fin, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 25);
                    printf("Rank %d sent FIN\n", rank);
                    count++;
                    if (count == 2)
                    {
                        break;
                    }
                }
            }
        }
        MPI_Finalize();
        return 0;

    }

    MPI_Finalize();
    return 0;
}
