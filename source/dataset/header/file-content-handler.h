#ifndef FILE_CONTENT_HANDLER_H
#define FILE_CONTENT_HANDLER_H

extern bool count_file_lines(int* amount, const char filePath[]);

extern bool extract_text_file(char** fileLines, int* amount, const char filePath[]);

#endif
