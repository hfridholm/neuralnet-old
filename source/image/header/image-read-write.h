#ifndef IMAGE_READ_WRITE_H
#define IMAGE_READ_WRITE_H

float* pixels_nrmliz_vector(int* imgWidth, int* imgHeight, const char filePath[]);

float** pixels_nrmliz_matrix(int* imgWidth, int* imgHeight, const char filePath[]);

bool write_nrmmat_pixels(const char filePath[], float** nrmmat, int width, int height);

bool write_nrmarr_pixels(const char filePath[], float* nrmarr, int width, int height);

#endif
