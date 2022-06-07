#include "helpers.h"
#include <bmp.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3;
            images[i][j].rgbtBlue = avg;
            images[i][j].rgbtGreen = avg;
            images[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            images[i][j].rgbtBlue = .272 * images[i][j].rgbtRed + .534 * images[i][j].rgbtGreen + .131 * images[i][j].rgbtBlue;
            images[i][j].rgbtGreen = .349 * images[i][j].rgbtRed + .686 * images[i][j].rgbtGreen + .168 * images[i][j].rgbtBlue;
            images[i][j].rgbtRed = .393 * images[i][j].rgbtRed + .769 * images[i][j].rgbtGreen + .189 * images[i][j].rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

        }
    }
    return;
}
