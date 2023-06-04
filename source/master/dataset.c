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

  char* binaryHeaders[] = {"symbol1", "symbol2"};
  int binaryAmount = 2;


  printf("height: %d width: %d length: %d\n", tHeight, tWidth, tLength);
  
  char*** strmat = create_string_matrix(tHeight, 20, tLength);

  int newWidth = 0;

  onehot_strmat_headers(strmat, &newWidth, tokens, tHeight, tWidth, tLength, binaryHeaders, binaryAmount);

  for(int hIndex = 0; hIndex < tHeight; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < newWidth; wIndex += 1)
    {
      if(wIndex == newWidth - 1) printf("%s\n", strmat[hIndex][wIndex]);
      else printf("%s, ", strmat[hIndex][wIndex]);
    }
  }

  free_string_matrix(strmat, tHeight, 20, tLength);

  free_string_matrix(tokens, 100, 10, 10);

  return 0;
}
