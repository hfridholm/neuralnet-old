#include "../engine/engine.h"
#include "../dataset/dataset.h"

int main(int argc, char* argv[])
{
  char filePath[] = "../source/assets/test-dataset.csv";

  char*** tokens = create_string_matrix(100, 10, 10);

  int tWidth = 0, tHeight = 0, tLength = 0;

  if(!text_file_tokens(tokens, &tHeight, &tWidth, &tLength, filePath, ",")) 
  {
    printf("Error text_file_tokens\n");
  }

  char* onehotHeaders[] = {"symbol1", "symbol2"};
  int onehotAmount = 2;

  char* nrmlizHeaders[] = {"number1"};
  int nrmlizAmount = 1;

  
  char*** strmat = create_string_matrix(tHeight, 20, tLength);

  prepare_strmat_data(strmat, &tWidth, tokens, tHeight, tWidth, tLength, onehotHeaders, onehotAmount, nrmlizHeaders, nrmlizAmount);
 
  for(int hIndex = 0; hIndex < tHeight; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < tWidth; wIndex += 1)
    {
      if(wIndex == tWidth - 1) printf("%s\n", strmat[hIndex][wIndex]);
      else printf("%s, ", strmat[hIndex][wIndex]);
    }
  }

  free_string_matrix(&strmat, tHeight, 20, tLength);

  free_string_matrix(&tokens, 100, 10, 10);

  return 0;
}
