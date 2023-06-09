#ifndef IMAGE_READ_WRITE_H
#define IMAGE_READ_WRITE_H

float** image_pixels_nrmmat(int* width, int* height, const char imgPath[]);

bool write_nrmmat_pixels(const char filePath[], float** nrmmat, int width, int height);

bool write_nrmarr_pixels(const char filePath[], float* nrmarr, int width, int height);

#endif
