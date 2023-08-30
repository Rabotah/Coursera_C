#include <mpi.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int st, size, rank, time, d, k, msg;
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

    time = 0;
    d = 1;
    if (rank <= 9)
        sprintf(way, "%s%d", "/home/falt202204/lamport/0", rank + 1);
    else
        sprintf(way, "%s%d", "/home/falt202204/lamport/", rank + 1);
    strcat(way, ".dat");

    if ((f = fopen(way, "r")) == NULL)
		printf("rank %d, file doesn't exist\n", rank);

    else
    {
        while (fscanf(f, "%d", &k) != EOF)
        {
            time += d;
            if (k == 0)
                printf("internal event at rank %d, time %d\n", time, rank);

            else if (k > 0)
            {
                printf("send msg from rank %d to rank %d at time %d\n", rank, k - 1, time);

                st = MPI_Send(&time, 1, MPI_INT, k - 1, 1, MPI_COMM_WORLD);
                    if (st != MPI_SUCCESS)
                        MPI_Abort(MPI_COMM_WORLD, 4);
            }

            else
            {
                printf("rank %d recv msg from rank %d at time %d\n", rank, abs(k) - 1, time);

                st = MPI_Recv(&msg, 1, MPI_INT, abs(k) - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                if (st != MPI_SUCCESS)
                    MPI_Abort(MPI_COMM_WORLD, 5);

				msg += d;
				if (msg > time)
					time = msg;
                printf("Im rank %d, new time %d\n", rank, time);
			}
		}
        fclose(f);
	}

	MPI_Finalize();
	return 0;
}
