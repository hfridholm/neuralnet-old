#include "../engine/header/engine-include-header.h"

int main(int argc, char* argv[])
{
  char filePath[] = "../source/datasets/test-dataset.csv";

  char*** tokens = create_string_matrix(100, 10, 10);

  int tWidth = 0, tHeight = 0;

  if(!text_file_tokens(tokens, &tHeight, &tWidth, filePath, ",")) 
  {
    printf("Error text_file_tokens\n");
  }

  for(int hIndex = 0; hIndex < tHeight; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < tWidth; wIndex += 1)
    {
      if(wIndex == tWidth - 1) printf("%s\n", tokens[hIndex][wIndex]);
      else printf("%s | ", tokens[hIndex][wIndex]);
    }
  }

  free_string_matrix(tokens, 100, 10, 10);

  return 0;
}
