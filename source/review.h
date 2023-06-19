#ifndef REVIEW_H
#define REVIEW_H

#include <math.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

extern int count_file_lines(const char filePath[]);

extern bool extract_text_file(char** fileLines, int* amount, const char filePath[]);

#endif