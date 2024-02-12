#include <stdio.h>
#include <string.h>

#include <mpi.h>

#include "arraymalloc.h"
#include "mpibcastc.h"

int main(void)
{
  static int nx = 1000, ny = 2000, nz = 3000;

  int i, j, k;

  int rank;
  
  MPI_Count cval, clen;

  MPI_Count ***array;

  MPI_Init(NULL, NULL);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  array = (MPI_Count ***) arraymalloc3d(nx, ny, nz, sizeof(MPI_Count));

  clen = ((MPI_Count) nx)*((MPI_Count) ny)*((MPI_Count) nz);

  printf("clen, bytes = %lld, %lld\n", clen, clen*sizeof(MPI_Count));

  memset(&array[0][0][0], 0, clen*sizeof(MPI_Count));

  printf("rank %d done memset\n", rank);

  if (rank == 0)
    {
      printf("nx, ny, nz = %d, %d, %d\n", nx, ny, nz);
      
      for (i=0; i < nx; i++)
        {
          printf("i = %d\n", i);
          for (j=0; j < ny; j++)
            {
              for (k=0; k < nz; k++)
                {
                  cval = ((MPI_Count) k) + ((MPI_Count) nz)*(((MPI_Count) j) + ((MPI_Count) ny)*((MPI_Count) i));
                  array[i][j][k] = cval;
                }
            }
        }
    }
  printf("rank %d before print\n", rank);
  
 printf("Before: rank = %d, array[1][1][1] = %lld, array[nx-1][ny-1][nz-1] = %lld\n", rank, array[1][1][1], array[nx-1][ny-1][nz-1]);

 MPI_Bcast(&array[0][0][0], nx*ny*nz, MPI_COUNT, 0, MPI_COMM_WORLD);

 // MPI_Bcast_c(&array[0][0][0], nx*ny*nz, MPI_COUNT, 0, MPI_COMM_WORLD);


 printf("After:  rank = %d, array[1][1][1] = %lld, array[nx-1][ny-1][nz-1] = %lld\n", rank, array[1][1][1], array[nx-1][ny-1][nz-1]);

 MPI_Finalize();

  return 0;
}
