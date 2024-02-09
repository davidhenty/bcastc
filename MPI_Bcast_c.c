#include <mpi.h>

int MPI_Bcast_c(void *buffer, MPI_Count count, MPI_Datatype datatype,
                int root, MPI_Comm comm)
{
  MPI_Count finishc, subcountc, ic;

  int subcounti;

  static int chunki = 0x40000000; // 2^31

  for (ic=0; ic < count; ic += chunki)
    {
      finishc = ic + chunki;
      if (finishc > count) finishc = count;
      subcountc = finishc - ic;
      subcounti = subcountc;
      MPI_Bcast(buffer+ic, subcounti, datatype, root, comm);
    }
  return MPI_SUCCESS;
}

