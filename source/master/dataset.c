#include "../engine/header/engine-include-header.h"

int main(int argc, char* argv[])
{
  char filePath[] = "../source/datasets/test-dataset.csv";

  char*** tokens = create_string_matrix(100, 10, 10);

  int tWidth = 0, tHeight = 0, tLength = 0;

  if(!text_file_tokens(tokens, &tHeight, &tWidth, &tLength, filePath, ",")) 
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

  char* binaryHeaders[] = {"symbol1", "symbol2"};
  int binaryAmount = 2;

  
  char*** strmat = create_string_matrix(tHeight, 20, 10);

  int newWidth = 0;

  onehot_strmat_headers(strmat, &newWidth, tokens, tHeight, tWidth, 10, binaryHeaders, binaryAmount);

  for(int hIndex = 0; hIndex < tHeight; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < newWidth; wIndex += 1)
    {
      if(wIndex == newWidth - 1) printf("%s\n", strmat[hIndex][wIndex]);
      else printf("%s, ", strmat[hIndex][wIndex]);
    }
  }

  free_string_matrix(strmat, tHeight, 20, 10);

  free_string_matrix(tokens, 100, 10, 10);

  return 0;
}
