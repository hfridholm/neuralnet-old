#include "../engine/engine.h"
#include "../dataset/dataset.h"

int main(int argc, char* argv[])
{
  srand(time(NULL));

  const char filePath[] = "../source/assets/test-dataset.csv";

  int amount = 0;

  bool result = count_file_lines(NULL, NULL);

  if(result) printf("%s has %d lines\n", filePath, amount);
  else printf("function failed\n");

  return 0;
}
