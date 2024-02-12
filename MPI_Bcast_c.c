#include <mpi.h>

int MPI_Bcast_c(void *buffer, MPI_Count count, MPI_Datatype datatype,
                int root, MPI_Comm comm)
{
  MPI_Count finishc, subcountc, ic, extentc, lbc;

  int subcounti;

  static int chunki = 0x40000000; // 2^31

  MPI_Type_get_extent_x(datatype, &lbc, &extentc);

  for (ic=0; ic < count; ic += chunki)
    {
      finishc = ic + chunki;
      if (finishc > count) finishc = count;
      subcountc = finishc - ic;
      subcounti = subcountc;
      MPI_Bcast((char *) buffer + ic*extentc, subcounti, datatype, root, comm);
    }

  return MPI_SUCCESS;
}

