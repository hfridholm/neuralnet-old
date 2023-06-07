#include "../dataset.h"

bool count_file_lines(int* amount, const char filePath[])
{
  FILE* filePointer = fopen(filePath, "r");

  if(filePointer == NULL) return false;
  
  char buffer[256]; int index = 0;

  for(index = 0; !feof(filePointer); index += 1)
  {
    if(fgets(buffer, sizeof(buffer), filePointer) == NULL) break;
  }
  fclose(filePointer);

  *amount = index; return true;
}

static bool extract_file_lines(char** fileLines, int* amount, FILE* filePointer)
{
  char buffer[256]; int index = 0;

  for(index = 0; !feof(filePointer); index += 1)
  {
    if(fgets(buffer, sizeof(buffer), filePointer) == NULL) break;

    sscanf(buffer, "%[^\n]%*c", fileLines[index]);
  }
  *amount = index; return true;
}

bool extract_text_file(char** fileLines, int* amount, const char filePath[])
{
  FILE* filePointer = fopen(filePath, "r");

  if(filePointer == NULL) return false;

  bool result = extract_file_lines(fileLines, amount, filePointer);

  fclose(filePointer); return result;
}
