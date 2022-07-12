#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Convert image to grayscale
// height - rows
// width - column
// 400 rows of 600 elements
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    printf("height=%i, width=%i\n", height, width);
    return;
}

// Convert image to sepia
//   sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
//   sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
//   sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
int into_0_255_range(WORD n)
{
    if (n < 0)
    {
        return 0;
    }
    else if (n > 255)
    {
        return 255;
    }
    return n;
}

typedef struct
{
    WORD rgbtBlue;
    WORD rgbtGreen;
    WORD rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE16;

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            RGBTRIPLE16 sepiaTripple;

            sepiaTripple.rgbtRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaTripple.rgbtGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaTripple.rgbtBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = into_0_255_range(sepiaTripple.rgbtRed);
            image[i][j].rgbtGreen = into_0_255_range(sepiaTripple.rgbtGreen);
            image[i][j].rgbtBlue = into_0_255_range(sepiaTripple.rgbtBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*copy_img)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_img[i][j].rgbtRed = image[i][j].rgbtRed;
            copy_img[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy_img[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy_img[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = copy_img[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = copy_img[i][width - 1 - j].rgbtBlue;
        }
    }
    free(copy_img);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE16(*copy_img)[width] = calloc(height, width * sizeof(RGBTRIPLE16));

    int slide_i[3] = {-1, 0, 1};
    int slide_j[3] = {-1, 0, 1};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_img[i][j].rgbtRed = 0;
            copy_img[i][j].rgbtGreen = 0;
            copy_img[i][j].rgbtBlue = 0;
            int cnt_ij = 0;
            for (int ii = 0; ii < 3; ii++)
            {
                for (int jj = 0; jj < 3; jj++)
                {
                    if ((i + slide_i[ii] >= 0) && (i + slide_i[ii] < height) && (j + slide_j[jj] >= 0) && (j + slide_j[jj] < width))
                    {
                        copy_img[i][j].rgbtRed += image[i + slide_i[ii]][j + slide_j[jj]].rgbtRed;
                        copy_img[i][j].rgbtGreen += image[i + slide_i[ii]][j + slide_j[jj]].rgbtGreen;
                        copy_img[i][j].rgbtBlue += image[i + slide_i[ii]][j + slide_j[jj]].rgbtBlue;
                        cnt_ij++;
                    }
                }
            }
            copy_img[i][j].rgbtRed = round(copy_img[i][j].rgbtRed / (float)cnt_ij);
            copy_img[i][j].rgbtGreen = round(copy_img[i][j].rgbtGreen / (float)cnt_ij);
            copy_img[i][j].rgbtBlue = round(copy_img[i][j].rgbtBlue / (float)cnt_ij);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy_img[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy_img[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy_img[i][j].rgbtBlue;
        }
    }

    return;
}
