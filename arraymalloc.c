#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void **arraymalloc2d(int nx, int ny, size_t typesize)
{
  int i;
  void **array2d;

  size_t mallocsize;

  // total memory requirements including pointers

  mallocsize = nx*sizeof(void *) + nx*ny*typesize;

  array2d = (void **) malloc(mallocsize);

  // set first pointer to first element of data

  array2d[0] = (void *) (array2d + nx);

  for(i=1; i < nx; i++)
    {
      // set other pointers to point at subsequent rows

      array2d[i] = (void *) (((char *) array2d[i-1]) + ny*typesize);
    }

  return array2d;
}

void ***arraymalloc3d(int nx, int ny, int nz, size_t typesize)
{
  void ***array3d;

  size_t it, jt, nxt, nyt, nzt, mallocsize;

  nxt = nx;
  nyt = ny;
  nzt = nz;

  // total memory requirements including pointers

  mallocsize = (nxt + nxt*nyt)*sizeof(void *) + nxt*nyt*nzt*typesize;

  array3d = (void ***) malloc(mallocsize);

  for (it=0; it < nxt; it++)
    {
      array3d[it] = (void *) (array3d + nxt + nyt*it);

      for (jt=0; jt < nyt; jt++)
      {
        array3d[it][jt] = (void *) ( ((char *) (array3d + nxt + nxt*nyt)) + (nyt*nzt*it + nzt*jt)*typesize);
        
      }
    }
  return array3d;
}
