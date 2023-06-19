#include "../review.h"

const size_t LINE_BUFFER_SIZE = 256;

int count_file_lines(const char filePath[])
{
  if(filePath == NULL) return 0;

  FILE* filePointer = fopen(filePath, "r");

  if(filePointer == NULL) return 0;
  
  char buffer[LINE_BUFFER_SIZE];
  int index = 0;

  for(index = 0; !feof(filePointer); index += 1)
  {
    if(fgets(buffer, sizeof(buffer), filePointer) == NULL) break;
  }
  fclose(filePointer);

  return index;
}

static bool extract_file_lines(char** fileLines, int* amount, FILE* filePointer)
{
  char buffer[LINE_BUFFER_SIZE];
  int index = 0;

  for(index = 0; !feof(filePointer); index += 1)
  {
    if(fgets(buffer, sizeof(buffer), filePointer) == NULL) break;

    sscanf(buffer, "%[^\n]%*c", fileLines[index]);
  }
  *amount = index;
  return true;
}

bool extract_text_file(char** fileLines, int* amount, const char filePath[])
{
  if(fileLines == NULL || amount == NULL || filePath == NULL) return false;

  FILE* filePointer = fopen(filePath, "r");

  if(filePointer == NULL) return false;

  bool result = extract_file_lines(fileLines, amount, filePointer);

  fclose(filePointer);
  return result;
}