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

extern int fpath_lines_amount(const char filePath[]);

extern bool fpath_lines_read(char** fileLines, int* amount, const char filePath[]);

#endif