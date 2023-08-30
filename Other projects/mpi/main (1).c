#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int st, size, rank, time_st, msg[2], recv_msg[2], rank_now, time_cli, rec_rank, d, time_cli_wait, new_time;
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
    srandom(rank);
    if (rank == 0)
    {
           time_st = random() % 21;
           rank_now = 0;
           while(rank_now < size - 1)
           {
               st = MPI_Recv(&rec_rank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
               if (st != MPI_SUCCESS)
                   MPI_Abort(MPI_COMM_WORLD, 4);
                rank_now ++;
                time_st += random() % 21;
                printf("I got a msg from %d at %d\n", rec_rank, time_st);
                d = random() % 4;
                time_st += d;
                msg[0] = time_st;
                msg[1] =  d;
                st = MPI_Send(&msg, 2*sizeof(int), MPI_INT, rec_rank, 1, MPI_COMM_WORLD);
                if (st != MPI_SUCCESS)
                    MPI_Abort(MPI_COMM_WORLD, 5);
                printf("I sent a msg to %d at %d with d = %d\n", rec_rank, time_st, d);
           }
    }
    else
    {
       time_cli = rand() % 21;
       st = MPI_Send(&rank, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
       if (st != MPI_SUCCESS)
           MPI_Abort(MPI_COMM_WORLD, 6);
       st = MPI_Recv(&recv_msg, 2*sizeof(int), MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
       if (st != MPI_SUCCESS)
           MPI_Abort(MPI_COMM_WORLD, 7);
       time_cli_wait = recv_msg[0] + 5 + random() % 6;
       new_time = time_cli + time_cli_wait - ceilf((time_cli_wait - time_cli - recv_msg[1])/2.0);
       printf("T0 =  %d,  T1 = %d, msg (%d, %d), new time = %d\n", time_cli, time_cli_wait, recv_msg[0], recv_msg[1], new_time);
    }
    MPI_Finalize();
    return 0;
};
