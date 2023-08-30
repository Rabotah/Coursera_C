#include <mpi.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int st, size, rank, d, k, i;
    FILE *f;
    char way[18];
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

    int *time = (int*) malloc(size*sizeof(int));
    for (i = 0; i < size; i++)
        time[i] = 0;
    int *msg = (int*) malloc(size*sizeof(int));
    d = 1;
    if (rank <= 9)
        sprintf(way, "%s%d", "/home/falt202204/vector/v0", rank + 1);
    else
        sprintf(way, "%s%d", "/home/falt202204/vector/v", rank + 1);
    strcat(way, ".dat");

    if ((f = fopen(way, "r")) == NULL)
		printf("rank %d, file doesn't exist\n", rank);

    else
    {
        while (fscanf(f, "%d", &k) != EOF)
        {
            time[rank] += d;
            if (k == 0)
                for (i = 0; i < size; i++)
                    printf("internal event from rank %d, time %d for rank %d\n", rank, time[i], i);

            else if (k > 0)
            {
                for (i = 0; i < size; i++)
                    printf("send msg from rank %d to rank %d at time %d for rank %d\n", rank, k - 1, time[i], i);

                st = MPI_Send(time, size, MPI_INT, k - 1, 1, MPI_COMM_WORLD);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 4);
            }

            else
            {
                for (i = 0; i < size; i++)
                    printf("rank %d recv msg from rank %d at time %d for rank %d\n", rank, abs(k) - 1, time[i], i);

                st = MPI_Recv(msg, size, MPI_INT, abs(k) - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                if (st != MPI_SUCCESS)
                    MPI_Abort(MPI_COMM_WORLD, 5);

                for (i = 0; i < size; i++)
                {
                    if (msg[i] > time[i])
                	time[i] = msg[i];
            	    printf("Im rank %d, new time %d for rank %d\n", rank, time[i], i);
            	}
			}
		}
        fclose(f);
	}

	MPI_Finalize();
	return 0;
}
