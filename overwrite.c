#include <stdio.h>
#include <stdlib.h>

int destroy(char **, int);
void obliterate(FILE *, size_t, char *, int);

int main(int argc, char **argv)
{
  if(argc == 1)
  {
    printf("Please enter at least 1 file name\n");
    return 1;
  }

  if(!destroy(argv, argc))
  {
    printf("could not destroy file properly\n");
    return 2;
  }

  return 0;
}

int destroy(char **files, int file_no)
{
  FILE * fptr;
  size_t fsize;
  unsigned char annihalate;
  int index, iter; // iter == iterations

  for(index=0; index < file_no-1; index++)
  {
    if(!(fptr=fopen(files[index+1], "r+")))
    {
      printf("error opening file %s\n", files[index]);
      return 0;
    }
    fseek(fptr, 0L, SEEK_END);
    fsize = ftell(fptr);
    rewind(fptr);

    for(iter =0; iter < 7; iter++)
      obliterate(fptr, fsize, &annihalate, iter),
      printf("iter %d w/bit pattern %x\n", iter, annihalate);

    fclose(fptr);
    remove(files[index+1]);
  }
  return 1;
}

void obliterate(FILE *fptr, size_t files, char *dest, int iterations)
{
  switch(iterations)
  {
    case 0:
      *dest = 0xFF;
      fwrite(dest, sizeof(char), files, fptr);
      fflush(fptr);
      rewind(fptr);
      break;
    case 1:
      *dest = 0xAA;
      fwrite(dest, sizeof(char), files, fptr);
      fflush(fptr);
      rewind(fptr);
      break;
    case 2:
      *dest = 0x55;
      fwrite(dest, sizeof(char), files, fptr);
      fflush(fptr);
      rewind(fptr);
      break;
    case 3:
      *dest = 0xA5;
      fwrite(dest ,sizeof(char), files, fptr);
      fflush(fptr);
      rewind(fptr);
      break;
    case 4:
      *dest = 0x5A;
      fwrite(dest, sizeof(char), files, fptr);
      fflush(fptr);
      rewind(fptr);
      break;
    case 5:
      *dest = 0x96;
      fwrite(dest, sizeof(char), files, fptr);
      fflush(fptr);
      rewind(fptr);
      break;
    case 6:
      *dest = 0x00;
      fwrite(dest, sizeof(char), files, fptr);
      fflush(fptr);
      rewind(fptr);
      break;
    default:
      break;
  }
  iterations++;
}
