#include "adjust.h"
#include "persue.h"
#include "secure.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <sys/time.h>

char* extract_shift_args(int* argc, char*** argv)
{
  if(*argc <= 0) return NULL;

  char* result = **argv;
  (*argc) -= 1;
  (*argv) += 1;
  return result;
}

int main(int argc, char* argv[])
{
  srand(time(NULL));

  char* program = extract_shift_args(&argc, &argv);
  if(program == NULL) return 1;


  struct timeval start;

  gettimeofday(&start, NULL);

  printf("Seconds: %ld Microseconds: %ld\n", start.tv_sec, start.tv_usec);

  //long int decimals = start.tv_usec / 1000 / 1000; 

//  long int seconds = start.tv_sec;

  long int hours = start.tv_sec % 86400 / 3600; 

  long int minutes = start.tv_sec % 3600 / 60;

  long int seconds = start.tv_sec % 60 / 1;

  long int decimals = start.tv_usec % 1000000;

  printf("%02ld:%02ld:%02ld.%06ld\n", hours, minutes, seconds, decimals);

  //printf("%d-%02d-%02d %02d:%02d:%02d.%ld\n",
  //  years, months, days, hours, minutes, seconds, decimals);


  return 0;
}
