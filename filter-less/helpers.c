#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
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
            image[i][j].rgbtBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            image[i][j].rgbtRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE tempBlue;
    BYTE tempGreen;
    BYTE tempRed;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < k; j++)
        {
            tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;
            image[i][k].rgbtBlue = tempBlue;

            tempGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][k].rgbtGreen = tempGreen;

            tempRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][k].rgbtRed = tempRed;

            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avgB;
    BYTE avgG;
    BYTE avgR;
    int surroundingCount;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avgB = 0;
            avgG = 0;
            avgR = 0;
            surroundingCount = 0;

            avgB += image[i][j].rgbtBlue;
            surroundingCount++;

            if (i + 1 < height)
            {
                avgB += image[i + 1][j].rgbtBlue;
                surroundingCount++;
            }
            if (image[i][j + 1] != NULL)
            {
                avgB += image[i][j + 1].rgbtBlue;
                surroundingCount++;
            }
            if (image[i - 1][j] != NULL)
            {
                avgB += image[i - 1][j].rgbtBlue;
                surroundingCount++;
            }
            if (image[i][j - 1] != NULL)
            {
                avgB += image[i][j - 1].rgbtBlue;
                surroundingCount++;
            }
            if (image[i + 1][j + 1] != NULL)
            {
                avgB += image[i + 1][j + 1].rgbtBlue;
                surroundingCount++;
            }
            if (image[i - 1][j + 1] != NULL)
            {
                avgB += image[i - 1][j + 1].rgbtBlue;
                surroundingCount++;
            }
            if (image[i + 1][j - 1] != NULL)
            {
                avgB += image[i + 1][j - 1].rgbtBlue;
                surroundingCount++;
            }
            if (image[i - 1][j - 1] != NULL)
            {
                avgB += image[i - 1][j - 1].rgbtBlue;
                surroundingCount++;
            }
            image[i][j].rgbtBlue = avgB / surroundingCount;




        }
    }
    return;
}
